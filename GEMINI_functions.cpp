#include "functions.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <vector>

std::unique_ptr<Node> build_tree_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return nullptr;

    std::stack<std::unique_ptr<Node>> s;
    char ch;

    while (file >> ch) {
        if (isdigit(ch)) {
            s.push(std::make_unique<Node>(ch - '0'));
        }
        else {
            int op_code = 0;
            if (ch == '+') op_code = -1;
            else if (ch == '-') op_code = -2;
            else if (ch == '*') op_code = -3;
            else if (ch == '/') op_code = -4;
            else if (ch == '%') op_code = -5;

            if (op_code != 0 && s.size() >= 2) {
                auto new_node = std::make_unique<Node>(op_code);
                // В ОПЗ: второй операнд сверху, первый под ним.
                new_node->right = std::move(s.top());
                s.pop();
                new_node->left = std::move(s.top());
                s.pop();
                s.push(std::move(new_node));
            }
        }
    }
    return s.empty() ? nullptr : std::move(s.top());
}

int calculate(Node* root) {
    if (!root) return 0;
    if (root->value >= 0) return root->value;

    int left_val = calculate(root->left.get());
    int right_val = calculate(root->right.get());

    switch (root->value) {
    case -1: return left_val + right_val;
    case -2: return left_val - right_val;
    case -3: return left_val * right_val;
    case -4: return (right_val != 0) ? left_val / right_val : 0;
    case -5: return (right_val != 0) ? left_val % right_val : 0;
    default: return 0;
    }
}

std::unique_ptr<Node> transform_tree(std::unique_ptr<Node> root) {
    if (!root) return nullptr;

    // Рекурсивно обрабатываем детей.
    root->left = transform_tree(std::move(root->left));
    root->right = transform_tree(std::move(root->right));

    // Если операция — умножение, заменяем узел числом.
    if (root->value == -3) {
        int result = calculate(root.get());
        auto leaf = std::make_unique<Node>(result);
        return leaf;
    }

    return root;
}

void print_tree(Node* root, int indent) {
    if (root != nullptr) {
        if (root->right) print_tree(root->right.get(), indent + 4);

        if (indent) std::cout << std::string(indent, ' ');

        if (root->value >= 0) {
            std::cout << root->value << "\n";
        }
        else {
            const char ops[] = { '?', '+', '-', '*', '/', '%' };
            std::cout << ops[std::abs(root->value)] << "\n";
        }

        if (root->left) print_tree(root->left.get(), indent + 4);
    }
}
