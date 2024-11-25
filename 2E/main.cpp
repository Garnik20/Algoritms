#include <cstdint>
#include <iostream>
#include <vector>

// Функция для разделения массива вокруг опорного элемента (pivot)
template <typename T>
T Partittion(std::vector<T>& arr, T left, T right, size_t ind) {
  T pivot = arr[ind];
  std::swap(arr[ind], arr[right]);
  T ind_pivot = left;

  // Перемещаем элементы меньше опорного в левую часть
  for (T j = left; j < right; ++j) {
    if (arr[j] < pivot) {
      std::swap(arr[ind_pivot], arr[j]);
      ind_pivot++;
    }
  }
  std::swap(arr[ind_pivot],
            arr[right]);  // Помещаем опорный элемент на своё место
  return ind_pivot;
}

template <typename T>
void ChosePivot(T left, T right, size_t& pivot) {
  pivot = left + std::rand() % (right - left + 1);
}

// Сортировка
template <typename T> void QuickSort(std::vector<T>& arr, T left, T right) {
  if (left < right) {
    size_t pivot_ind;
    ChosePivot(left, right, pivot_ind);

    // Разбиваем массив на части относительно (pivot)
    T partition_ind = Partittion<T>(arr, left, right, pivot_ind);

    // Рекурсивно сортируем левую и правую части
    QuickSort<T>(arr, left, partition_ind - 1);
    QuickSort<T>(arr, partition_ind + 1, right);
  }
}

int main() {
  size_t count;
  std::cin >> count;
  std::vector<uint32_t> arr(count);
  for (uint32_t item : arr) {
    std::cin >> item;
  }

  QuickSort<uint32_t>(arr, 0, arr.size() - 1);

  for (uint32_t item : arr) {
    std::cout << item << " ";
  }
  std::cout << '\n';

  return 0;
}
