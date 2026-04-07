#include "expression_tree.h"
#include <cctype>
#include <stdexcept>
#include <sstream>

NumberNode::NumberNode(int value) : value_(value) {}

int NumberNode::evaluate(int /*x*/) const {
    return value_;
}

std::string NumberNode::to_infix() const {
    std::ostringstream oss;
    oss << value_;
    return oss.str();
}

std::string NumberNode::to_prefix() const {
    std::ostringstream oss;
    oss << value_;
    return oss.str();
}

std::string NumberNode::to_postfix() const {
    std::ostringstream oss;
    oss << value_;
    return oss.str();
}

void NumberNode::transform() {
    // Ничего не делаем для чисел
}

int VariableNode::evaluate(int x) const {
    return x;
}

std::string VariableNode::to_infix() const {
    return "x";
}

std::string VariableNode::to_prefix() const {
    return "x";
}

std::string VariableNode::to_postfix() const {
    return "x";
}

void VariableNode::transform() {
    // Ничего не делаем для переменных
}

BinaryOperationNode::BinaryOperationNode(
    char op, std::unique_ptr<ExpressionNode> left,
    std::unique_ptr<ExpressionNode> right)
    : op_(op), left_(std::move(left)), right_(std::move(right)) {}

int BinaryOperationNode::evaluate(int x) const {
    int left_val = left_->evaluate(x);
    int right_val = right_->evaluate(x);

    switch (op_) {
    case '+':
        return left_val + right_val;
    case '-':
        return left_val - right_val;
    case '*':
        return left_val * right_val;
    case '/':
        if (right_val == 0) {
            throw std::runtime_error("Division by zero");
        }
        return left_val / right_val;
    case '%':
        if (right_val == 0) {
            throw std::runtime_error("Modulo by zero");
        }
        return left_val % right_val;
    case '^': {
        int result = 1;
        for (int i = 0; i < right_val; ++i) {
            result *= left_val;
        }
        return result;
    }
    default:
        throw std::runtime_error("Unknown operation");
    }
}

std::string BinaryOperationNode::to_infix() const {
    std::ostringstream oss;
    oss << "(" << left_->to_infix() << " " << op_ << " "
        << right_->to_infix() << ")";
    return oss.str();
}

std::string BinaryOperationNode::to_prefix() const {
    std::ostringstream oss;
    oss << op_ << " " << left_->to_prefix() << " "
        << right_->to_prefix();
    return oss.str();
}

std::string BinaryOperationNode::to_postfix() const {
    std::ostringstream oss;
    oss << left_->to_postfix() << " " << right_->to_postfix()
        << " " << op_;
    return oss.str();
}

void BinaryOperationNode::transform() {
    left_->transform();
    right_->transform();

    // Применяем преобразование A+x -> x+A
    if (op_ == '+' && dynamic_cast<VariableNode*>(right_.get())) {
        // Меняем местами левое и правое поддеревья
        std::swap(left_, right_);
    }
}

std::unique_ptr<ExpressionNode> ExpressionParser::parse(
    const std::string& expression) {
    expr_ = expression;
    pos_ = 0;
    return parse_expression();
}

std::unique_ptr<ExpressionNode> ExpressionParser::parse_expression() {
    return parse_additive();
}

std::unique_ptr<ExpressionNode> ExpressionParser::parse_additive() {
    auto left = parse_multiplicative();

    while (pos_ < expr_.size() && (expr_[pos_] == '+' || expr_[pos_] == '-')) {
        char op = expr_[pos_++];
        auto right = parse_multiplicative();
        left = std::make_unique<BinaryOperationNode>(op, std::move(left),
            std::move(right));
    }
    return left;
}

std::unique_ptr<ExpressionNode> ExpressionParser::parse_multiplicative() {
    auto left = parse_power();

    while (pos_ < expr_.size() &&
        (expr_[pos_] == '*' || expr_[pos_] == '/' || expr_[pos_] == '%')) {
        char op = expr_[pos_++];
        auto right = parse_power();
        left = std::make_unique<BinaryOperationNode>(op, std::move(left),
            std::move(right));
    }

    return left;
}
