#ifndef S21_MAP_H
#define S21_MAP_H

#include "../tree/S21Tree.h"
#include "../vector/s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename Tree<value_type>::iterator;
  using const_iterator = typename Tree<value_type>::const_iterator;
  using size_type = size_t;

  // конструкторы
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m) noexcept;
  ~map();

  map& operator=(map&& m) noexcept;
  map& operator=(const map& m) noexcept;

  // методы доступа
  T& at(const Key& key);
  T& operator[](const Key& key);

  // итерирование
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  // емкость
  bool empty();
  size_type size();
  size_type max_size();

  // модификаторы
  void clear() noexcept;
  // вставляет узел, возвращает итератор и флаг успешности
  std::pair<iterator, bool> insert(const value_type& value);
  // вставляет элемент по ключу, возвращает итератор и флаг успешности
  std::pair<iterator, bool> insert(const Key& key, const T& onj);
  // вставляет элемент, если он уже существует - обновляет значение
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos) noexcept;
  void swap(map& other) noexcept;
  void merge(map& other);

  // метод просмотра содержимого
  bool contains(const Key& key) const;

  // бонус
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  Tree<value_type> tree_;
};
}  // namespace s21

#include "s21_map.tpp"
#endif  // S21_MAP_H