#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

std::vector<double> LogPref(std::vector<double> inp_arr, size_t count) {
  // Преобразуем элементы массива с помощью натурального логарифма.
  // Это нужно, чтобы среднее геометрическое можно было найти через суммы
  // логарифмов

  std::vector<double> arr_log(count);
  for (size_t i = 0; i < count; ++i) {
    arr_log[i] = log(inp_arr[i]);
  }
  // Вычисляем префиксные суммы для массива логарифмов
  std::vector<double> pref_sum(count);
  pref_sum[0] = arr_log[0];
  for (size_t i = 1; i < count; ++i) {
    pref_sum[i] = pref_sum[i - 1] + arr_log[i];
  }

  return pref_sum;
}

int main() {
  const int Dec = 10;
  // Вводим количество элементов в массиве
  size_t count;
  std::cin >> count;

  // Вводим сам массив чисел
  std::vector<double> inp_arr(count);
  for (size_t i = 0; i < count; ++i) {
    std::cin >> inp_arr[i];
  }

  // Вводим количество запросов
  size_t count_req;
  std::cin >> count_req;

  // Вводим границы диапазонов для каждого запроса
  std::vector<size_t> left(count_req);
  std::vector<size_t> right(count_req);
  for (size_t i = 0; i < count_req; ++i) {
    std::cin >> left[i] >> right[i];
  }

  std::vector<double> pref_sum(count);
  pref_sum = LogPref(inp_arr, count);

  // Для каждого запроса находим среднее геометрическое чисел в диапазоне
  for (size_t i = 0; i < count_req; ++i) {
    // e ^ [(1/k) * (сумма логарифмов от left[i] до right[i])]
    // где k — это количество элементов в диапазоне
    double result = exp((pref_sum[right[i]] - pref_sum[left[i] - 1]) /
                        (right[i] - left[i] + 1));
    std::cout << std::fixed << std::setprecision(Dec) << result << '\n';
  }

  return 0;
}
