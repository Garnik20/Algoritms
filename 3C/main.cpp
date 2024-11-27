#include <iostream>
#include <string>
#include <vector>

struct Node {
  std::string key;
  std::string value;
  Node* left;
  Node* right;
  Node(const std::string& key, const std::string& val)
      : key(key), value(val), left(nullptr), right(nullptr) {}
};

class SplayTree {
 private:
  Node* root_;

  // Правый поворот
  static Node* RightRot(Node* node) {
    Node* node_l = node->left;
    node->left = node_l->right;
    node_l->right = node;
    return node_l;
  }

  // Левый поворот
  static Node* LeftRot(Node* node) {
    Node* node_r = node->right;
    node->right = node_r->left;
    node_r->left = node;
    return node_r;
  }

  // Splay: перемещает узел к корню дерева
  Node* Splay(Node* root, const std::string& key) {
    // Если дерево пусто
    if (root == nullptr || key == root->key) { 
      return root;
    }

    // Ключ находится в левом поддереве
    if (key < root->key) {
      // Если левое поддерево пусто
      if (root->left == nullptr) {
        return root;
      }
      // Zig-Zig левый левый
      if (key < root->left->key) {
        // Делаем сплей для левой ветки левой части
        root->left->left = Splay(root->left->left, key);

        // Потом правый приворот
        root = RightRot(root);
      }
      // Zig-Zag левый правый
      else if (key > root->left->key) {
        // Делаем сплей для правой ветки левой части
        root->left->right = Splay(root->left->right, key);

        // Потом левый приворот если он не пуст
        if (root->left->right) root->left = LeftRot(root->left);
      }

      // Вконце если не пуст левое поддерево делаем правый приворот
      return RightRot(root);
    }
    // Ключ находится в правом поддереве

    // Если правое поддерево пусто
    if (root->right == nullptr) {
      return root;
    }
    // Zig-Zig правый правый
    if (key > root->right->key) {
    // Делаем сплей для правой ветки правой части
    root->right->right = Splay(root->right->right, key);

    // Потом левый приворот
    root = LeftRot(root);
    }
    // Zig-Zag правый левый
    else if (key < root->right->key) {
    // Делаем сплей для левой ветки правой части
    root->right->left = Splay(root->right->left, key);

    // Потом правый приворот если он не пуст
    if (root->right->left != nullptr) {
      root->right = RightRot(root->right);
    }
    }
    
    // Вконце если не пуст правое поддерево делаем левый приворот
    return LeftRot(root);
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
  void Insert(const std::string& key, const std::string& value) {
    // Если дерево пустое, просто добавляем новый узел в корень
    if (root_ == nullptr) {
      root_ = new Node(key, value);
      return;
    }

    Node* parent = nullptr;
    Node* current = root_;

    // Поиск подходящего места для вставки нового узла
    while (current != nullptr) {
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
    Node* new_node = new Node(key, value);

    // Вставляем новый узел на нужное место
    if (key < parent->key) {
      parent->left = new_node;
    } else {
      parent->right = new_node;
    }

    // Выполняем splay для перемещения нового узла в корень
    root_ = Splay(root_, key);
  }

  // Поиск значения по ключу
  std::string Find(const std::string& key) {
    // Перемешаем пару по значению key в корень
    root_ = Splay(root_, key);

    // Выведем значение
    return root_->value;
  }
};

void Input(size_t count, SplayTree& tree) {
  // Чтение пар
  for (size_t i = 0; i < count; ++i) {
    std::string nickname;
    std::string car;
    std::cin >> nickname >> car;
    tree.Insert(nickname, car);
    tree.Insert(car, nickname);
  }
}

void Requests(size_t reqs, SplayTree& tree, std::vector<std::string>& results) {
  // Обработка запросов
  for (size_t i = 0; i < reqs; ++i) {
    std::string query;
    std::cin >> query;

    // Ишем по имени
    std::string result = tree.Find(query);
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
  SplayTree tree;

  Input(count, tree);
  
  size_t reqs;
  std::cin >> reqs;
  std::vector<std::string> results(reqs);

  Requests(reqs, tree, results);

  Output(results);

  return 0;
}
