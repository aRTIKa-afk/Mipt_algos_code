#include <iostream>
const int cMod = 1000000000;

struct Node {
  int key;
  int height;
  Node* left;
  Node* right;
  Node(int value) : key(value), height(1), left(nullptr), right(nullptr) {}
};

int GetHeight(Node* node) { return node != nullptr ? node->height : 0; }

int GetBalance(Node* node) {
  return node != nullptr ? GetHeight(node->left) - GetHeight(node->right) : 0;
}

void UpdateHeight(Node* node) {
  if (node != nullptr) {
    node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
  }
}

Node* RotateRight(Node* second) {
  Node* first = second->left;
  Node* temp = first->right;
  first->right = second;
  second->left = temp;
  UpdateHeight(second);
  UpdateHeight(first);
  return first;
}

Node* RotateLeft(Node* first) {
  Node* second = first->right;
  Node* temp = second->left;
  second->left = first;
  first->right = temp;
  UpdateHeight(first);
  UpdateHeight(second);
  return second;
}

Node* Balance(Node* node) {
  UpdateHeight(node);
  int balance_factor = GetBalance(node);
  if (balance_factor > 1) {
    if (GetBalance(node->left) < 0) {
      node->left = RotateLeft(node->left);
    }
    return RotateRight(node);
  }
  if (balance_factor < -1) {
    if (GetBalance(node->right) > 0) {
      node->right = RotateRight(node->right);
    }
    return RotateLeft(node);
  }
  return node;
}

Node* Insert(Node* node, int key) {
  if (node == nullptr) {
    return new Node(key);
  }
  if (key < node->key) {
    node->left = Insert(node->left, key);
  } else if (key > node->key) {
    node->right = Insert(node->right, key);
  } else {
    return node;
  }
  return Balance(node);
}

int LowerBound(Node* node, int key) {
  int result = -1;
  while (node != nullptr) {
    if (node->key >= key) {
      result = node->key;
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return result;
}

void FreeTree(Node* node) {
  if (node == nullptr) {
    return;
  }
  FreeTree(node->left);
  FreeTree(node->right);
  delete node;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Node* root = nullptr;
  int count_of_query = 0;
  int last_lwb = -1;
  int last_result = 0;
  std::cin >> count_of_query;
  for (int i = 1; i <= count_of_query; i++) {
    char type;
    std::cin >> type;
    if (type == '+') {
      int in_var = 0;
      std::cin >> in_var;
      if (last_lwb + 1 == i) {
        in_var = (in_var + last_result) % cMod;
      }
      root = Insert(root, in_var);
    } else {
      int in_var = 0;
      std::cin >> in_var;
      last_lwb = i;
      last_result = LowerBound(root, in_var);
      std::cout << last_result << '\n';
    }
  }
  FreeTree(root);
  return 0;
}