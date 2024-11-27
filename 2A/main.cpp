#include <iostream>
#include <string>
#include <vector>

template <typename T, typename Comparator = std::less<T>>
class MinHeap {
 private:
  std::vector<T> heap_;  // Хранилище элементов кучи
  Comparator comp_;      // Экземпляр компаратора

  // Функция SiftUp поднимает элемент вверх по куче
  void SiftUp(size_t index) {
    while (index > 0 && comp_(heap_[(index - 1) / 2], heap_[index])) {
      std::swap(heap_[index], heap_[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

  // Функция MinOfSons находит минимального из двух дочерних узлов
  size_t MinOfSons(size_t index) {
    size_t left_son = index * 2 + 1;
    size_t right_son = index * 2 + 2;
    size_t best = index;

    if (left_son < heap_.size() && comp_(heap_[best], heap_[left_son])) {
      best = left_son;
    }
    if (right_son < heap_.size() && comp_(heap_[best], heap_[right_son])) {
      best = right_son;
    }
    return best;
  }

  // Функция SiftDown опускает элемент вниз по куче
  void SiftDown(size_t index) {
    size_t best = MinOfSons(index);
    while (index != best) {
      std::swap(heap_[index], heap_[best]);
      index = best;
      best = MinOfSons(index);
    }
  }

 public:
  // Конструктор с возможностью передачи пользовательского компаратора
  explicit MinHeap(Comparator comp = Comparator()) : comp_(comp) {}

  void Insert(T value) {
    heap_.push_back(value);
    SiftUp(heap_.size() - 1);
  }

  // Метод GetMin возвращает минимальный элемент
  T GetMin() { return heap_[0]; }

  // Метод ExtractMin удаляет минимальный элемент
  void ExtractMin() {
    std::swap(heap_[0], heap_[heap_.size() - 1]);
    heap_.pop_back();
    if (!heap_.empty()) {
      SiftDown(0);
    }
  }

  // Метод DecreaseKey уменьшает значение элемента
  void DecreaseKey(T value, T det) {
    size_t index = 0;
    while (index < heap_.size() && heap_[index] != value) {
      ++index;
    }
    if (index < heap_.size()) {
      heap_[index] -= det;  // Уменьшаем значение
      SiftUp(index);  // Поднимаем элемент, чтобы восстановить кучу
    }
  }
};

// Функция для вывода
template <typename T>
void Print(std::vector<T>& result) {
  for (T& item : result) {
    std::cout << item << "\n";
  }
}

// Функция обработки запросов
template <typename T, typename Comparator>
void Requests(MinHeap<T, Comparator>& heap, size_t count,
              std::vector<T>& help_arr, std::vector<T>& result) {
  for (size_t i = 0; i < count; ++i) {
    std::string command;
    std::cin >> command;

    if (command == "insert") {
      T value;
      std::cin >> value;
      heap.Insert(value);
      help_arr[i + 1] = value;
    } else if (command == "getMin") {
      result.emplace_back(heap.GetMin());
    } else if (command == "extractMin") {
      heap.ExtractMin();
    } else if (command == "decreaseKey") {
      size_t index;
      T det;
      std::cin >> index >> det;
      heap.DecreaseKey(help_arr[index], det);
      help_arr[index] -= det;
    }
  }
}

// Основная функция
int main() {
  MinHeap<int64_t, std::less<int64_t>> heap;
  size_t count;
  std::cin >> count;

  std::vector<int64_t> help_arr(count + 1);
  std::vector<int64_t> result;

  Requests(heap, count, help_arr, result);

  Print(result);
}
