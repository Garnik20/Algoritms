#include <iostream>
#include <vector>

class Queue {
 private:
  // Перемещает все элементы из stack_1 в stack_2
  void Transfer() {
    while (!stack_1.empty()) {
      int el = stack_1.back();  // Берем верхний элемент из stack_1
      stack_2.push_back(el);  // Добавляем его в stack_2
      stack_1.pop_back();     // Удаляем из stack_1
      stack_1_min.pop_back();  // Удаляем элемент минимума в stack_1

      // Обновляем stack_2_min для корректного отслеживания минимума в stack_2
      if (stack_2_min.empty()) {
        stack_2_min.push_back(el);
      } else {
        stack_2_min.push_back(std::min(stack_2_min.back(), el));
      }
    }
  }

 public:
  std::vector<int> stack_1;  // Стек для добавления новых элементов
  std::vector<int> stack_1_min;  // Стек для отслеживания минимума в stack_1
  std::vector<int> stack_2;  // Стек для удаления элементов из очереди
  std::vector<int> stack_2_min;  // Стек для отслеживания минимума в stack_2
  // Добавление элемента в очередь
  void Enqueue(int num) {
    stack_1.push_back(num);  // Добавляем элемент в stack_1
    if (stack_1_min.empty()) {
      stack_1_min.push_back(num);  // Если stack_1_min пуст
    } else {
      stack_1_min.push_back(std::min(stack_1_min.back(), num));
    }
    std::cout << "ok\n";
  }

  // Удаление элемента из начала очереди
  void Dequeue() {
    if (stack_1.empty() && stack_2.empty()) {
      std::cout << "error\n";
      return;
    }
    if (stack_2.empty()) {
      Transfer();  // Переносим элементы из stack_1 в stack_2
    }
    std::cout << stack_2.back() << '\n';  // Выводим элемент из начала очереди
    stack_2.pop_back();  // Удаляем его
    stack_2_min.pop_back();  // Удаляем соответствующий минимум
  }

  // Получение элемента из начала очереди без удаления
  void Front() {
    if (stack_1.empty() && stack_2.empty()) {
      std::cout << "error\n";
      return;
    }
    if (stack_2.empty()) {
      Transfer();  // Переносим элементы из stack_1 в stack_2
    }
    std::cout << stack_2.back() << '\n';  // Выводим элемент из начала очереди
  }

  // Вывод размера очереди
  void SizeSt() const { std::cout << stack_1.size() + stack_2.size() << '\n'; }

  // Очистка очереди
  void Clear() {
    stack_1.clear();
    stack_2.clear();
    stack_1_min.clear();
    stack_2_min.clear();
    std::cout << "ok\n";
  }

  // Получение минимального элемента в очереди
  void Min() {
    if (stack_1.empty() && stack_2.empty()) {
      std::cout << "error\n";
      return;
    }

    // Выбираем минимальный элемент между stack_1_min и stack_2_min
    int min_queue;
    if (stack_1_min.empty()) {
      min_queue = stack_2_min.back();
    } else if (stack_2_min.empty()) {
      min_queue = stack_1_min.back();
    } else {
      min_queue = std::min(stack_1_min.back(), stack_2_min.back());
    }
    std::cout << min_queue << '\n';
  }
};

int main() {
  int count;
  std::cin >> count;
  Queue heap;
  std::string command;

  for (int i = 0; i < count; ++i) {
    std::cin >> command;
    if (command == "enqueue") {
      int element;
      std::cin >> element;
      heap.Enqueue(element);
    } else if (command == "front") {
      heap.Front();
    } else if (command == "dequeue") {
      heap.Dequeue();
    } else if (command == "size") {
      heap.SizeSt();
    } else if (command == "min") {
      heap.Min();
    } else if (command == "clear") {
      heap.Clear();
    }
  }

  return 0;
}
