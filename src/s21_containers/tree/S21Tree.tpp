#include "S21Tree.h"

namespace s21 {

template <typename T>
Tree<T>::Tree()
    : root_(nullptr), leftMost_(nullptr), endNode_(new Node(T())), size_(0){};

template <typename T>
Tree<T>::Tree(std::initializer_list<value_type> const& items) : Tree() {
  for (auto& item : items) {
    insert(item);
  }
}

template <typename T>
Tree<T>::Tree(const Tree<T>& other) : Tree() {
  *this = other;
}

template <typename T>
Tree<T>::Tree(Tree<T>&& other) noexcept : Tree() {
  *this = std::move(other);
}

template <typename T>
Tree<T>::~Tree() {
  DestroyTree(this->root_);
  delete endNode_;
}

template <typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other) {
  if (this != &other) {
    clear();
    for (auto it = other.begin(); it != other.end(); ++it) {
      insertNonUnique(*it);
    }
  }
  return *this;
}

template <typename T>
Tree<T>& Tree<T>::operator=(Tree<T>&& other) {
  if (this != &other) {
    clear();
    std::swap(root_, other.root_);
    std::swap(endNode_, other.endNode_);
    std::swap(leftMost_, other.leftMost_);
    std::swap(size_, other.size_);
  }
  return *this;
}

template <typename T>
bool Tree<T>::empty() {
  return root_ == nullptr;
}

template <typename T>
typename Tree<T>::size_type Tree<T>::size() {
  return size_;
}

template <typename T>
typename Tree<T>::size_type Tree<T>::max_size() {
  return (std::numeric_limits<std::ptrdiff_t>::max() / sizeof(Node<T>));
}

template <typename T>
void Tree<T>::DestroyTree(Node<T>* node) {
  if (node) {
    DestroyTree(node->left);
    DestroyTree(node->right);
    delete node;
  }
}

template <typename T>
std::pair<typename Tree<T>::iterator, bool> Tree<T>::insert(
    const value_type& newdata) {
  Node<T>* newNode = new Node(newdata);
  iterator iter = iterator(newNode);
  bool insertSuccess = true;
  root_ = insert(root_, newNode, &insertSuccess, &iter);
  if (insertSuccess) {
    ++size_;
    balanceTree(newNode);
    root_->colour = BLACK;
    root_->parent = endNode_;
    updateExtremes(newNode);
  } else {
    delete newNode;
  }
  iterator res = (insertSuccess ? iterator(newNode) : iter);
  return std::make_pair(res, insertSuccess);
}

template <typename T>
Node<T>* Tree<T>::insert(Node<T>* node, Node<T>* newNode, bool* flag,
                         iterator* it) {
  if (node == nullptr) {
    return newNode;
  }
  if (newNode->value < node->value) {
    node->left = insert(node->left, newNode, flag, it);
    node->left->parent = node;
  } else if (newNode->value > node->value) {
    node->right = insert(node->right, newNode, flag, it);
    node->right->parent = node;
  } else {
    *it = iterator(node);
    *flag = false;
  }
  return node;
}

template <typename T>
std::pair<typename Tree<T>::iterator, bool> Tree<T>::insertNonUnique(
    const value_type& newdata) {
  Node<T>* newNode = new Node(newdata);
  root_ = insertNonUnique(root_, newNode);
  ++size_;
  balanceTree(newNode);
  root_->colour = BLACK;
  root_->parent = endNode_;
  updateExtremes(newNode);
  iterator res = iterator(newNode);
  return std::make_pair(res, true);
}

template <typename T>
Node<T>* Tree<T>::insertNonUnique(Node<T>* node, Node<T>* newNode) {
  if (node == nullptr) {
    return newNode;
  }
  if (newNode->value < node->value) {
    node->left = insertNonUnique(node->left, newNode);
    node->left->parent = node;
  } else {
    node->right = insertNonUnique(node->right, newNode);
    node->right->parent = node;
  }
  return node;
}

template <typename T>
void Tree<T>::balanceTree(Node<T>* node) {
  Node<T>* currentNode = node;
  while (currentNode != root_ && currentNode->parent->colour == RED) {
    Node<T>* parent = currentNode->parent;
    Node<T>* grandparent = currentNode->parent->parent;
    if (grandparent->left == parent) {
      if (grandparent->right && grandparent->right->colour == RED) {
        parent->colour = BLACK;
        grandparent->colour = RED;
        grandparent->right->colour = BLACK;
        currentNode = grandparent;
      } else {
        if (currentNode == parent->right) {
          currentNode = parent;
          leftRotate(currentNode);
        }
        currentNode->parent->colour = BLACK;
        grandparent->colour = RED;
        rightRotate(grandparent);
      }
    } else if (grandparent->right == parent) {
      if (grandparent->left && grandparent->left->colour == RED) {
        parent->colour = BLACK;
        grandparent->colour = RED;
        grandparent->left->colour = BLACK;
        currentNode = grandparent;
      } else {
        if (currentNode == parent->left) {
          currentNode = parent;
          rightRotate(currentNode);
        }
        currentNode->parent->colour = BLACK;
        grandparent->colour = RED;
        leftRotate(grandparent);
      }
    }
  }
}

template <typename T>
void Tree<T>::leftRotate(Node<T>* node) {
  Node<T>* pivot = node->right;
  pivot->parent = node->parent;

  if (node == root_) {
    root_ = pivot;
  } else if (node->parent->left == node) {
    node->parent->left = pivot;
  } else {
    node->parent->right = pivot;
  }
  node->right = pivot->left;
  if (pivot->left != nullptr) {
    pivot->left->parent = node;
  }
  node->parent = pivot;
  pivot->left = node;
}

template <typename T>
void Tree<T>::rightRotate(Node<T>* node) {
  Node<T>* pivot = node->left;

  pivot->parent = node->parent;
  if (node == root_) {
    root_ = pivot;
  } else if (node->parent->left == node) {
    node->parent->left = pivot;
  } else {
    node->parent->right = pivot;
  }

  node->left = pivot->right;
  if (pivot->right != nullptr) {
    pivot->right->parent = node;
  }
  node->parent = pivot;
  pivot->right = node;
}

template <typename T>
void Tree<T>::print() {
  if (root_) {
    std::cout << root_->value << " <- ROOT" << std::endl;
    for (ConstTreeIterator iter = begin(); iter != end(); ++iter) {
      std::cout << *iter << " " << (iter.getColour() == RED ? "red" : "black")
                << std::endl;
    }
    std::cout << "size:" << size_ << std::endl;
  } else {
    std::cout << "tree is empty" << std::endl;
  }
}

template <typename T>
void Tree<T>::printBT(const std::string& prefix, const Node<T>* node,
                      bool isLeft) {
  if (node != nullptr) {
    std::cout << prefix;

    std::cout << (isLeft ? "├──" : "└──");

    // print the value of the node
    std::cout << node->value << " " << (node->colour == RED ? "red" : "black")
              << std::endl;

    // enter the next tree level - left and right branch
    printBT(prefix + (isLeft ? "│   " : "    "), node->right, true);
    printBT(prefix + (isLeft ? "│   " : "    "), node->left, false);
  }
}

template <typename T>
void Tree<T>::printBT(const Node<T>* node) {
  printBT("", node, false);
}

template <typename T>
void Tree<T>::updateExtremes(Node<T>* node) {
  if (!leftMost_ || leftMost_->value > node->value) {
    leftMost_ = node;
  }
  if (!(endNode_->parent) || endNode_->parent->value < node->value) {
    endNode_->parent = node;
  }
}

template <typename T>
void Tree<T>::updateExtremesOnDeletion(Node<T>* node) {
  if (node == leftMost_) {
    iterator it(leftMost_);
    ++it;
    leftMost_ = it.getCurrentNode();
  }
  if (node == endNode_->parent) {
    iterator it(endNode_->parent);
    --it;
    endNode_->parent = it.getCurrentNode();
  }
}

template <typename T>
Node<T>* Tree<T>::minimum(Node<T>* node) const {
  Node<T>* temp = node;
  while (temp && temp->left) {
    temp = temp->left;
  }
  return temp;
}

template <typename T>
Node<T>* Tree<T>::maximum(Node<T>* node) const {
  Node<T>* temp = node;
  while (temp && temp->right) {
    temp = temp->right;
  }
  return temp;
}

template <typename T>
void Tree<T>::clear() {
  if (root_) {
    DestroyTree(root_);
  }
  root_ = nullptr;
  endNode_->parent = nullptr;
  leftMost_ = nullptr;
  size_ = 0;
}

template <typename T>
void Tree<T>::transplant(Node<T>* node, Node<T>* other) {
  if (other->parent->left == other) {
    other->parent->left = node;
  } else {
    other->parent->right = node;
  }

  if (node == root_) {
    root_ = other;
  } else {
    if (node->parent->left == node) {
      node->parent->left = other;
    } else {
      node->parent->right = other;
    }
  }

  std::swap(node->parent, other->parent);
  std::swap(node->left, other->left);
  std::swap(node->right, other->right);
  std::swap(node->colour, other->colour);

  if (node->left) {
    node->left->parent = node;
  }
  if (node->right) {
    node->right->parent = node;
  }
  if (other->left) {
    other->left->parent = other;
  }
  if (other->right) {
    other->right->parent = other;
  }
}

template <typename T>
void Tree<T>::erase(iterator pos) {
  if (pos == end()) return;
  Node<T>* deletedNode = pos.getCurrentNode();

  if (deletedNode->left != nullptr && deletedNode->right != nullptr) {
    Node<T>* replace = minimum(deletedNode->right);
    transplant(deletedNode, replace);
  }
  int count_child = (deletedNode->left ? 1 : 0) + (deletedNode->right ? 1 : 0);

  if (deletedNode->colour == BLACK && count_child == 1) {
    Node<T>* replace;
    if (deletedNode->left != nullptr) {
      replace = deletedNode->left;
    } else {
      replace = deletedNode->right;
    }
    transplant(deletedNode, replace);
  }

  if (deletedNode->colour == BLACK && count_child == 0) {
    fixDelete(deletedNode);
  }
  if (deletedNode == root_) {
    root_ = nullptr;
    leftMost_ = nullptr;
    endNode_->parent = nullptr;
  } else {
    if (deletedNode == deletedNode->parent->left) {
      deletedNode->parent->left = nullptr;
    } else {
      deletedNode->parent->right = nullptr;
    }
    updateExtremesOnDeletion(deletedNode);
  }
  --size_;
  delete deletedNode;
}

template <typename T>
void Tree<T>::fixDelete(Node<T>* node) {
  bool flag = true;
  while (node != root_ && node->colour == BLACK && flag) {
    if (node == node->parent->left) {
      fixLeft(&node, &flag);
    } else {
      fixRight(&node, &flag);
    }
  }
}

template <typename T>
void Tree<T>::fixLeft(Node<T>** node, bool* flag) {
  Node<T>* parent = (*node)->parent;
  Node<T>* sibling = parent->right;

  if (sibling->colour == RED) {
    sibling->colour = BLACK;
    parent->colour = RED;
    leftRotate(parent);
    parent = (*node)->parent;
    sibling = parent->right;
  }
  if (sibling->colour == BLACK &&
      (sibling->left == nullptr || sibling->left->colour == BLACK) &&
      (sibling->right == nullptr || sibling->right->colour == BLACK)) {
    sibling->colour = RED;
    if (parent->colour == RED) {
      parent->colour = BLACK;
      *flag = false;
    }
    if (*flag) {
      (*node) = parent;
      parent = (*node)->parent;
    }
  } else {
    if (sibling->left != nullptr && sibling->left->colour == RED &&
        (sibling->right == nullptr || sibling->right->colour == BLACK)) {
      std::swap(sibling->colour, sibling->left->colour);
      rightRotate(sibling);
      sibling = parent->right;
    }
    sibling->right->colour = BLACK;
    sibling->colour = parent->colour;
    parent->colour = BLACK;
    leftRotate(parent);
    *flag = false;
  }
}

template <typename T>
void Tree<T>::fixRight(Node<T>** node, bool* flag) {
  Node<T>* parent = (*node)->parent;
  Node<T>* sibling = parent->left;
  if (sibling->colour == RED) {
    sibling->colour = BLACK;
    parent->colour = RED;
    rightRotate(parent);
    parent = (*node)->parent;
    sibling = parent->left;
  }
  if (sibling->colour == BLACK &&
      (sibling->left == nullptr || sibling->left->colour == BLACK) &&
      (sibling->right == nullptr || sibling->right->colour == BLACK)) {
    sibling->colour = RED;
    if (parent->colour == RED) {
      parent->colour = BLACK;
      *flag = false;
    }
    if (*flag) {
      (*node) = parent;
      parent = (*node)->parent;
    }
  } else {
    if (sibling->right != nullptr && sibling->right->colour == RED &&
        (sibling->left == nullptr || sibling->left->colour == BLACK)) {
      std::swap(sibling->colour, sibling->right->colour);
      leftRotate(sibling);
      sibling = parent->left;
    }
    sibling->left->colour = BLACK;
    sibling->colour = parent->colour;
    parent->colour = BLACK;
    rightRotate(parent);
    *flag = false;
  }
}

template <typename T>
TreeIterator<T> Tree<T>::begin() {
  if (root_)
    return TreeIterator(leftMost_);
  else
    return end();
}

template <typename T>
TreeIterator<T> Tree<T>::end() {
  return TreeIterator(endNode_);
}

template <typename T>
ConstTreeIterator<T> Tree<T>::begin() const {
  if (root_)
    return ConstTreeIterator(leftMost_);
  else
    return end();
}

template <typename T>
ConstTreeIterator<T> Tree<T>::end() const {
  return TreeIterator(endNode_);
}

template <typename T>
void Tree<T>::swap(Tree<T>& other) {
  std::swap(root_, other.root_);
  std::swap(leftMost_, other.leftMost_);
  std::swap(endNode_, other.endNode_);
  std::swap(size_, other.size_);
}

template <typename T>
void Tree<T>::merge(Tree<T>& other) {
  if (this != &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(*it);
    }
    other.clear();
  }
}

template <typename T>
typename Tree<T>::iterator Tree<T>::find(const_reference key) {
  Node<T>* currentNode = root_;
  Node<T>* result = endNode_;
  while (currentNode && result == endNode_) {
    if (key < currentNode->value) {
      currentNode = currentNode->left;
    } else if (key > currentNode->value) {
      currentNode = currentNode->right;
    } else {
      result = currentNode;
    }
  }
  return iterator(result);
}

template <typename T>
bool Tree<T>::contains(const_reference key) {
  return (find(key) != end());
}

template <typename T>
typename Tree<T>::iterator Tree<T>::lower_bound(const_reference key) {
  Node<T>* current = root_;
  Node<T>* result = endNode_;
  while (current) {
    if (key <= current->value) {
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return iterator(result);
}

template <typename T>
typename Tree<T>::iterator Tree<T>::upper_bound(const_reference key) {
  Node<T>* current = root_;
  Node<T>* result = endNode_;
  while (current) {
    if (key >= current->value) {
      current = current->right;
    } else {
      result = current;
      current = current->left;
    }
  }
  return iterator(result);
}

/* ================ Iterator ================ */

template <typename T>
TreeIterator<T>::TreeIterator(const TreeIterator& other) {
  *this = other;
}

template <typename T>
TreeIterator<T>::TreeIterator(TreeIterator&& other) {
  currentNode_ = other.currentNode_;
  other.currentNode_ = nullptr;
}

template <typename T>
TreeIterator<T>& TreeIterator<T>::operator=(const TreeIterator& other) {
  if (this != &other) {
    currentNode_ = other.currentNode_;
  }
  return *this;
}

template <typename T>
TreeIterator<T>& TreeIterator<T>::operator=(TreeIterator&& other) noexcept {
  if (this != &other) {
    currentNode_ = other.currentNode_;
    other.currentNode_ = nullptr;
  }
  return *this;
}

template <typename T>
bool TreeIterator<T>::operator==(TreeIterator& other) const {
  return (currentNode_ == other.currentNode_);
}

template <typename T>
bool TreeIterator<T>::operator==(const TreeIterator& other) const {
  return (currentNode_ == other.currentNode_);
}

template <typename T>
bool TreeIterator<T>::operator!=(TreeIterator& other) const {
  return (currentNode_ != other.currentNode_);
}

template <typename T>
bool TreeIterator<T>::operator!=(const TreeIterator& other) const {
  return (currentNode_ != other.currentNode_);
}

template <typename T>
TreeIterator<T>& TreeIterator<T>::operator++() {
  if (currentNode_ && currentNode_->right) {
    Node<T>* rightNode = currentNode_->right;
    while (rightNode->left) {
      rightNode = rightNode->left;
    }
    currentNode_ = rightNode;
  } else if (currentNode_) {
    Node<T>* parent = currentNode_->parent;
    while (parent && parent->right == currentNode_) {
      currentNode_ = parent;
      parent = currentNode_->parent;
    }
    currentNode_ = parent;
  }
  return *this;
}

template <typename T>
TreeIterator<T>& TreeIterator<T>::operator--() {
  if (currentNode_ && currentNode_->left) {
    Node<T>* leftNode = currentNode_->left;
    while (leftNode->right) {
      leftNode = leftNode->right;
    }
    currentNode_ = leftNode;
  } else if (currentNode_) {
    Node<T>* parent = currentNode_->parent;
    while (parent && parent->left == currentNode_) {
      currentNode_ = parent;
      parent = currentNode_->parent;
    }
    currentNode_ = parent;
  }
  return *this;
}

template <typename T>
TreeIterator<T> TreeIterator<T>::operator++(int) {
  TreeIterator tmp(*this);
  ++(*this);
  return tmp;
}

template <typename T>
TreeIterator<T> TreeIterator<T>::operator--(int) {
  TreeIterator tmp(*this);
  --(*this);
  return tmp;
}

template <typename T>
T& TreeIterator<T>::operator*() {
  return currentNode_->value;
}

template <typename T>
Colour TreeIterator<T>::getColour() {
  return currentNode_->colour;
}

template <typename T>
Node<T>* TreeIterator<T>::getCurrentNode() const {
  return currentNode_;
}

/* ================ Const Iterator ================ */

template <typename T>
ConstTreeIterator<T>& ConstTreeIterator<T>::operator=(
    const ConstTreeIterator<T>& other) {
  if (this != &other) {
    TreeIterator<T>::operator=(other);
  }
  return *this;
}

template <typename T>
ConstTreeIterator<T>& ConstTreeIterator<T>::operator=(
    ConstTreeIterator<T>&& other) noexcept {
  if (this != &other) {
    TreeIterator<T>::operator=(std::move(other));
  }
  return *this;
}

template <typename T>
typename ConstTreeIterator<T>::const_reference ConstTreeIterator<T>::operator*()
    const {
  return this->getCurrentNode()->value;
}

}  // namespace s21
