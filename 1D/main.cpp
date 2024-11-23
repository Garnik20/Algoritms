#include <cstdint>
#include <iostream>
#include <vector>

// Функция для проверки, можно ли добиться минимального расстояния distance
// между выбранными точками так, чтобы выбрать хотя бы k точек
bool IsCanForD(std::vector<uint32_t>& arr, uint32_t distance, size_t count,
               size_t count_ell) {
  size_t exe_count = 0;  // Счетчик подмножеств с суммой >= distance
  uint32_t sum = 0;  // Переменная для суммы расстояний между точками

  // Проходим по всем элементам массива
  for (size_t i = 0; i < count - 1; i++) {
    sum += arr[i];

    // Если сумма расстояний между точками >= distance, сбрасываем сумму и
    // увеличиваем счетчик
    if (sum >= distance) {
      sum = 0;
      exe_count++;
    }
  }

  // Возвращаем true, если удалось найти не менее count_ell подходящих
  // интервалов, иначе false
  return exe_count >= count_ell;
}

uint32_t Search(std::vector<uint32_t> &arr, size_t count, size_t count_ell) {
  // Границы бинарного поиска
  uint32_t mid_up =
      (arr[count - 1] - arr[0]) /
      (count_ell -
       1);  // Верхняя граница — максимальное расстояние между точками
  uint32_t mid_down = 1;  // Нижняя граница — минимальное расстояние

  // Преобразуем массив arr в массив расстояний между соседними точками
  for (size_t i = 0; i < count - 1; i++) {
    arr[i] = arr[i + 1] - arr[i];
  }

  // Цикл бинарного поиска
  while (mid_up - mid_down != 1) {
    // Находим середину текущего диапазона
    uint32_t mid = (mid_down + mid_up) / 2;

    // Проверяем, можно ли выбрать count_ell - 1 отрезков с минимальным
    // расстоянием mid
    if (IsCanForD(arr, mid, count, count_ell - 1)) {
      mid_down = mid;  // Если можно, поднимаем нижнюю границу
      continue;
    }
    mid_up = mid;  // Если нельзя, опускаем верхнюю границу
  }

  uint32_t result;
  // Проверяем крайние значения mid_down и mid_up для получения точного ответа
  if (IsCanForD(arr, mid_down, count, count_ell - 1) &&
      IsCanForD(arr, mid_up, count, count_ell - 1)) {
    result = mid_up;
  } else {
    result = mid_down;
  }

  return result;
}

int main() {
  // Вводим количество точек count и количество отрезков count_ell
  size_t count_ell;
  size_t count;
  std::cin >> count >> count_ell;

  // Вводим координаты точек
  std::vector<uint32_t> arr(count);
  for (size_t i = 0; i < count; i++) {
    std::cin >> arr[i];
  }

  uint32_t reslut;
  reslut = Search(arr, count, count_ell);

  // Вывод
  std::cout << reslut << '\n';

  return 0;
}
