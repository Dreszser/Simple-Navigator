#ifndef S21_VECTOR_TPP
#define S21_VECTOR_TPP

namespace s21 {
// конструкторы
template <typename T>  // конструктор по умолчанию
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>  // конструктор с параметрами
vector<T>::vector(size_type n)
    : data_(new value_type[n]), size_(n), capacity_(n) {
  // инициализация всех элементов значением по умолчанию
  std::fill_n(data_, n, value_type());
}

template <typename T>  // инициализация с помощью списка
vector<T>::vector(std::initializer_list<value_type> const &items)
    : vector(items.size()) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T>  // конструктор копирования
vector<T>::vector(const vector &v) : vector(v.size_) {
  std::copy(v.data_, v.data_ + v.size_, data_);
}

template <typename T>  // конструктор перемещения
vector<T>::vector(vector &&v) noexcept {
  size_ = std::exchange(v.size_, 0);
  capacity_ = std::exchange(v.capacity_, 0);
  data_ = std::exchange(v.data_, nullptr);
}

template <typename T>  // деструктор
vector<T>::~vector() {
  delete[] data_;
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename T>  // перемещение присваиванием
vector<T> &vector<T>::operator=(vector<T> &&v) noexcept {
  if (this != &v) {
    this->swap(v);
    delete[] v.data_;
    v.size_ = 0;
    v.capacity_ = 0;
    v.data_ = nullptr;
  }
  return *this;
}

// методы доступа к элементам класса
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index out of range");
  return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  return data_[size_ - 1];
}

template <typename T>
typename vector<T>::pointer vector<T>::data() noexcept {
  return data_;
}

// методы итерирования
template <typename T>
typename vector<T>::iterator vector<T>::begin() noexcept {
  return iterator(data_);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() noexcept {
  return iterator(data_ + size_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const noexcept {
  return const_iterator(data_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const noexcept {
  return const_iterator(data_ + size_);
}

// информация о заполненности
template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  // возвращает максимально возможное значение для типа size_type
  // делит его на sizeof(T), чтобы узнать максимальное кол-во элементов
  return std::numeric_limits<size_type>::max() / sizeof(T);
}

template <typename T>
void vector<T>::reserve(size_type new_cap) {
  if (new_cap > capacity_) {
    vector<T> temp(new_cap);
    std::copy(data_, data_ + size_, temp.data_);
    temp.size_ = size_;
    this->swap(temp);
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    vector<T> temp(size_);
    std::copy(data_, data_ + size_, temp.data_);
    this->swap(temp);
  }
}

// модификаторы
template <typename T>
void vector<T>::clear() noexcept {
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - begin();
  if (index > size_) {
    throw std::out_of_range("Iterator out of bounds");
  }
  if (this->size_ == capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }
  for (size_type i = size_; i > index; --i) {
    data_[i] = std::move(data_[i - 1]);
  }
  data_[index] = value;
  ++size_;
  return iterator(data_ + index);
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type index = pos - data_;
  if (index > size_) {
    throw std::out_of_range("Iterator out of bounds");
  }
  for (iterator i = pos; i != end() - 1; ++i) {
    *i = *(i + 1);
  }
  --size_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }
  data_[size_++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ == 0) {
    throw std::out_of_range("Cannot pop_back from an empty vector");
  }
  --size_;
}

template <typename T>
void vector<T>::swap(vector<T> &other) noexcept {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
template <typename... Args>
typename s21::vector<T>::iterator s21::vector<T>::insert_many(
    const_iterator pos, Args &&...args) {
  size_type index = pos - data_;
  // Проверка на выход за пределы
  if (index > size_) {
    throw std::out_of_range("Iterator out of bounds");
  }
  size_type insert_pos = pos - cbegin();
  size_type count = sizeof...(args);
  // Обработка случая вставки 0 элементов
  if (count != 0) {
    // Если превышаем емкость, выделяем больше места
    if (size_ + count > capacity_) {
      reserve(std::max(size_ + count, capacity_ * 2));
    }
    // Сдвигаем элементы вправо
    for (size_type i = size_; i > insert_pos; --i) {
      *(begin() + i + count - 1) = *(begin() + i - 1);
    }
    // Вставляем новые элементы
    size_type i = 0;
    ((*(begin() + insert_pos + i++) = T(std::forward<Args>(args))), ...);
    size_ += count;
  }
  return begin() + insert_pos;
}

template <typename T>
template <typename... Args>
void s21::vector<T>::insert_many_back(Args &&...args) {
  insert_many(cend(), args...);
}
}  // namespace s21

#endif  // S21_VECTOR_TPP