#include <cstdint>
#include <iostream>
#include <vector>

// Функция для разделения массива вокруг опорного элемента (pivot)
template <typename T, typename Comparator>
size_t Partition(std::vector<T>& arr, size_t left, size_t right,
                 size_t pivot_ind, Comparator comp) {
  T pivot = arr[pivot_ind];
  std::swap(arr[pivot_ind], arr[right]);  // Переместим опорный элемент в конец
  size_t ind_pivot = left;

  // Перемещаем элементы, удовлетворяющие компаратору, в левую часть
  for (size_t j = left; j < right; ++j) {
    if (comp(arr[j], pivot)) {
      std::swap(arr[ind_pivot], arr[j]);
      ++ind_pivot;
    }
  }
  std::swap(arr[ind_pivot],
            arr[right]);  // Помещаем опорный элемент на своё место
  return ind_pivot;
}

// Функция для выбора случайного опорного элемента (pivot)
void ChoosePivot(size_t left, size_t right, size_t& pivot) {
  size_t random_number = std::rand() % right;
  if (random_number >= left) {
    pivot = random_number;
  } else {
    pivot = right - random_number;
  }
}

// Сортировка
template <typename T, typename Comparator = std::less<T>>
void QuickSort(std::vector<T>& arr, size_t left, size_t right,
               Comparator comp = Comparator()) {
  if (left < right) {
    size_t pivot_ind;
    ChoosePivot(left, right, pivot_ind);

    // Разбиваем массив на части относительно pivot
    size_t partition_ind = Partition(arr, left, right, pivot_ind, comp);

    // Рекурсивно сортируем левую и правую части
    QuickSort(arr, left, partition_ind - 1, comp);
    QuickSort(arr, partition_ind + 1, right, comp);
  }
}

template <typename T>
void Input(std::vector<T>& arr) {
  for (T& item : arr) {
    std::cin >> item;
  }
}

template <typename T>
void Print(const std::vector<T>& arr) {
  for (const T& item : arr) {
    std::cout << item << " ";
  }
  std::cout << '\n';
}

int main() {
  size_t count;
  std::cin >> count;
  std::vector<uint32_t> arr(count);

  Input(arr);

  // Сортируем
  QuickSort<uint32_t>(arr, 0, arr.size() - 1, std::less<uint32_t>());

  Print(arr);

  return 0;
}
