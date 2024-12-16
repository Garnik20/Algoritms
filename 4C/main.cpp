#include <iostream>
#include <vector>

class FenwickTree {
private:
  int16_t cube_size_;
  std::vector<std::vector<std::vector<int64_t>>> fenwick_;

  // Метод для получения младшего установленного бита
  static int16_t Lsb(int16_t x_cord) { return x_cord & -x_cord; }

public:
  // Конструктор
  FenwickTree(int16_t size) : cube_size_(size) {
    fenwick_.resize(
        cube_size_ + 1,
        std::vector<std::vector<int64_t>>(
            cube_size_ + 1, std::vector<int64_t>(cube_size_ + 1, 0)));
  }

  // Обновление значения delta в точке (x_cord, y_cord, z_cord)
  void Update(int16_t x_cord, int16_t y_cord, int16_t z_cord, int64_t delta) {
    for (int16_t i = x_cord + 1; i <= cube_size_; i += Lsb(i)) {
      for (int16_t j = y_cord + 1; j <= cube_size_; j += Lsb(j)) {
        for (int16_t k = z_cord + 1; k <= cube_size_; k += Lsb(k)) {
          fenwick_[i][j][k] += delta;
        }
      }
    }
  }

  // Префиксная сумма от (0, 0, 0) до (x_cord, y_cord, z_cord)
  int64_t PrefixSum(int16_t x_cord, int16_t y_cord, int16_t z_cord) {
    int64_t sum = 0;
    for (int16_t i = x_cord + 1; i > 0; i -= Lsb(i)) {
      for (int16_t j = y_cord + 1; j > 0; j -= Lsb(j)) {
        for (int16_t k = z_cord + 1; k > 0; k -= Lsb(k)) {
          sum += fenwick_[i][j][k];
        }
      }
    }
    return sum;
  }

  // Сумма в области от (x1, y1, z1) до (x2, y2, z2)
  int64_t RangeSum() {
    int16_t x1;
    int16_t y1;
    int16_t z1;
    int16_t x2;
    int16_t y2;
    int16_t z2;
    std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
    return PrefixSum(x2, y2, z2) - (x1 > 0 ? PrefixSum(x1 - 1, y2, z2) : 0) -
           (y1 > 0 ? PrefixSum(x2, y1 - 1, z2) : 0) -
           (z1 > 0 ? PrefixSum(x2, y2, z1 - 1) : 0) +
           (x1 > 0 && y1 > 0 ? PrefixSum(x1 - 1, y1 - 1, z2) : 0) +
           (x1 > 0 && z1 > 0 ? PrefixSum(x1 - 1, y2, z1 - 1) : 0) +
           (y1 > 0 && z1 > 0 ? PrefixSum(x2, y1 - 1, z1 - 1) : 0) -
           (x1 > 0 && y1 > 0 && z1 > 0 ? PrefixSum(x1 - 1, y1 - 1, z1 - 1) : 0);
  }
};

void Requests(std::vector<int64_t> &result, FenwickTree &fenwicktree) {
  while (true) {
    int16_t req;
    std::cin >> req;

    if (req == 1) {
      int16_t x_cord;
      int16_t y_cord;
      int16_t z_cord;
      int64_t delim;
      std::cin >> x_cord >> y_cord >> z_cord >> delim;
      fenwicktree.Update(x_cord, y_cord, z_cord, delim);
    } else if (req == 2) {
      result.emplace_back(fenwicktree.RangeSum());
    } else if (req == 3) {
      break;
    }
  }
}

void Print(const std::vector<int64_t> &result) {
  for (const int64_t kItem : result) {
    std::cout << kItem << '\n';
  }
}

int main() {
  int16_t cube_size;
  std::cin >> cube_size;

  FenwickTree fenwicktree(cube_size);
  std::vector<int64_t> result;

  Requests(result, fenwicktree);

  Print(result);

  return 0;
}
