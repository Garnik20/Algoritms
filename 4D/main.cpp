#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

class SparseTable {
 private:
  std::vector<std::vector<int>> table_;
  std::vector<std::vector<int>> second_;
  std::vector<int> log_;

 public:
  SparseTable(const std::vector<int>& arr) {
    int count = arr.size();
    int max_size = log2(count) + 1;

    log_.resize(count + 1);
    log_[1] = 0;
    for (int i = 2; i <= count; ++i) {
      log_[i] = log_[i / 2] + 1;
    }

    table_.resize(max_size, std::vector<int>(count));
    second_.resize(max_size, std::vector<int>(count, INT_MAX));

    for (int i = 0; i < count; ++i) {
      table_[0][i] = arr[i];
    }

    for (int j = 1; j < max_size; ++j) {
      for (int i = 0; i + (1 << j) <= count; ++i) {
        int left_min = table_[j - 1][i];
        int right_min = table_[j - 1][i + (1 << (j - 1))];

        table_[j][i] = std::min(left_min, right_min);

        std::vector<int> candidates = {left_min, right_min, second_[j - 1][i],
                                  second_[j - 1][i + (1 << (j - 1))]};
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()),
                         candidates.end());

        second_[j][i] = (candidates.size() > 1) ? candidates[1] : INT_MAX;
      }
    }
  }

  int SecondMin(int start, int finish) {
    int range = finish - start + 1;
    int elem = log_[range];

    int left_min = table_[elem][start];
    int right_min = table_[elem][finish - (1 << elem) + 1];

    std::vector<int> candidates = {left_min, right_min, second_[elem][start],
                              second_[elem][finish - (1 << elem) + 1]};
    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()),
                     candidates.end());

    return (candidates.size() > 1) ? candidates[1] : INT_MAX;
  }
};

void Input(std::vector<int>& arr, std::vector<std::pair<int, int>>& requests) {
  int count;
  int reqs;
  std::cin >> count >> reqs;
  arr.resize(count);
  requests.resize(reqs);
  for (int i = 0; i < count; ++i) {
    std::cin >> arr[i];
  }
  for (int i = 0; i < reqs; ++i) {
    int start;
    int finish;
    std::cin >> start >> finish;
    --start;
    --finish;
    requests[i] = {start, finish};
  }
}

void Solver(SparseTable& table, std::vector<std::pair<int, int>>& requests) {
  for (auto item : requests) {
    std::cout << table.SecondMin(item.first, item.second) << "\n";
  }
}

int main() {
  std::vector<int> arr;
  std::vector<std::pair<int, int>> requests;

  Input(arr, requests);

  SparseTable table(arr);

  Solver(table, requests);

  return 0;
}
