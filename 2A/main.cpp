#include <iostream>
#include <map>
#include <string>
#include <vector>

// Класс min_heap - минимальнaq кучa
class MinHeap {
 private:
  // Массив кучи
  std::vector<int64_t> heap;

  // Функция sift_up поднимает элемент вверх по куче
  void SiftUp(size_t index) {
    while (index > 0 && heap[index] < heap[(index - 1) / 2]) {
      std::swap(heap[index], heap[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

  // Функция MinOfSons находит минимального из двух дочерних узлов
  size_t MinOfSons(size_t index) {
    size_t left_son = index * 2 + 1;
    size_t right_son = index * 2 + 2;
    size_t smallest = index;

    if (left_son < heap.size() && heap[left_son] < heap[smallest]) {
      smallest = left_son;
    }
    if (right_son < heap.size() && heap[right_son] < heap[smallest]) {
      smallest = right_son;
    }
    return smallest;
  }

  // Функция SiftDown опускает элемент вниз по куче
  void SiftDown(size_t index) {
    size_t smallest = MinOfSons(index);
    while (index != smallest) {
      std::swap(heap[index], heap[smallest]);
      index = smallest;
      smallest = MinOfSons(index);
    }
  }

 public:
  void Insert(int64_t value) {
    heap.push_back(value);  // Добавляем элемент в конец кучи.
    SiftUp(heap.size() - 1);  // Восстанавливаем свойства кучи.
  }

  // Метод getMin возвращает минимальный элемент из кучи.
  int64_t GetMin() { return heap[0]; }

  // Метод extractMin удаляет минимальный элемент из кучи.
  void ExtractMin() {
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    if (!heap.empty()) {
      SiftDown(0);
    }
  }

  // Метод decreaseKey уменьшает значение элемента в куче.
  void DecreaseKey(int64_t value,int64_t det) {
    // Находим индекс элемента с указанным значением.
    size_t count = 0;
    while (count < heap.size() && heap[count] != value) {
      ++count;
    }
    // Уменьшаем значение и поднимаем его, чтобы сохранить структуру кучи.
    heap[count] -= det;
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
