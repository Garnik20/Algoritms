#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class SparseTable {
 private:
  vector<vector<int>> table_;
  vector<vector<int>> second_;
  vector<int> log_;

 public:
  SparseTable(const vector<int>& arr) {
    int count = arr.size();
    int max_size = log2(count) + 1;

    log_.resize(count + 1);
    log_[1] = 0;
    for (int i = 2; i <= count; ++i) {
      log_[i] = log_[i / 2] + 1;
    }

    table_.resize(max_size, vector<int>(count));
    second_.resize(max_size, vector<int>(count, INT_MAX));

    for (int i = 0; i < count; ++i) {
      table_[0][i] = arr[i];
    }

    for (int j = 1; j < max_size; ++j) {
      for (int i = 0; i + (1 << j) <= count; ++i) {
        int leftMin = table_[j - 1][i];
        int rightMin = table_[j - 1][i + (1 << (j - 1))];

        table_[j][i] = min(leftMin, rightMin);

        vector<int> candidates = {leftMin, rightMin, second_[j - 1][i],
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
    int j = log_[range];

    int leftMin = table_[j][start];
    int rightMin = table_[j][finish - (1 << j) + 1];

    vector<int> candidates = {leftMin, rightMin, second_[j][start],
                              second_[j][finish - (1 << j) + 1]};
    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()),
                     candidates.end());

    return (candidates.size() > 1) ? candidates[1] : INT_MAX;
  }
};

void Input(vector<int>& arr, vector<pair<int, int>>& requests) {
  int count, reqs;
  cin >> count >> reqs;
  arr.resize(count);
  requests.resize(reqs);
  for (int i = 0; i < count; ++i) {
    cin >> arr[i];
  }
  for (int i = 0; i < reqs; ++i) {
    int start, finish;
    cin >> start >> finish;
    --start;
    --finish;
    requests[i] = {start, finish};
  }
}

void Solver(SparseTable& table, vector<pair<int, int>>& requests) {
  for (auto item : requests) {
    cout << table.SecondMin(item.first, item.second) << "\n";
  }
}

int main() {
  int reqs;
  vector<int> arr;
  vector<pair<int, int>> requests;

  Input(arr, requests);

  SparseTable table(arr);

  Solver(table, requests);

  return 0;
}
