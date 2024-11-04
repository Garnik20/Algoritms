#include <cmath>
#include <iostream>
#include <vector>

int main() {
  // Вводим количество элементов в массиве
  int count;
  std::cin >> count;

  // Вводим сам массив чисел
  std::vector<double> inp_arr(count);
  for (int i = 0; i < count; ++i) {
    std::cin >> inp_arr[i];
  }

  // Вводим количество запросов
  int count_req;
  std::cin >> count_req;

  // Вводим границы диапазонов для каждого запроса
  std::vector<int> left(count_req);
  std::vector<int> right(count_req);
  for (int i = 0; i < count_req; ++i) {
    std::cin >> left[i] >> right[i];
  }

  // Преобразуем элементы массива с помощью натурального логарифма.
  // Это нужно, чтобы среднее геометрическое можно было найти через суммы
  // логарифмов
  std::vector<double> arr_log(count);
  for (int i = 0; i < count; ++i) {
    arr_log[i] = log(inp_arr[i]);
  }

  // Вычисляем префиксные суммы для массива логарифмов
  std::vector<double> pref_sum(count);
  pref_sum[0] = arr_log[0];
  for (int i = 1; i < count; ++i) {
    pref_sum[i] = pref_sum[i - 1] + arr_log[i];
  }

  // Для каждого запроса находим среднее геометрическое чисел в диапазоне
  for (int i = 0; i < count_req; ++i) {
    // e ^ [(1/k) * (сумма логарифмов от left[i] до right[i])]
    // где k — это количество элементов в диапазоне
    printf("%.10f\n", exp((pref_sum[right[i]] - pref_sum[left[i] - 1]) /
                          (right[i] - left[i] + 1)));
  }

  return 0;
}
