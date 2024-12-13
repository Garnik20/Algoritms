#include <iostream>
#include <random>

struct Node {
  int32_t value;
  int32_t priority;
  size_t size;
  Node* left;
  Node* right;

  // Генератор случайных чисел (общий для всех узлов)
  static std::mt19937 gen;
  static std::uniform_int_distribution<int32_t> dist;

  Node(int32_t val)
      : value(val),
        priority(dist(gen)),
        size(1),
        left(nullptr),
        right(nullptr) {}
};

// Инициализация генератора и распределения
std::mt19937 Node::gen(std::random_device{}());
std::uniform_int_distribution<int32_t> Node::dist(0, INT32_MAX);

using NodePtr = Node*;

class Treap {
 public:
  Treap() : root_(nullptr) {}

  ~Treap() { FullDell(root_); }

  // Вставка элемента с проверкой существования
  void Insert(int32_t value) { root_ = Insert(root_, value); }

  // Удаление элемента
  void Deletenode(int32_t value) { root_ = Deletenode(root_, value); }

  // Проверка существования элемента
  bool Exists(int32_t value) { return Exists(root_, value); }

  // Поиск следующего элемента
  int32_t Next(int32_t value) { return Next(root_, value); }

  // Поиск предыдущего элемента
  int32_t Prev(int32_t value) { return Prev(root_, value); }

  // Поиск k-го элемента по порядку
  int32_t Kth(size_t priority) { return Kth(root_, priority); }

 private:
  NodePtr root_;

  // Функция для обновления размера поддерева
  static void UpdateSize(NodePtr node) {
    if (node != nullptr) {
      node->size = 1 + GetSize(node->left) + GetSize(node->right);
    }
  }

  // Функция для получения размера поддерева
  static size_t GetSize(NodePtr node) {
    return node != nullptr ? node->size : 0;
  }

  // Split - разделяет дерево на две части по значению
  void Split(NodePtr node, int32_t value, NodePtr& left, NodePtr& right) {
    if (node == nullptr) {
      left = right = nullptr;
      return;
    }

    if (node->value < value) {
      Split(node->right, value, node->right, right);
      left = node;
    } else {
      Split(node->left, value, left, node->left);
      right = node;
    }

    UpdateSize(node);
  }

  // Merge - сливает два дерева
  NodePtr Merge(NodePtr left, NodePtr right) {
    if (left == nullptr || right == nullptr) {
      return left != nullptr ? left : right;
    }

    if (left->priority > right->priority) {
      left->right = Merge(left->right, right);
      UpdateSize(left);
      return left;
    }
    right->left = Merge(left, right->left);
    UpdateSize(right);
    return right;
  }

  // Вставка нового элемента в дерево
  NodePtr Insert(NodePtr node, int32_t value) {
    if (Exists(node, value)) {
      return node;
    }
    NodePtr new_node = new Node(value);
    NodePtr left;
    NodePtr right;
    Split(node, value, left, right);
    left = Merge(left, new_node);
    return Merge(left, right);
  }

  // Удаление узла с заданным значением
  NodePtr Deletenode(NodePtr node, int32_t value) {
    if (node == nullptr) {
      return nullptr;
    }

    if (node->value == value) {
      NodePtr temp = Merge(node->left, node->right);
      delete node;
      return temp;
    }

    if (value < node->value) {
      node->left = Deletenode(node->left, value);
    } else {
      node->right = Deletenode(node->right, value);
    }

    UpdateSize(node);
    return node;
  }

  // Функция для поиска элемента в дереве
  bool Exists(NodePtr node, int32_t value) {
    if (node == nullptr) {
      return false;
    }
    if (node->value == value) {
      return true;
    }
    if (value < node->value) {
      return Exists(node->left, value);
    }
    return Exists(node->right, value);
  }

  // Функция для поиска следующего элемента (Next)
  static int32_t Next(NodePtr node, int32_t value) {
    int32_t res = -1;
    while (node != nullptr) {
      if (node->value > value) {
        res = node->value;
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return res;
  }

  // Функция для поиска предыдущего элемента (Prev)
  static int32_t Prev(NodePtr node, int32_t value) {
    int32_t res = -1;
    while (node != nullptr) {
      if (node->value < value) {
        res = node->value;
        node = node->right;
      } else {
        node = node->left;
      }
    }
    return res;
  }

  // Функция для поиска k-го элемента по порядку
  int32_t Kth(NodePtr node, size_t prir) {
    if (node == nullptr) {
      return -1;
    }
    size_t left_size = GetSize(node->left);
    if (prir < left_size) {
      return Kth(node->left, prir);
    }
    if (prir == left_size) {
      return node->value;
    }
    return Kth(node->right, prir - left_size - 1);
  }

  void FullDell(NodePtr node) {
    if (node != nullptr) {
      FullDell(node->left);
      FullDell(node->right);
      delete node;
    }
  }
};

void Requests(Treap& tree, std::vector<int32_t>& results) {
  std::string op;
  int32_t element;
  size_t priority;
  while (std::cin >> op) {
    if (op == "Insert") {
      std::cin >> element;
      tree.Insert(element);
    } else if (op == "delete") {
      std::cin >> element;
      tree.Deletenode(element);
    } else if (op == "Exists") {
      std::cin >> element;
      if (tree.Exists(element)) {
        results.emplace_back(-2);
      } else {
        results.emplace_back(-3);
      }
    } else if (op == "Next") {
      std::cin >> element;
      int32_t result = tree.Next(element);
      results.emplace_back(result);
    } else if (op == "Prev") {
      std::cin >> element;
      int32_t result = tree.Prev(element);
      results.emplace_back(result);
    } else if (op == "Kth") {
      std::cin >> priority;
      int32_t result = tree.Kth(priority);
      results.emplace_back(result);
    }
  }
}

void Print(const std::vector<int32_t>& results) {
  for (const int32_t& item : results) {
    if (item == -1) {
      std::cout << "none\n";
    } else if (item == -2) {
      std::cout << "true\n";
    } else if (item == -3) {
      std::cout << "false\n";
    } else {
      std::cout << item << "\n";
    }
  }
}

int main() {
  Treap tree;
  std::vector<int32_t> results;

  Requests(tree, results);

  Print(results);

  return 0;
}
