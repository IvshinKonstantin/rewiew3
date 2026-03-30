#include "functions.h"
#include <fstream>
#include <stack>
#include <iostream>

Node* buildTreeFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return nullptr;

    std::stack<Node*> s;
    char ch;

    while (file >> ch) {
        if (isdigit(ch)) {
            s.push(new Node(ch - '0'));
        }
        else {
            int opCode = 0;
            if (ch == '+') opCode = -1;
            else if (ch == '-') opCode = -2;
            else if (ch == '*') opCode = -3;
            else if (ch == '/') opCode = -4;
            else if (ch == '%') opCode = -5;

            if (opCode != 0) {
                Node* newNode = new Node(opCode);
                // В ОПЗ: второй операнд сверху, первый под ним
                newNode->right = s.top(); s.pop();
                newNode->left = s.top(); s.pop();
                s.push(newNode);
            }
        }
    }
    return s.empty() ? nullptr : s.top();
}

int calculate(Node* root) {
    if (!root) return 0;
    if (root->value >= 0) return root->value;

    int leftVal = calculate(root->left);
    int rightVal = calculate(root->right);

    switch (root->value) {
    case -1: return leftVal + rightVal;
    case -2: return leftVal - rightVal;
    case -3: return leftVal * rightVal;
    case -4: return (rightVal != 0) ? leftVal / rightVal : 0;
    case -5: return (rightVal != 0) ? leftVal % rightVal : 0;
    default: return 0;
    }
}

Node* transformTree(Node* root) {
    if (!root) return nullptr;

    // Сначала обрабатываем детей (снизу вверх)
    root->left = transformTree(root->left);
    root->right = transformTree(root->right);

    // Если текущая операция — умножение (-3)
    if (root->value == -3) {
        int result = calculate(root);
        // Удаляем старые ветки умножения
        deleteTree(root->left);
        deleteTree(root->right);
        // Превращаем узел в лист со значением
        root->value = result;
        root->left = nullptr;
        root->right = nullptr;
    }

    return root;
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void printTree(Node* root, int indent) {
    if (root != nullptr) {
        if (root->right) printTree(root->right, indent + 4);
        if (indent) std::cout << std::string(indent, ' ');

        if (root->value >= 0) std::cout << root->value << "\n";
        else {
            char ops[] = { '?', '+', '-', '*', '/', '%' };
            std::cout << ops[abs(root->value)] << "\n";
        }
        if (root->left) printTree(root->left, indent + 4);
    }
}
