#pragma once
#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <memory>
#include <string>

// Константы для кодирования операций
const int kAddition = -1;
const int kSubtraction = -2;
const int kMultiplication = -3;
const int kDivision = -4;
const int kModulo = -5;

// Узел дерева выражения
class TreeNode {
public:
    // Конструктор для операнда (целое число 0-9)
    explicit TreeNode(int value);

    // Конструктор для оператора
    TreeNode(int op, std::unique_ptr<TreeNode> left,
        std::unique_ptr<TreeNode> right);

    // Проверяет, является ли узел операндом
    bool IsOperand() const;

    // Проверяет, является ли узел оператором умножения
    bool IsMultiplication() const;

    // Вычисляет значение поддерева
    int Evaluate() const;

    // Заменяет поддерево на его вычисленное значение
    void FoldMultiplication();

    int data;  // Значение: для операнда - число (0-9),
    // для оператора - код операции (-1 до -5)
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;
};

// Класс для построения и обработки дерева выражения
class ExpressionTree {
public:
    // Конструктор принимает имя файла с выражением в ОПН
    explicit ExpressionTree(const std::string& filename);

    // Строит дерево из выражения в файле
    void BuildFromFile();

    // Убирает операции умножения, заменяя их вычисленными значениями
    void EliminateMultiplication();

    // Возвращает указатель на корень дерева
    TreeNode* GetRoot() const;

private:
    std::string filename_;  // Имя входного файла
    std::unique_ptr<TreeNode> root_;  // Корень дерева

    // Парсит строку и строит дерево
    std::unique_ptr<TreeNode> ParseExpression(const std::string& expr);

    // Проверяет, является ли символ оператором
    bool IsOperator(char ch) const;

    // Преобразует символ оператора в код операции
    int OperatorToCode(char op) const;
};

#endif  // EXPRESSION_TREE_H