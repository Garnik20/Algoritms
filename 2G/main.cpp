#include <iostream>
#include <vector>

// Функция для сортировки по конкретному байту
void SortByByte(std::vector<long long>& arr, int byte_ind, int count) {
  std::vector<long long> output(count);
  int count_byte[256] = {0};

  // Считаем частоты каждого значения байта на позиции byte_ind для всех чисел
  for (int i = 0; i < count; ++i) {
    unsigned char byte = (arr[i] >> (byte_ind * 8)) & 0b11111111;
    count_byte[byte]++;  // Увеличиваем счетчик для данного байта
  }

  // Накапливаем частоты для определения позиций элементов
  for (int i = 1; i < 256; ++i) {
    count_byte[i] += count_byte[i - 1];
  }

  // Заполняем массив output, размещая элементы в порядке, определенном count
  for (int i = count - 1; i >= 0; --i) {
    unsigned char byte = (arr[i] >> (byte_ind * 8)) & 0b11111111;
    output[--count_byte[byte]] = arr[i];
  }

  // Копируем отсортированные значения из output обратно в исходный массив
  for (int i = 0; i < count; ++i) {
    arr[i] = output[i];
  }
}

// LSD сортировка для длинных чисел (long long)
void SortLSD(std::vector<long long>& arr, int count) {
  // Последовательно сортируем по каждому байту (от младшего к старшему)
  for (int byte_ind = 0; byte_ind < 8; ++byte_ind) {
    SortByByte(arr, byte_ind, count);  // Сортируем по конкретному байту
  }
}

int main() {
  int count;
  std::cin >> count; // Считываем количество элементов
  std::vector<long long> arr; // Вектор для хранения элементов

  // Считываем элементы и добавляем в массив
  long long num;
  for (int i = 0; i < count; i++) {
    std::cin >> num;
    arr.push_back(num);
  }

  // Выполняем сортировку LSD
  SortLSD(arr, count);

  // Выводим отсортированные элементы
  for (long long num : arr) {
    std::cout << num << "\n";
  }

  return 0;
}
