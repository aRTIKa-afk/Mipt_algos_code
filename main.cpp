#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Node {
  int key;
  int value;
  Node* left = nullptr;
  Node* right = nullptr;
  Node(int build_key, int build_value)
      : key(build_key), value(build_value), left(nullptr), right(nullptr) {}
};

Node* Create(std::vector<std::pair<int, int>>& arr, int left_dot,
             int right_dot) {
  if (right_dot < left_dot) {
    return nullptr;
  }
  int middle_dot = (left_dot + right_dot) / 2;
  Node* result = new Node(arr[middle_dot].first, arr[middle_dot].second);
  result->left = Create(arr, left_dot, middle_dot - 1);
  result->right = Create(arr, middle_dot + 1, right_dot);
  return result;
}

void FreeTree(Node* root) {
  if (root == nullptr) {
    return;
  }
  FreeTree(root->left);
  FreeTree(root->right);
  delete root;
}

int Find(Node* root, int key) {
  if (root == nullptr) {
    return -1;
  }
  if (root->key == key) {
    return root->value;
  }
  if (root->key < key) {
    return Find(root->right, key);
  }
  return Find(root->left, key);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int in_n;
  std::cin >> in_n;
  std::vector<std::pair<std::string, std::string>> login_to_password(in_n);
  std::vector<std::pair<std::string, std::string>> password_to_login(in_n);
  std::vector<std::pair<int, int>> login_to_password_like_ind(in_n);
  std::vector<std::pair<int, int>> password_to_login_like_ind(in_n);
  std::vector<std::string> logins_and_passwords;
  for (int i = 0; i < in_n; i++) {
    std::cin >> login_to_password[i].first;
    std::cin >> login_to_password[i].second;
    password_to_login[i].first = login_to_password[i].second;
    password_to_login[i].second = login_to_password[i].first;
    logins_and_passwords.push_back(login_to_password[i].first);
    logins_and_passwords.push_back(login_to_password[i].second);
  }
  std::sort(logins_and_passwords.begin(), logins_and_passwords.end());
  logins_and_passwords.resize(
      std::unique(logins_and_passwords.begin(), logins_and_passwords.end()) -
      logins_and_passwords.begin());
  for (int i = 0; i < in_n; i++) {
    login_to_password_like_ind[i].first =
        std::lower_bound(logins_and_passwords.begin(),
                         logins_and_passwords.end(),
                         login_to_password[i].first) -
        logins_and_passwords.begin();
    login_to_password_like_ind[i].second =
        std::lower_bound(logins_and_passwords.begin(),
                         logins_and_passwords.end(),
                         login_to_password[i].second) -
        logins_and_passwords.begin();
    password_to_login_like_ind[i].first =
        std::lower_bound(logins_and_passwords.begin(),
                         logins_and_passwords.end(),
                         password_to_login[i].first) -
        logins_and_passwords.begin();
    password_to_login_like_ind[i].second =
        std::lower_bound(logins_and_passwords.begin(),
                         logins_and_passwords.end(),
                         password_to_login[i].second) -
        logins_and_passwords.begin();
  }
  std::sort(login_to_password_like_ind.begin(),
            login_to_password_like_ind.end());
  std::sort(password_to_login_like_ind.begin(),
            password_to_login_like_ind.end());
  Node* root_login_to_password =
      Create(login_to_password_like_ind, 0, in_n - 1);
  Node* root_password_to_login =
      Create(password_to_login_like_ind, 0, in_n - 1);
  int in_q;
  std::cin >> in_q;
  for (int i = 0; i < in_q; i++) {
    std::string query;
    std::cin >> query;
    int index_query = std::lower_bound(logins_and_passwords.begin(),
                                       logins_and_passwords.end(), query) -
                      logins_and_passwords.begin();
    int result = Find(root_login_to_password, index_query);
    if (result == -1) {
      result = Find(root_password_to_login, index_query);
    }
    std::cout << logins_and_passwords[result] << '\n';
  }

  FreeTree(root_login_to_password);
  FreeTree(root_password_to_login);
  return 0;
}