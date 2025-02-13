#include <iostream>
#include <vector>

int main() {
  int num;
  int max_wieght;
  std::cin >> num >> max_wieght;
  std::vector<int> wieghts(num + 1);
  std::vector<int> costs(num + 1);
  for (int i = 1; i <= num; ++i) {
    std::cin >> wieghts[i];
  }
  for (int i = 1; i <= num; ++i) {
    std::cin >> costs[i];
  }

  std::vector<std::vector<int>> dp_table(num + 1,
                                         std::vector<int>(max_wieght + 1, 0));
  for (int i = 1; i <= num; ++i) {
    for (int j = 0; j <= max_wieght; ++j) {
      dp_table[i][j] = dp_table[i - 1][j];
      if (j >= wieghts[i]) {
        dp_table[i][j] = std::max(dp_table[i][j],
                                  dp_table[i - 1][j - wieghts[i]] + costs[i]);
      }
    }
  }

  std::vector<int> result;
  int j = max_wieght;
  for (int i = num; i >= 1; --i) {
    if (dp_table[i][j] != dp_table[i - 1][j]) {
      result.push_back(i);
      j -= wieghts[i];
    }
  }
  for (int i = result.size() - 1; i >= 0; --i) {
    std::cout << result[i] << '\n';
  }
}
