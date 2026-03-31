#include "expression_tree.h"

#include <iostream>
#include <stdexcept>

int main() {
    try {
        std::string filename;
        std::cout << "Enter filename: ";
        std::getline(std::cin, filename);

        // Создаем объект дерева
        ExpressionTree tree(filename);

        // Строим дерево из файла
        tree.BuildFromFile();

        // Выводим корень до преобразования (для отладки)
        std::cout << "Root before transformation: " << tree.GetRoot() << std::endl;

        // Убираем операции умножения
        tree.EliminateMultiplication();

        // Выводим указатель на корень полученного дерева
        std::cout << "Root after transformation: " << tree.GetRoot() << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}