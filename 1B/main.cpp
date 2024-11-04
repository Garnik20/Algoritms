#include <cmath>
#include <iostream>
#include <vector>

int main() {
  // Вводим количество элементов в массиве
  int n;
  std::cin >> n;

  // Вводим сам массив чисел
  std::vector<double> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  // Вводим количество запросов
  int q;
  std::cin >> q;

  // Вводим границы диапазонов для каждого запроса
  std::vector<int> left(q);
  std::vector<int> right(q);
  for (int i = 0; i < q; ++i) {
    std::cin >> left[i] >> right[i];
  }

  // Преобразуем элементы массива с помощью натурального логарифма.
  // Это нужно, чтобы среднее геометрическое можно было найти через суммы
  // логарифмов
  std::vector<double> arr_log(n);
  for (int i = 0; i < n; ++i) {
    arr_log[i] = log(a[i]);
  }

  // Вычисляем префиксные суммы для массива логарифмов
  std::vector<double> pref_sum(n);
  pref_sum[0] = arr_log[0];
  for (int i = 1; i < n; ++i) {
    pref_sum[i] = pref_sum[i - 1] + arr_log[i];
  }

  // Для каждого запроса находим среднее геометрическое чисел в диапазоне
  for (int i = 0; i < q; ++i) {
    // e ^ [(1/k) * (сумма логарифмов от left[i] до right[i])]
    // где k — это количество элементов в диапазоне
    printf("%.10f\n", exp((pref_sum[right[i]] - pref_sum[left[i] - 1]) /
                          (right[i] - left[i] + 1)));
  }

  return 0;
}
