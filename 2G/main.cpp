#include <cstdint>
#include <iostream>
#include <vector>

// Функция для сортировки по конкретному байту
template <typename T>
void SortByByte(std::vector<T>& arr, uint32_t byte_ind, size_t count) {
  std::vector<T> output(count);
  const uint8_t kHex = 0b11111111;
  const uint8_t kByt = 8;
  std::vector<uint32_t> count_byte(kHex, 0);

  // Считаем частоты каждого значения байта на позиции byte_ind для всех чисел
  for (size_t i = 0; i < count; ++i) {
    unsigned char byte = (arr[i] >> (byte_ind * kByt)) & kHex;
    count_byte[byte]++;  // Увеличиваем счетчик для данного байта
  }

  // Накапливаем частоты для определения позиций элементов
  for (size_t i = 1; i < kHex; ++i) {
    count_byte[i] += count_byte[i - 1];
  }

  // Заполняем массив output, размещая элементы в порядке, определенном count
  for (size_t i = count - 1; i >= 0; --i) {
    uint8_t byte = (arr[i] >> (byte_ind * kByt)) & kHex;
    output[--count_byte[byte]] = arr[i];
  }

  // Копируем отсортированные значения из output обратно в исходный массив
  for (size_t i = 0; i < count; ++i) {
    arr[i] = output[i];
  }
}

// LSD сортировка для длинных чисел (long long)
template <typename T>
void SortLSD(std::vector<T>& arr, size_t count) {
  const int kByt = 8;
  // Последовательно сортируем по каждому байту (от младшего к старшему)
  for (size_t byte_ind = 0; byte_ind < kByt; ++byte_ind) {
    SortByByte(arr, byte_ind, count); // Сортируем по конкретному байту
  }
}

int main() {
  int count;
  std::cin >> count;  // Считываем количество элементов
  std::vector<uint64_t> arr(count);  // Вектор для хранения элементов

  // Считываем элементы и добавляем в массив
  for (uint64_t item : arr) {
    std::cin >> item;
  }

  // Выполняем сортировку LSD
  SortLSD(arr, count);

  // Выводим отсортированные элементы
  for (uint64_t num : arr) {
    std::cout << num << "\n";
  }

  return 0;
}
