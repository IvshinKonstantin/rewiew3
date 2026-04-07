#include <fstream>
#include <iostream>
#include <stdexcept>
#include "expression_tree.h"

// Константы для имён файлов
const std::string kInputFileName = "FN1";
const std::string kOutputFileName = "FN2";

int main() {
    try {
        // Читаем выражение из входного файла
        std::ifstream input_file(kInputFileName);
        if (!input_file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл FN1 для чтения");
        }

        std::string expression;
        std::getline(input_file, expression);
        input_file.close();

        // Парсим выражение в дерево
        ExpressionParser parser;
        auto expression_tree = parser.parse(expression);

        // Запрашиваем значение переменной x
        int x_value;
        std::cout << "Введите значение переменной x: ";
        std::cin >> x_value;

        // Вычисляем значение выражения
        int result = expression_tree->evaluate(x_value);

        // Открываем выходной файл
        std::ofstream output_file(kOutputFileName);
        if (!output_file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл FN2 для записи");
        }

        // Записываем результат вычисления
        output_file << "Результат вычисления при x = " << x_value
            << ": " << result << std::endl << std::endl;

        // Преобразуем дерево: A+x -> x+A
        expression_tree->transform();

        // Записываем дерево в разных формах
        output_file << "Префиксная форма: " << expression_tree->to_prefix()
            << std::endl;
        output_file << "Постфиксная форма: " << expression_tree->to_postfix()
            << std::endl;
        output_file << "Инфиксная форма с избыточными скобками: "
            << expression_tree->to_infix() << std::endl;

        output_file.close();
        std::cout << "Результаты записаны в файл " << kOutputFileName << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
