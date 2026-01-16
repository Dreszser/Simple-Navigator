#include "s21_multiset.h"

namespace s21 {

template <typename Key>
multiset<Key>::multiset() : set<Key>() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items)
    : multiset() {
  for (auto& item : items) {
    insert(item);
  }
}

template <typename Key>
multiset<Key>::multiset(const multiset& other) : set<Key>(other) {}

template <typename Key>
multiset<Key>::multiset(multiset&& other) noexcept
    : set<Key>(std::move(other)) {}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(const multiset<Key>& other) {
  set<Key>::operator=(other);
  return *this;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset<Key>&& other) {
  set<Key>::operator=(std::move(other));
  return *this;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, bool> multiset<Key>::insert(
    const value_type& value) {
  return this->tree_->insertNonUnique(value);
}

template <typename Key>
void multiset<Key>::merge(multiset<Key>& other) {
  if (this != &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(*it);
    }
    other.clear();
  }
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  return this->tree_->lower_bound(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  return this->tree_->upper_bound(key);
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) {
  iterator low = lower_bound(key);
  iterator high = upper_bound(key);
  size_type result = 0;
  while (low != high) {
    ++result;
    ++low;
  }
  return result;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename Key>
template <typename... Args>
s21::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args&&... args) {
  s21::vector<std::pair<iterator, bool>> results;
  (results.push_back(insert(std::forward<Args>(args))), ...);
  return results;
}

}  // namespace s21