#include <deque>
#include <iostream>

int main() {
  int64_t in_num;
  std::cin >> in_num;
  std::deque<int64_t> first_half;
  std::deque<int64_t> second_half;
  char input_command;
  for (int32_t i = 0; i < in_num; i++) {
    std::cin >> input_command;
    if (input_command == '+') {
      int64_t input;
      std::cin >> input;
      if (first_half.size() > second_half.size()) {
        second_half.push_back(input);
      } else {
        second_half.push_back(input);
        first_half.push_back(second_half.front());
        second_half.pop_front();
      }
    } else if (input_command == '*') {
      int64_t input;
      std::cin >> input;
      if (first_half.size() > second_half.size()) {
        second_half.push_front(input);
      } else {
        first_half.push_back(input);
      }
    } else {
      std::cout << first_half.front() << "\n";
      first_half.pop_front();
      if (second_half.size() > first_half.size()) {
        first_half.push_back(second_half.front());
        second_half.pop_front();
      }
    }
  }
}
