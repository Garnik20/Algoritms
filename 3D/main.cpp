#include <iostream>
#include <random>

class Treap {
 private:
  struct Node {
    int32_t value;
    int32_t priority;
    size_t size;
    Node* left;
    Node* right;

    Node(int32_t val)
        : value(val), priority(rand()), size(1), left(nullptr), right(nullptr) {}
  };

  Node* root_;

  // Функция для обновления размера поддерева
  static void UpdateSize(Node* node) {
    if (node != nullptr) {
      node->size = 1 + GetSize(node->left) + GetSize(node->right);
    }
  }

  // Функция для получения размера поддерева
  static size_t GetSize(Node* node) { return node != nullptr ? node->size : 0; }

  // Split - разделяет дерево на две части по значению
  void Split(Node* node, int32_t value, Node*& left, Node*& right) {
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
  Node* Merge(Node* left, Node* right) {
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
  Node* Insert(Node* node, int value) {
    if (Exists(node, value)) {
      return node;
    }
    Node* new_node = new Node(value);
    Node *left;
    Node *right;
    Split(node, value, left, right);
    left = Merge(left, new_node);
    return Merge(left, right);
  }

  // Удаление узла с заданным значением
  Node* Deletenode(Node* node, int32_t value) {
    if (node == nullptr) {
      return nullptr;
    }

    if (node->value == value) {
      Node* temp = Merge(node->left, node->right);
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
  bool Exists(Node* node, int32_t value) {
    if (node  == nullptr) {
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
  static int32_t Next(Node* node, int32_t value) {
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
  static int32_t Prev(Node* node, int32_t value) {
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
  int32_t Kth(Node* node, size_t prir) {
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

  void FullDell(Node* node) {
    if (node != nullptr) {
      FullDell(node->left);
      FullDell(node->right);
      delete node;
    }
  }

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
  int32_t Kth(size_t prir) { return Kth(root_, prir); }
};

void Requests(Treap& tree, std::vector<int32_t>& results) {
  std::string op;
  int32_t x;
  size_t prir;
  while (std::cin >> op) {
    if (op == "Insert") {
      std::cin >> x;
      tree.Insert(x);
    } else if (op == "delete") {
      std::cin >> x;
      tree.Deletenode(x);
    } else if (op == "Exists") {
      std::cin >> x;
      if (tree.Exists(x)) {
        results.emplace_back(-2);
      } else {
        results.emplace_back(-3);
      }
    } else if (op == "Next") {
      std::cin >> x;
      int32_t result = tree.Next(x);
      results.emplace_back(result);
    } else if (op == "Prev") {
      std::cin >> x;
      int32_t result = tree.Prev(x);
      results.emplace_back(result);
    } else if (op == "Kth") {
      std::cin >> prir;
      int32_t result = tree.Kth(prir);
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
