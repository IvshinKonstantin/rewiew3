#pragma once
#pragma once
#include <string>

// Структура узла дерева
struct Node {
    int value; // Число (0-9) или код операции (-1...-5)
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для построения дерева из файла (ОПЗ)
Node* buildTreeFromFile(const std::string& filename);

// Функция для вычисления значения поддерева (нужна для трансформации)
int calculate(Node* root);

// Функция для трансформации дерева (удаление умножения)
Node* transformTree(Node* root);

// Функция для очистки памяти
void deleteTree(Node* root);

// Вспомогательная функция для вывода дерева (для проверки)
void printTree(Node* root, int indent = 0);
