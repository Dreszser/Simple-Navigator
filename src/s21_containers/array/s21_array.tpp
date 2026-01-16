#ifndef S21_ARRAY_TPP
#define S21_ARRAY_TPP

#include <iostream>

namespace s21 {

// конструкторы
template <typename T, std::size_t N>
array<T, N>::array() {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) {
    throw std::out_of_range("Initializer list size exceeds array size");
  }
  std::copy(items.begin(), items.end(), data_);
}

template <typename T, std::size_t N>
array<T, N>::array(const array &a) {
  std::copy(a.data_, a.data_ + N, data_);
}

template <typename T, std::size_t N>
array<T, N>::array(array &&a) noexcept {
  std::move(a.data_, a.data_ + N, data_);
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) noexcept {
  if (this != &a) {
    std::move(a.data_, a.data_ + N, data_);
  }
  return *this;
}

template <typename T, std::size_t N>
array<T, N>::~array() {}

// методы доступа
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Array index out of bounds");
  }
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return data_[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return data_[N - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() noexcept {
  return data_;
}

// методы итерирования
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return data_ + N;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
  return data_ + N;
}

// информация о наполнении
template <typename T, std::size_t N>
bool array<T, N>::empty() const {
  return N == 0;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const {
  return N;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const {
  return size();
}

// методы изменения
template <typename T, std::size_t N>
void array<T, N>::swap(array &other) noexcept {
  std::swap_ranges(data_, data_ + N, other.data_);
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(data_, data_ + N, value);
}
}  // namespace s21

#endif  // S21_ARRAT_TPP