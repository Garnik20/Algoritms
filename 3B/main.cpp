#include <iostream>
#include <vector>

struct AVLNode {
  int32_t key;
  int32_t height;
  AVLNode *left;
  AVLNode *right;
  AVLNode(int32_t new_key) : key(new_key), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
public:
  AVLTree() : root(nullptr) {}

  // Добавление ключа в дерево
  void Add(int32_t key) { root = Insert(root, key); }

  // Поиск следующего элемента, не меньшего key
  int32_t Next(int32_t key) {
    AVLNode *result = FindNext(root, key);
    return result ? result->key : -1;
  }

private:
  AVLNode *root;

  // Получение высоты узла
  int32_t GetHeight(AVLNode *node) { return node ? node->height : 0; }

  // Обновление высоты узла
  void UpdateHeight(AVLNode *node) {
    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
  }

  // Баланс узла
  int32_t GetBalance(AVLNode *node) {
    return node ? GetHeight(node->left) - GetHeight(node->right) : 0;
  }

  // Правый поворот
  AVLNode *RotateRight(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    UpdateHeight(y);
    UpdateHeight(x);
    return x;
  }

  // Левый поворот
  AVLNode *RotateLeft(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    UpdateHeight(x);
    UpdateHeight(y);
    return y;
  }

  // Вставка элемента с балансировкой
  AVLNode *Insert(AVLNode *node, int32_t key) {
    if (!node)
      return new AVLNode(key);

    if (key < node->key)
      node->left = Insert(node->left, key);
    else if (key > node->key)
      node->right = Insert(node->right, key);
    else
      return node; // Если ключ уже существует, не добавляем его снова

    UpdateHeight(node);
    int32_t balance = GetBalance(node);

    // LL
    if (balance > 1 && key < node->left->key)
      return RotateRight(node);
    // RR
    if (balance < -1 && key > node->right->key)
      return RotateLeft(node);
    // LR
    if (balance > 1 && key > node->left->key) {
      node->left = RotateLeft(node->left);
      return RotateRight(node);
    }
    // RL
    if (balance < -1 && key < node->right->key) {
      node->right = RotateRight(node->right);
      return RotateLeft(node);
    }

    return node;
  }

  // Поиск следующего узла, не меньшего key
  AVLNode *FindNext(AVLNode *node, int32_t key) {
    AVLNode *res = nullptr;
    while (node) {
      if (node->key >= key) {
        res = node;
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return res;
  }
};

void Requests(AVLTree &avl_tree, size_t count, std::vector<int32_t> &results) {
    int32_t last_y = 0;
  for (size_t i = 0; i < count; ++i) {
    char operation;
    int32_t value;
    std::cin >> operation >> value;

    if (operation == '+') {
      if (last_y == 0 || (results.empty() || results.back() == -1)) {
        avl_tree.Add(value);
      } else {
        avl_tree.Add((value + last_y) % 1000000000);
      }
      last_y = 0;
    } else if (operation == '?') {
      last_y = avl_tree.Next(value);
      results.emplace_back(last_y);
    }
  }
}

int main() {
  size_t count;
  std::cin >> count;
  AVLTree avl_tree;
  std::vector<int32_t> results;

  Requests(avl_tree, count, results);

  for (int32_t &result : results) {
    std::cout << result << "\n";
  }

  return 0;
}
