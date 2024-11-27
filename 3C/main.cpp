#include <iostream>
#include <string>
#include <vector>

struct Node {
  std::string key;
  std::string value;
  Node* left;
  Node* right;
  Node(const std::string& k, const std::string& v)
      : key(k), value(v), left(nullptr), right(nullptr) {}
};

class SplayTree {
 private:
  Node* root_;

  // Правый поворот
  Node* RightRot(Node* node) {
    Node* node_l = node->left;
    node->left = node_l->right;
    node_l->right = node;
    return node_l;
  }

  // Левый поворот
  Node* LeftRot(Node* node) {
    Node* node_r = node->right;
    node->right = node_r->left;
    node_r->left = node;
    return node_r;
  }

  // Splay: перемещает узел к корню дерева
  Node* Splay(Node* root_, const std::string& key) {
    // Если дерево пусто
    if (!root_ || key == root_->key) return root_;

    // Ключ находится в левом поддереве
    if (key < root_->key) {
      // Если левое поддерево пусто
      if (!root_->left) return root_;

      // Zig-Zig левый левый
      if (key < root_->left->key) {
        // Делаем сплей для левой ветки левой части
        root_->left->left = Splay(root_->left->left, key);

        // Потом правый приворот
        root_ = RightRot(root_);
      }
      // Zig-Zag левый правый
      else if (key > root_->left->key) {
        // Делаем сплей для правой ветки левой части
        root_->left->right = Splay(root_->left->right, key);

        // Потом левый приворот если он не пуст
        if (root_->left->right) root_->left = LeftRot(root_->left);
      }

      // Вконце если не пуст левое поддерево делаем правый приворот
      return RightRot(root_);
    }
    // Ключ находится в правом поддереве

    // Если правое поддерево пусто
    if (!root_->right) return root_;

    // Zig-Zig правый правый
    if (key > root_->right->key) {
    // Делаем сплей для правой ветки правой части
    root_->right->right = Splay(root_->right->right, key);

    // Потом левый приворот
    root_ = LeftRot(root_);
    }
    // Zig-Zag правый левый
    else if (key < root_->right->key) {
    // Делаем сплей для левой ветки правой части
    root_->right->left = Splay(root_->right->left, key);

    // Потом правый приворот если он не пуст
    if (root_->right->left) root_->right = RightRot(root_->right);
    }
    
    // Вконце если не пуст правое поддерево делаем левый приворот
    return LeftRot(root_);
  }

 public:
  SplayTree() : root_(nullptr) {}

  ~SplayTree() { FreeNode(root_); }

  // Освобождение памяти узла
  void FreeNode(Node* node) {
    if (node != nullptr) {
      FreeNode(node->left);
      FreeNode(node->right);
      delete node;
    }
  }

  
  // Вставка новой пары
  void insert(const std::string& key, const std::string& value) {
    // Если дерево пустое, просто добавляем новый узел в корень
    if (!root_) {
      root_ = new Node(key, value);
      return;
    }

    Node* parent = nullptr;
    Node* current = root_;

    // Поиск подходящего места для вставки нового узла
    while (current) {
      parent = current;
      if (key < current->key) {
        current = current->left;
      } else if (key > current->key) {
        current = current->right;
      } else {
        // Если ключ уже существует, обновляем значение и выполняем splay
        current->value = value;
        root_ = Splay(root_, key);
        return;
      }
    }

    // Создаем новый узел
    Node* newNode = new Node(key, value);

    // Вставляем новый узел на нужное место
    if (key < parent->key) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }

    // Выполняем splay для перемещения нового узла в корень
    root_ = Splay(root_, key);
  }

  // Поиск значения по ключу
  std::string find(const std::string& key) {
    // Перемешаем пару по значению key в корень
    root_ = Splay(root_, key);

    // Выведем значение
    return root_->value;
  }
};

void Input(size_t count, SplayTree& Tree) {
  // Чтение пар
  for (size_t i = 0; i < count; ++i) {
    std::string nickname;
    std::string car;
    std::cin >> nickname >> car;
    Tree.insert(nickname, car);
    Tree.insert(car, nickname);
  }
}

void Requests(size_t reqs, SplayTree& Tree, std::vector<std::string>& results) {
  // Обработка запросов
  for (size_t i = 0; i < reqs; ++i) {
    std::string query;
    std::cin >> query;

    // Ишем по имени
    std::string result = Tree.find(query);
    results.emplace_back(result);
  }
}

void Output(std::vector<std::string>& results) {
    for(std::string& item : results) {
        std::cout << item << '\n';
    }
}

int main() {
  size_t count;
  std::cin >> count;
  if (count == 0) return 0;
  SplayTree Tree;

  Input(count, Tree);
  
  size_t reqs;
  std::cin >> reqs;
  std::vector<std::string> results(reqs);

  Requests(reqs, Tree, results);

  Output(results);

  return 0;
}
