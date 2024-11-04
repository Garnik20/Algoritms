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
  std::vector<int> r(q), l(q);
  for (int i = 0; i < q; ++i) {
    std::cin >> l[i] >> r[i];
  }
  
  // Преобразуем элементы массива с помощью натурального логарифма.
  // Это нужно, чтобы среднее геометрическое можно было найти через суммы логарифмов
  std::vector<double> lg(n);
  for (int i = 0; i < n; ++i) {
    lg[i] = log(a[i]);
  }

  // Вычисляем префиксные суммы для массива логарифмов
  std::vector<double> pref_sum(n);
  pref_sum[0] = lg[0];
  for (int i = 1; i < n; ++i) {
    pref_sum[i] = pref_sum[i - 1] + lg[i];
  }
  
  // Для каждого запроса находим среднее геометрическое чисел в диапазоне
  for (int i = 0; i < q; ++i) {
    // e ^ [(1/k) * (сумма логарифмов от l[i] до r[i])]
    // где k — это количество элементов в диапазоне
    printf("%.10f\n",
           exp((pref_sum[r[i]] - pref_sum[l[i] - 1]) / (r[i] - l[i] + 1)));
  }

  return 0;
}
