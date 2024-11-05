#include <iostream>
#include <vector>

// Функция для разделения массива вокруг опорного элемента (pivot)
int Partittion(std::vector<int> &arr, int left, int right, int ind) {
  int pivot = arr[ind];
  std::swap(arr[ind], arr[right]);
  int ind_pivot = left;

  // Перемещаем элементы меньше опорного в левую часть
  for (int j = left; j < right; ++j) {
    if (arr[j] < pivot) {
      std::swap(arr[ind_pivot], arr[j]);
      ind_pivot++;
    }
  }
  std::swap(arr[ind_pivot], arr[right]); // Помещаем опорный элемент на своё место
  return ind_pivot;
}

// Сортировка
void QuickSort(std::vector<int> &arr, int left, int right) {
  if (left < right) {
    int pivot_ind = left + std::rand() % (right - left + 1);

    // Разбиваем массив на части относительно (pivot)
    int partition_ind = Partittion(arr, left, right, pivot_ind);

    // Рекурсивно сортируем левую и правую части
    QuickSort(arr, left, partition_ind - 1);
    QuickSort(arr, partition_ind + 1, right);
  }
}

int main() {
  int count;
  std::cin >> count;
  std::vector<int> arr;
  int num;
  for (int i = 0; i < count; i++) {
    std::cin >> num;
    arr.push_back(num);
  }

  QuickSort(arr, 0, arr.size() - 1);

  for (int i = 0; i < count - 1; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << arr[count - 1] << '\n';

  return 0;
}
