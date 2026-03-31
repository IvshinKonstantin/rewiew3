#include <iostream>
#include <string>

#include "functions.h"

int main() {
  setlocale(LC_ALL, "Russian");

  std::string file_name;
  int k, l;

  std::cout << "Введите имя файла: ";
  std::cin >> file_name;
  std::cout << "Введите номер начального города K: ";
  std::cin >> k;
  std::cout << "Введите минимальное количество пересадок L: ";
  std::cin >> l;

  find_target_cities(file_name, k, l);

  return 0;
}
