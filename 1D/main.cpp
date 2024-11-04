#include <iostream>
#include <vector>

// Функция для проверки, можно ли добиться минимального расстояния distance
// между выбранными точками так, чтобы выбрать хотя бы k точек
bool is_can_for_d(std::vector<int> &arr, int distance, int count,
                  int count_ell) {
  int count = 0; // Счетчик подмножеств с суммой >= distance
  int sum = 0; // Переменная для накопления суммы расстояний между точками

  // Проходим по всем элементам массива
  for (size_t i = 0; i < count - 1; i++) {
    sum += arr[i];

    // Если сумма расстояний между точками >= distance, сбрасываем сумму и
    // увеличиваем счетчик
    if (sum >= distance) {
      sum = 0;
      count++;
    }
  }

  // Возвращаем true, если удалось найти не менее count_ell подходящих
  // интервалов, иначе false
  return count >= count_ell;
}

int main() {
  // Вводим количество точек count и количество отрезков count_ell
  int count, count_ell;
  std::cin >> count >> count_ell;

  // Вводим координаты точек
  std::vector<int> arr(count);
  for (size_t i = 0; i < count; i++) {
    std::cin >> arr[i];
  }

  // Границы бинарного поиска
  int mid_up = (arr[count - 1] - arr[0]) /
               (count_ell -
                1); // Верхняя граница — максимальное расстояние между точками
  int mid_down = 1; // Нижняя граница — минимальное расстояние

  // Преобразуем массив arr в массив расстояний между соседними точками
  for (size_t i = 0; i < count - 1; i++) {
    arr[i] = arr[i + 1] - arr[i];
  }

  // Цикл бинарного поиска
  while (mid_up - mid_down != 1) {
    // Находим середину текущего диапазона
    int mid = (mid_down + mid_up) / 2;

    // Проверяем, можно ли выбрать count_ell - 1 отрезков с минимальным
    // расстоянием mid
    if (is_can_for_d(arr, mid, count, count_ell - 1)) {
      mid_down = mid; // Если можно, поднимаем нижнюю границу
    } else {
      mid_up = mid; // Если нельзя, опускаем верхнюю границу
    }
  }

  // Проверяем крайние значения mid_down и mid_up для получения точного ответа
  if (is_can_for_d(arr, mid_down, count, count_ell - 1) &&
      is_can_for_d(arr, mid_up, count, count_ell - 1)) {
    std::cout << mid_up << '\n';
  } else {
    std::cout << mid_down << '\n';
  }
  return 0;
}
