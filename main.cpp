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

Node* RotateRight(Node* y) {
  Node* x = y->left;
  Node* temp = x->right;
  x->right = y;
  y->left = temp;
  UpdateHeight(y);
  UpdateHeight(x);
  return x;
}

Node* RotateLeft(Node* x) {
  Node* y = x->right;
  Node* temp = y->left;
  y->left = x;
  x->right = temp;
  UpdateHeight(x);
  UpdateHeight(y);
  return y;
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
  int in_q = 0;
  int last_lwb = -1;
  int last_result = 0;
  std::cin >> in_q;
  for (int i = 1; i <= in_q; i++) {
    char type;
    std::cin >> type;
    if (type == '+') {
      int in_x = 0;
      std::cin >> in_x;
      if (last_lwb + 1 == i) {
        in_x = (in_x + last_result) % cMod;
      }
      root = Insert(root, in_x);
    } else {
      int in_x = 0;
      std::cin >> in_x;
      last_lwb = i;
      last_result = LowerBound(root, in_x);
      std::cout << last_result << '\n';
    }
  }
  FreeTree(root);
  return 0;
}