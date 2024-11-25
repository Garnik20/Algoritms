#include <iostream>
#include <map>
#include <string>
#include <vector>

template <typename T>
// Класс min_heap - минимальнaq кучa
class MinHeap {
 private:
  // Массив кучи
  std::vector<T> heap_;

  // Функция sift_up поднимает элемент вверх по куче
  void SiftUp(size_t index) {
    while (index > 0 && heap_[index] < heap_[(index - 1) / 2]) {
      std::swap(heap_[index], heap_[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

  // Функция MinOfSons находит минимального из двух дочерних узлов
  size_t MinOfSons(size_t index) {
    size_t left_son = index * 2 + 1;
    size_t right_son = index * 2 + 2;
    size_t smallest = index;

    if (left_son < heap_.size() && heap_[left_son] < heap_[smallest]) {
      smallest = left_son;
    }
    if (right_son < heap_.size() && heap_[right_son] < heap_[smallest]) {
      smallest = right_son;
    }
    return smallest;
  }

  // Функция SiftDown опускает элемент вниз по куче
  void SiftDown(size_t index) {
    size_t smallest = MinOfSons(index);
    while (index != smallest) {
      std::swap(heap_[index], heap_[smallest]);
      index = smallest;
      smallest = MinOfSons(index);
    }
  }

 public:
  void Insert(T value) {
    heap_.push_back(value);  // Добавляем элемент в конец кучи.
    SiftUp(heap_.size() - 1);  // Восстанавливаем свойства кучи.
  }

  // Метод getMin возвращает минимальный элемент из кучи.
  T GetMin() { return heap_[0]; }

  // Метод extractMin удаляет минимальный элемент из кучи.
  void ExtractMin() {
    std::swap(heap_[0], heap_[heap_.size() - 1]);
    heap_.pop_back();
    if (!heap_.empty()) {
      SiftDown(0);
    }
  }

  // Метод decreaseKey уменьшает значение элемента в куче.
  void DecreaseKey(T value, T det) {
    // Находим индекс элемента с указанным значением.
    size_t count = 0;
    while (count < heap_.size() && heap_[count] != value) {
      ++count;
    }
    // Уменьшаем значение и поднимаем его, чтобы сохранить структуру кучи.
    heap_[count] -= det;
    SiftUp(count);
  }
};
template <typename T>
void Print(std::vector<T>& result) {
  for (int64_t item : result) {
    std::cout << item << "\n";
  }
}

template <typename T>
void Requests(MinHeap<T>& heap, size_t count, std::vector<T>& help_arr,
              std::vector<T>& result) {
  for (size_t i = 0; i < count; ++i) {
    std::string str;
    std::cin >> str;

    if (str == "insert") {
      int64_t value;
      std::cin >> value;
      heap.Insert(value);
      help_arr[i + 1] = value;
    } else if (str == "getMin") {
      result.emplace_back(heap.GetMin());
    } else if (str == "extractMin") {
      heap.ExtractMin();
    } else if (str == "decreaseKey") {
      int64_t det;
      size_t ind;
      std::cin >> ind >> det;  // Считываем индекс и значение для уменьшения.
      heap.DecreaseKey(help_arr[ind], det);  // Уменьшаем значение в куче.
      help_arr[ind] -= det;  // Обновляем значение в словаре.
    }
  }
}

int main() {
  MinHeap<int64_t> heap;
  size_t count;
  std::cin >> count;
  // Вектор для хранения вставленных элементов и их индексов.
  std::vector<int64_t> help_arr(count + 1);
  std::vector<int64_t> result;

  Requests(heap, count, help_arr, result);

  Print(result);
}
