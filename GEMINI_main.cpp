#include <iostream>
#include <memory>
#include <string>

#include "functions.h"

int main() {
    setlocale(LC_ALL, "Russian");
    const std::string kFilename = "input.txt";

    // 1. Строим дерево.
    std::unique_ptr<Node> root = build_tree_from_file(kFilename);
    if (!root) {
        std::cerr << "Ошибка: файл не найден или пуст." << std::endl;
        return 1;
    }

    std::cout << "--- Исходное дерево ---" << std::endl;
    print_tree(root.get());

    // 2. Трансформируем (сворачиваем умножение).
    root = transform_tree(std::move(root));

    std::cout << "\n--- Трансформированное дерево ---" << std::endl;
    print_tree(root.get());

    // 3. Вывод адреса корня.
    std::cout << "\nУказатель на корень: " << root.get() << std::endl;

    return 0;
}
