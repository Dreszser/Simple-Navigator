#ifndef S21_ARRAY_H
#define S21_ARRAY_H

namespace s21 {

template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // конструкторы
  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);                 // copy
  array(array &&a) noexcept;             // move
  array &operator=(array &&a) noexcept;  // moving assingment
  ~array();

  // методы доступа
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data() noexcept;

  // методы итерирования
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  // информация о наполнении
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // методы изменения
  void swap(array &other) noexcept;
  void fill(const_reference value);

 private:
  value_type data_[N];
};
}  // namespace s21

#include "s21_array.tpp"
#endif  // S21_ARRAY_H