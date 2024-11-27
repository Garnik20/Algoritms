#include <cstdint>
#include <iostream>
#include <vector>

template <typename T, typename Comp = std::less<T>>
class Queue {
 public:
  explicit Queue(Comp comp = Comp()) : comp_(comp) {}

  // Добавление элемента в очередь
  T Enqueue(T num) {
    stack_1_.push_back(num);  // Добавляем элемент в stack_1_
    if (stack_1_min_.empty()) {
      stack_1_min_.push_back(num);  // Если stack_1_min_ пуст
    } else {
      stack_1_min_.push_back(std::min(stack_1_min_.back(), num, comp_));
    }
    return -2;
  }

  // Удаление элемента из начала очереди
  T Dequeue() {
    if (stack_1_.empty() && stack_2_.empty()) {
      return -1;
    }
    if (stack_2_.empty()) {
      Transfer();  // Переносим элементы из stack_1_ в stack_2_
    }
    T res = stack_2_.back();  // Выводим элемент из начала очереди
    stack_2_.pop_back();  // Удаляем его
    stack_2_min_.pop_back();  // Удаляем соответствующий минимум
    return res;
  }

  // Получение элемента из начала очереди без удаления
  T Front() {
    if (stack_1_.empty() && stack_2_.empty()) {
      return -1;
    }
    if (stack_2_.empty()) {
      Transfer();  // Переносим элементы из stack_1_ в stack_2_
    }
    return stack_2_.back();  // Выводим элемент из начала очереди
  }

  // Вывод размера очереди
  T SizeSt() const { return stack_1_.size() + stack_2_.size(); }

  // Очистка очереди
  T Clear() {
    stack_1_.clear();
    stack_2_.clear();
    stack_1_min_.clear();
    stack_2_min_.clear();
    return -2;
  }

  // Получение минимального элемента в очереди
  T Min() {
    if (stack_1_.empty() && stack_2_.empty()) {
      return -1;
    }

    // Выбираем минимальный элемент между stack_1_min_ и stack_2_min_
    if (stack_1_min_.empty()) {
      return stack_2_min_.back();
    }
    if (stack_2_min_.empty()) {
      return stack_1_min_.back();
    }
    return std::min(stack_1_min_.back(), stack_2_min_.back(), comp_);
  }

 private:
  std::vector<T> stack_1_;  // Стек для добавления новых элементов
  std::vector<T> stack_1_min_;  // Стек для отслеживания минимума в stack_1_
  std::vector<T> stack_2_;  // Стек для удаления элементов из очереди
  std::vector<T> stack_2_min_;  // Стек для отслеживания минимума в stack_2_
  Comp comp_;  // Компаратор

  // Перемещает все элементы из stack_1_ в stack_2_
  void Transfer() {
    while (!stack_1_.empty()) {
      T el = stack_1_.back();  // Берем верхний элемент из stack_1_
      stack_2_.emplace_back(el);  // Добавляем его в stack_2_
      stack_1_.pop_back();        // Удаляем из stack_1_
      stack_1_min_.pop_back();  // Удаляем элемент минимума в stack_1_

      // Обновляем stack_2_min_ для корректного отслеживания минимума в stack_2_
      if (stack_2_min_.empty()) {
        stack_2_min_.emplace_back(el);
      } else {
        stack_2_min_.emplace_back(std::min(stack_2_min_.back(), el, comp_));
      }
    }
  }
};

template <typename T>
void Requests(size_t count, Queue<T>& heap, std::vector<T>& results) {
  std::string command;
  for (size_t i = 0; i < count; ++i) {
    std::cin >> command;
    if (command == "enqueue") {
      T element;
      std::cin >> element;
      results.emplace_back(heap.Enqueue(element));
    } else if (command == "front") {
      results.emplace_back(heap.Front());
    } else if (command == "dequeue") {
      results.emplace_back(heap.Dequeue());
    } else if (command == "size") {
      results.emplace_back(heap.SizeSt());
    } else if (command == "min") {
      results.emplace_back(heap.Min());
    } else if (command == "clear") {
      results.emplace_back(heap.Clear());
    }
  }
}

template <typename T>
void Print(const std::vector<T> results) {
  for (const T& item : results) {
    if (item == -2) {
      std::cout << "ok\n";
    } else if (item == -1) {
      std::cout << "error\n";
    } else {
      std::cout << item << "\n";
    }
  }
}

int main() {
  size_t count;
  std::cin >> count;
  Queue<int32_t> heap;
  std::vector<int32_t> results;

  Requests(count, heap, results);

  Print(results);

  return 0;
}
