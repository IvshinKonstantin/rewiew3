#include "expression_tree.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

// Реализация TreeNode
TreeNode::TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}

TreeNode::TreeNode(int op, std::unique_ptr<TreeNode> left_node,
    std::unique_ptr<TreeNode> right_node)
    : data(op), left(std::move(left_node)), right(std::move(right_node)) {}

bool TreeNode::IsOperand() const {
    // Операндами являются числа от 0 до 9
    return data >= 0 && data <= 9;
}

bool TreeNode::IsMultiplication() const {
    return data == kMultiplication;
}

int TreeNode::Evaluate() const {
    if (IsOperand()) {
        return data;
    }

    int left_val = left->Evaluate();
    int right_val = right->Evaluate();

    switch (data) {
    case kAddition:
        return left_val + right_val;
    case kSubtraction:
        return left_val - right_val;
    case kMultiplication:
        return left_val * right_val;
    case kDivision:
        // Проверка деления на ноль
        if (right_val == 0) {
            throw std::runtime_error("Division by zero");
        }
        return left_val / right_val;
    case kModulo:
        // Проверка деления на ноль
        if (right_val == 0) {
            throw std::runtime_error("Modulo by zero");
        }
        return left_val % right_val;
    default:
        throw std::runtime_error("Unknown operator");
    }
}

void TreeNode::FoldMultiplication() {
    // Сначала обрабатываем левое поддерево
    if (left) {
        left->FoldMultiplication();
    }

    // Затем обрабатываем правое поддерево
    if (right) {
        right->FoldMultiplication();
    }

    // Если текущий узел - умножение, заменяем его на значение
    if (IsMultiplication()) {
        int computed_value = Evaluate();
        // Создаем новый узел-операнд с вычисленным значением
        // Освобождаем память дочерних узлов через умные указатели
        std::unique_ptr<TreeNode> new_node =
            std::make_unique<TreeNode>(computed_value);
        // Перемещаем данные из нового узла в текущий
        data = new_node->data;
        left.reset();
        right.reset();
    }
}

// Реализация ExpressionTree
ExpressionTree::ExpressionTree(const std::string& filename)
    : filename_(filename), root_(nullptr) {}

void ExpressionTree::BuildFromFile() {
    std::ifstream file(filename_);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename_);
    }

    std::string line;
    std::getline(file, line);
    file.close();

    if (line.empty()) {
        throw std::runtime_error("File is empty");
    }

    root_ = ParseExpression(line);
}

std::unique_ptr<TreeNode> ExpressionTree::ParseExpression(
    const std::string& expr) {
    std::stack<std::unique_ptr<TreeNode>> node_stack;
    std::istringstream iss(expr);
    std::string token;

    while (iss >> token) {
        // Проверяем, является ли токен оператором
        if (token.length() == 1 && IsOperator(token[0])) {
            // Для бинарного оператора нужно два операнда
            if (node_stack.size() < 2) {
                throw std::runtime_error("Invalid expression: not enough operands");
            }

            // Извлекаем правый и левый операнды (обратный порядок)
            std::unique_ptr<TreeNode> right = std::move(node_stack.top());
            node_stack.pop();
            std::unique_ptr<TreeNode> left = std::move(node_stack.top());
            node_stack.pop();

            int op_code = OperatorToCode(token[0]);
            auto node = std::make_unique<TreeNode>(op_code, std::move(left),
                std::move(right));
            node_stack.push(std::move(node));
        }
        else {
            // Токен - операнд (целое число)
            try {
                int value = std::stoi(token);
                if (value < 0 || value > 9) {
                    throw std::runtime_error("Operand out of range (0-9): " + token);
                }
                auto node = std::make_unique<TreeNode>(value);
                node_stack.push(std::move(node));
            }
            catch (const std::invalid_argument&) {
                throw std::runtime_error("Invalid token: " + token);
            }
        }
    }

    // После обработки всех токенов в стеке должен быть один узел
    if (node_stack.size() != 1) {
        throw std::runtime_error("Invalid expression: too many operands");
    }

    return std::move(node_stack.top());
}

bool ExpressionTree::IsOperator(char ch) const {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
}

int ExpressionTree::OperatorToCode(char op) const {
    switch (op) {
    case '+': return kAddition;
    case '-': return kSubtraction;
    case '*': return kMultiplication;
    case '/': return kDivision;
    case '%': return kModulo;
    default:
        throw std::runtime_error("Unknown operator: " + std::string(1, op));
    }
}

void ExpressionTree::EliminateMultiplication() {
    if (root_) {
        root_->FoldMultiplication();
    }
}

TreeNode* ExpressionTree::GetRoot() const {
    return root_.get();
}