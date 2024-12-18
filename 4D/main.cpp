#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

class SparseTable {
 private:
  std::vector<std::vector<int32_t>> table_;
  std::vector<std::vector<int32_t>> second_;
  std::vector<int32_t> log_;

 public:
  SparseTable(const std::vector<int32_t>& arr) {
    int32_t count = arr.size();
    int32_t max_size = log2(count) + 1;

    log_.resize(count + 1);
    log_[1] = 0;
    for (int32_t i = 2; i <= count; ++i) {
      log_[i] = log_[i / 2] + 1;
    }

    table_.resize(max_size, std::vector<int32_t>(count));
    second_.resize(max_size, std::vector<int32_t>(count, INT_MAX));

    for (int32_t i = 0; i < count; ++i) {
      table_[0][i] = arr[i];
    }

    for (int32_t j = 1; j < max_size; ++j) {
      for (int32_t i = 0; i + (1 << j) <= count; ++i) {
        int32_t left_min = table_[j - 1][i];
        int32_t right_min = table_[j - 1][i + (1 << (j - 1))];

        table_[j][i] = std::min(left_min, right_min);

        std::vector<int32_t> candidates = {left_min, right_min,
                                           second_[j - 1][i],
                                           second_[j - 1][i + (1 << (j - 1))]};
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()),
                         candidates.end());

        second_[j][i] = (candidates.size() > 1) ? candidates[1] : INT_MAX;
      }
    }
  }

  int32_t SecondMin(int32_t start, int32_t finish) {
    int32_t range = finish - start + 1;
    int32_t elem = log_[range];

    int32_t left_min = table_[elem][start];
    int32_t right_min = table_[elem][finish - (1 << elem) + 1];

    std::vector<int32_t> candidates = {left_min, right_min,
                                       second_[elem][start],
                                       second_[elem][finish - (1 << elem) + 1]};
    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()),
                     candidates.end());

    return (candidates.size() > 1) ? candidates[1] : INT_MAX;
  }
};

void Input(std::vector<int32_t>& arr,
           std::vector<std::pair<int32_t, int32_t>>& requests) {
  int32_t count;
  int32_t reqs;
  std::cin >> count >> reqs;
  arr.resize(count);
  requests.resize(reqs);
  for (int32_t i = 0; i < count; ++i) {
    std::cin >> arr[i];
  }
  for (int32_t i = 0; i < reqs; ++i) {
    int32_t start;
    int32_t finish;
    std::cin >> start >> finish;
    --start;
    --finish;
    requests[i] = {start, finish};
  }
}

void Solver(SparseTable& table,
            std::vector<std::pair<int32_t, int32_t>>& requests) {
  for (auto item : requests) {
    std::cout << table.SecondMin(item.first, item.second) << "\n";
  }
}

int main() {
  std::vector<int32_t> arr;
  std::vector<std::pair<int32_t, int32_t>> requests;

  Input(arr, requests);

  SparseTable table(arr);

  Solver(table, requests);

  return 0;
}
