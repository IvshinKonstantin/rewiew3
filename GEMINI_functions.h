#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <memory>
#include <string>

// Структура узла дерева.
struct Node {
	int value;  // Число (0-9) или код операции (-1...-5).
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;

	explicit Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Строит дерево из файла (обратная польская запись).
std::unique_ptr<Node> build_tree_from_file(const std::string& filename);

// Вычисляет значение поддерева.
int calculate(Node* root);

// Трансформирует дерево (удаляет операции умножения, заменяя их результатом).
std::unique_ptr<Node> transform_tree(std::unique_ptr<Node> root);

// Выводит дерево в консоль (повернуто на 90 градусов).
void print_tree(Node* root, int indent = 0);

#endif  // FUNCTIONS_H_
