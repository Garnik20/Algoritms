#include <iostream>
#include <map>
#include <string>
#include <vector>

// Класс min_heap - минимальнaq кучa
class min_heap {
private:
  std::vector<long long> heap;

  // Функция sift_up поднимает элемент вверх по куче
  void sift_up(size_t index) {
    while (index > 0 && heap[index] < heap[(index - 1) / 2]) {
      std::swap(heap[index], heap[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

  // Функция min_of_sons находит минимального из двух дочерних узлов
  size_t min_of_sons(size_t index) {
    size_t left_son = index * 2 + 1;  // Индекс левого сына.
    size_t right_son = index * 2 + 2; // Индекс правого сына.
    size_t smallest = index;

    if (left_son < heap.size() && heap[left_son] < heap[smallest]) {
      smallest = left_son;
    }
    if (right_son < heap.size() && heap[right_son] < heap[smallest]) {
      smallest = right_son;
    }
    return smallest;
  }

  // Функция sift_down опускает элемент вниз по куче
  void sift_down(size_t i) {
    size_t smallest = min_of_sons(i);
    while (i != smallest) {
      std::swap(heap[i], heap[smallest]);
      i = smallest;
      smallest = min_of_sons(i);
    }
  }

public:
  void insert(long long value) {
    heap.push_back(value); // Добавляем элемент в конец кучи.
    sift_up(heap.size() - 1); // Восстанавливаем свойства кучи.
  }

  // Метод getMin возвращает минимальный элемент из кучи.
  long long getMin() { return heap[0]; }

  // Метод extractMin удаляет минимальный элемент из кучи.
  void extractMin() {
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    if (!heap.empty()) {
      sift_down(0);
    }
  }

  // Метод decreaseKey уменьшает значение элемента в куче.
  void decreaseKey(long long value, long long r) {
    // Находим индекс элемента с указанным значением.
    size_t i = 0;
    while (i < heap.size() && heap[i] != value) {
      ++i;
    }
    // Уменьшаем значение и поднимаем его, чтобы сохранить структуру кучи.
    heap[i] -= r;
    sift_up(i);
  }
};

int main() {
  min_heap heap;
  size_t count;
  std::cin >> count;
  // Словарь для хранения вставленных элементов и их индексов.
  std::map<size_t, long long> help_arr;

  for (size_t i = 0; i < count; ++i) {
    std::string str;
    std::cin >> str;

    if (str == "insert") {
      long long value;
      std::cin >> value;
      heap.insert(value);
      help_arr.insert({i + 1, value});
    } else if (str == "getMin") {
      std::cout << heap.getMin() << "\n";
    } else if (str == "extractMin") {
      heap.extractMin();
    } else if (str == "decreaseKey") {
      long long det;
      size_t ind;
      std::cin >> ind >> det; // Считываем индекс и значение для уменьшения.
      heap.decreaseKey(help_arr[ind], det); // Уменьшаем значение в куче.
      help_arr[ind] -= det; // Обновляем значение в словаре.
    }
  }
}
