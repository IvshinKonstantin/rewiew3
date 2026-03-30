#include <iostream>
#include "functions.h"

int main() {
    setlocale(LC_ALL, "Russian");
    std::string filename = "input.txt";

    // 1. Строим дерево
    Node* root = buildTreeFromFile(filename);
    if (!root) {
        std::cerr << "Ошибка: не удалось прочитать файл или файл пуст." << std::endl;
        return 1;
    }

    std::cout << "--- Исходное дерево ---" << std::endl;
    printTree(root);

    // 2. Трансформируем (удаляем умножение)
    root = transformTree(root);

    std::cout << "\n--- Трансформированное дерево (без умножения) ---" << std::endl;
    printTree(root);

    // 3. Выводим указатель на корень, как просит задача
    std::cout << "\nУказатель на корень: " << root << std::endl;

    // Очистка памяти
    deleteTree(root);

    return 0;
}
