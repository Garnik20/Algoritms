#include <iostream>
#include <vector>

const int32_t kHex = 1000000000;

struct AVLNode {
  int32_t key;
  int32_t height;
  AVLNode *left;
  AVLNode *right;
  AVLNode(int32_t new_key)
      : key(new_key), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
 public:
  AVLTree() : root_(nullptr) {}
  
  ~AVLTree() { FreeNode(root_); }

  // Добавление ключа в дерево
  void Add(int32_t key) { root_ = Insert(root_, key); }

  // Поиск следующего элемента, не меньшего key
  int32_t Next(int32_t key) {
    AVLNode *result = FindNext(root_, key);
    return result != nullptr ? result->key : -1;
  }

 private:
  AVLNode *root_;

  // Получение высоты узла
  static int32_t GetHeight(AVLNode *node) {
    return node != nullptr ? node->height : 0;
  }

  // Освобождение памяти узла
  void FreeNode(AVLNode* node) {
    if (node != nullptr) {
      FreeNode(node->left);
      FreeNode(node->right);
      delete node;
    }
  }

  // Обновление высоты узла
  static void UpdateHeight(AVLNode* node) {
    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
  }

  // Баланс узла
  static int32_t GetBalance(AVLNode* node) {
    return node != nullptr ? GetHeight(node->left) - GetHeight(node->right) : 0;
  }

  // Правый поворот
  static AVLNode* RotateRight(AVLNode* node) {
    AVLNode *node_l = node->left;
    AVLNode *node_lr = node_l->right;
    node_l->right = node;
    node->left = node_lr;
    UpdateHeight(node);
    UpdateHeight(node_l);
    return node_l;
  }

  // Левый поворот
  static AVLNode* RotateLeft(AVLNode* node) {
    AVLNode *node_r = node->right;
    AVLNode *node_rl = node_r->left;
    node_r->left = node;
    node->right = node_rl;
    UpdateHeight(node);
    UpdateHeight(node_r);
    return node_r;
  }

  // Вставка элемента с балансировкой
  AVLNode* Insert(AVLNode* node, int32_t key) {
    if (node == nullptr) {
      return new AVLNode(key);
    }
    if (key < node->key) {
      node->left = Insert(node->left, key);
    } else if (key > node->key) {
      node->right = Insert(node->right, key);
    } else {
      return node;  // Если ключ уже существует, не добавляем его снова
    }
    UpdateHeight(node);
    int32_t balance = GetBalance(node);

    // LL
    if (balance > 1 && key < node->left->key) {
      return RotateRight(node);
    }
    // RR
    if (balance < -1 && key > node->right->key) {
      return RotateLeft(node);
    }
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
  static AVLNode* FindNext(AVLNode* node, int32_t key) {
    AVLNode* res = nullptr;
    while (node != nullptr) {
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

void Requests(AVLTree& avl_tree, size_t count, std::vector<int32_t>& results) {
  int32_t last_y = 0;
  for (size_t i = 0; i < count; ++i) {
    char operation;
    int32_t value;
    std::cin >> operation >> value;

    if (operation == '+') {
      if (last_y == 0 || (results.empty() || results.back() == -1)) {
        avl_tree.Add(value);
      } else {
        avl_tree.Add((value + last_y) % kHex);
      }
      last_y = 0;
    } else if (operation == '?') {
      last_y = avl_tree.Next(value);
      results.push_back(last_y);
    }
  }
}

int main() {
  size_t count;
  std::cin >> count;
  AVLTree avl_tree;
  std::vector<int32_t> results;

  Requests(avl_tree, count, results);

  for (int32_t& result : results) {
    std::cout << result << "\n";
  }
  return 0;
}
