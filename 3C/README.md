Это реализация splay-дерева, самобалансирующегося бинарного дерева поиска, которое перемещает наиболее часто используемые элементы ближе к корню.Амортизированное время операций O(logn).

Основные методы:
Конструктор: SplayTree()
Создаёт пустое дерево.
Деструктор: ~SplayTree()
Освобождает всю выделенную память, удаляя все узлы дерева.
Insert: void Insert(const std::string& key, const std::string& value)
Вставляет пару ключ-значение в дерево. Если ключ уже существует, обновляет значение и выполняет splay (перемещение узла с этим ключом в корень).
Find: std::string Find(const std::string& key)
Ищет ключ в дереве. Если ключ найден, перемещает узел с этим ключом в корень. Возвращает значение, связанное с ключом.


Приватные методы:
RightRot: static Node* RightRot(Node* node)
Выполняет правый поворот вокруг указанного узла.
LeftRot: static Node* LeftRot(Node* node)
Выполняет левый поворот вокруг указанного узла.
Splay: Node* Splay(Node* root, const std::string& key)
Перемещает узел с заданным ключом к корню дерева, используя операции splay:
Zig-Zig (лево-лево)
Zig-Zag (лево-право)
Zag-Zag (право-право)
Zag-Zig (право-лево)
FreeNode: void FreeNode(Node* node)
Рекурсивно освобождает память для узлов дерева.

Input: void Input(size_t count, SplayTree& tree)
Читает count пар строк (имя и машина) и добавляет их в дерево в обоих направлениях (имя -> машина, машина -> имя).

Requests: void Requests(size_t reqs, SplayTree& tree, std::vector<std::string>& results)
Читает reqs запросов на поиск по ключу и записывает результаты в вектор results.

Output: void Output(std::vector<std::string>& results)
Выводит результаты запросов построчно.