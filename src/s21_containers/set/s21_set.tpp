#include "s21_set.h"

namespace s21 {

template <typename Key>
set<Key>::set() : tree_(new set::tree){};

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items)
    : tree_(new set::tree) {
  for (auto& item : items) {
    insert(item);
  }
}

template <typename Key>
set<Key>::~set() {
  delete tree_;
}

template <typename Key>
set<Key>::set(const set& other) : tree_(new tree(*other.tree_)) {}

template <typename Key>
set<Key>::set(set&& other) noexcept
    : tree_(new tree(std::move(*other.tree_))) {}

template <typename Key>
set<Key>& set<Key>::operator=(const set<Key>& other) {
  if (this != &other) {
    *tree_ = *other.tree_;
  }
  return *this;
}

template <typename Key>
set<Key>& set<Key>::operator=(set<Key>&& other) {
  if (this != &other) {
    *tree_ = std::move(*other.tree_);
  }
  return *this;
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() {
  return tree_->begin();
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() {
  return tree_->end();
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::begin() const {
  return tree_->begin();
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::end() const {
  return tree_->end();
}

template <typename Key>
bool set<Key>::empty() {
  return tree_->empty();
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() {
  return tree_->size();
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() {
  return tree_->max_size();
}

template <typename Key>
void set<Key>::clear() {
  tree_->clear();
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  return tree_->insert(value);
}

template <typename Key>
void set<Key>::print() {
  tree_->print();
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  tree_->erase(pos);
}

template <typename Key>
void set<Key>::swap(set<Key>& other) {
  tree_->swap(*other.tree_);
}

template <typename Key>
void set<Key>::merge(set<Key>& other) {
  tree_->merge(*other.tree_);
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key& key) {
  return tree_->find(key);
}

template <typename Key>
bool set<Key>::contains(const Key& key) {
  return tree_->contains(key);
}

// бонус
template <typename Key>
template <typename... Args>
s21::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args&&... args) {
  s21::vector<std::pair<iterator, bool>> results;
  (results.push_back(insert(std::forward<Args>(args))), ...);
  return results;
}

}  // namespace s21