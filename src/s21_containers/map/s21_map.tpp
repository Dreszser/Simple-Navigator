#ifndef S21_MAP_TPP
#define S21_MAP_TPP

namespace s21 {
// конструкторы
template <typename Key, typename T>
map<Key, T>::map() : tree_() {}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items) : tree_() {
  for (auto& item : items) {
    tree_.insert(item);
  }
}

template <typename Key, typename T>
map<Key, T>::map(const map& m) {
  for (const auto& pair : m) {
    tree_.insert(pair);
  }
}

template <typename Key, typename T>
map<Key, T>::map(map&& m) noexcept : tree_(std::move(m.tree_)) {}

template <typename Key, typename T>
map<Key, T>::~map() = default;

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(map&& m) noexcept {
  if (this != &m) {
    tree_ = std::move(m.tree_);
  }
  return *this;
}

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(const map& m) noexcept {
  if (this != &m) {
    tree_ = m.tree_;
  }
  return *this;
}

// методы доступа
template <typename Key, typename T>
T& map<Key, T>::at(const Key& key) {
  for (auto it = tree_.begin(); it != tree_.end(); ++it) {
    if ((*it).first == key) {
      return (*it).second;
    }
  }
  throw std::out_of_range("Key not found");
}

template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  for (auto it = tree_.begin(); it != tree_.end(); ++it) {
    if ((*it).first == key) {
      return (*it).second;
    }
  }
  // Если элемент не найден, создаем новый элемент с заданным ключом
  T value = T();
  auto result = tree_.insert(std::make_pair(key, value));
  auto it = result.first;
  return (*it).second;
}

// итерирование
template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() noexcept {
  return tree_.begin();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() noexcept {
  return tree_.end();
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::begin() const noexcept {
  return tree_.begin();
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::end() const noexcept {
  return tree_.end();
}

// емкость
template <typename Key, typename T>
bool map<Key, T>::empty() {
  return tree_.empty();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() {
  return tree_.size();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() {
  return tree_.max_size();
}

// модификаторы
template <typename Key, typename T>
void map<Key, T>::clear() noexcept {
  tree_.clear();
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  for (auto it = tree_.begin(); it != tree_.end(); ++it) {
    if ((*it).first == value.first) {
      return {it, false};
    }
  }
  auto result = tree_.insert(value);
  return {result.first, true};
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  std::pair<const Key, T> pair = std::make_pair(key, obj);
  return insert(pair);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  value_type temp(key, obj);
  for (auto it = begin(); it != end(); ++it) {
    if ((*it).first == key) {
      (*it).second = obj;
      return {it, false};
    }
  }
  auto result = tree_.insert(temp);
  return {result.first, true};
}

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) noexcept {
  tree_.erase(pos);
}

template <typename Key, typename T>
void map<Key, T>::swap(map& other) noexcept {
  tree_.swap(other.tree_);
}

template <typename Key, typename T>
void map<Key, T>::merge(map& other) {
  tree_.merge(other.tree_);
}

// метод просмотра содержимого
template <typename Key, typename T>
bool map<Key, T>::contains(const Key& key) const {
  for (auto it = begin(); it != end(); ++it) {
    if ((*it).first == key) {
      return true;
    }
  }
  return false;
}

// бонус
template <typename Key, typename T>
template <typename... Args>
s21::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args&&... args) {
  s21::vector<std::pair<iterator, bool>> results;
  (results.push_back(insert(args.first, args.second)), ...);
  return results;
}

}  // namespace s21

#endif  // S21_MAP_TPP