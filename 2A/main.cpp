#include <iostream>
#include <map>
#include <string>
#include <vector>

// Класс min_heap - минимальнaq кучa
class MinHeap {
 private:
  // Массив кучи
  std::vector<int64_t> heap_;

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
  void Insert(int64_t value) {
    heap_.push_back(value);  // Добавляем элемент в конец кучи.
    SiftUp(heap_.size() - 1);  // Восстанавливаем свойства кучи.
  }

  // Метод getMin возвращает минимальный элемент из кучи.
  int64_t GetMin() { return heap_[0]; }

  // Метод extractMin удаляет минимальный элемент из кучи.
  void ExtractMin() {
    std::swap(heap_[0], heap_[heap_.size() - 1]);
    heap_.pop_back();
    if (!heap_.empty()) {
      SiftDown(0);
    }
  }

  // Метод decreaseKey уменьшает значение элемента в куче.
  void DecreaseKey(int64_t value,int64_t det) {
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

int main() {
  MinHeap heap;
  size_t count;
  std::cin >> count;
  // Словарь для хранения вставленных элементов и их индексов.
  std::map<size_t,int64_t> help_arr;

  for (size_t i = 0; i < count; ++i) {
    std::string str;
    std::cin >> str;

    if (str == "insert") {
      int64_t value;
      std::cin >> value;
      heap.Insert(value);
      help_arr.insert({i + 1, value});
    } else if (str == "getMin") {
      std::cout << heap.GetMin() << "\n";
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
