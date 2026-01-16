#ifndef S21_VECTOR_H
#define S21_VECTOR_H

namespace s21 {

template <typename T>
class vector {
 public:
  class VectorIterator;
  class VectorConstIterator;

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using size_type = size_t;

  // итераторы
  using iterator = vector<T>::VectorIterator;
  using const_iterator = vector<T>::VectorConstIterator;

  // конструкторы
  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const&
             items);  // инициализация с помощью списка
  vector(const vector& v);      // конструктор копирования
  vector(vector&& v) noexcept;  // конструктор перемещения

  //  оператор
  vector& operator=(vector&& v) noexcept;  // перемещающее присваивание

  // деструктор
  ~vector();

  // методы доступа к элементам класса
  reference at(size_type pos);  // ссылка на элемент с проверкой границ
  reference operator[](size_type pos);  // ссылка на элемент без проверки границ
  const_reference front() const;  // сылка на первый элемент
  const_reference back() const;  // ссылка на последний элемент
  pointer data() noexcept;  // указатель на первый элемент

  // методы итерирования
  iterator begin() noexcept;  // итератор на первый элемент
  iterator end() noexcept;  // итератор на элемент после последнего
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // информация о заполненности
  bool empty() const;
  size_type size() const;  // возвращает кол-во элементов в векторе
  size_type max_size() const;
  void reserve(size_type new_cap);
  size_type capacity() const;
  void shrink_to_fit();

  // модификаторы
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other) noexcept;

  // дополнительно
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  pointer data_;
  size_type size_;
  size_type capacity_;
};

template <typename T>
class vector<T>::VectorIterator {
 public:
  using value_type = typename vector<T>::value_type;
  using pointer = typename vector<T>::pointer;
  using reference = typename vector<T>::reference;

  VectorIterator(pointer ptr) : ptr_(ptr) {}

  reference operator*() const { return *ptr_; }

  VectorIterator operator++(int) {
    // перемещает итератор вперед, возвращает его состояние до изменения
    VectorIterator temp(*this);
    ++ptr_;
    return temp;
  }

  VectorIterator operator--(int) {
    VectorIterator temp(*this);
    --ptr_;
    return temp;
  }

  VectorIterator& operator++() {
    // перемещает итератор вперед, возвращает его состояние после изменения
    ++ptr_;
    return *this;
  }

  VectorIterator& operator--() {
    --ptr_;
    return *this;
  }

  bool operator==(const VectorIterator& other) const {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const VectorIterator& other) const {
    return ptr_ != other.ptr_;
  }

  VectorIterator operator+(int n) const {
    VectorIterator temp(*this);
    for (int i = 0; i < n; i++) {
      temp++;
    }
    return temp;
  }

  VectorIterator operator-(int n) const {
    VectorIterator temp(*this);
    for (int i = 0; i < n; i++) {
      temp--;
    }
    return temp;
  }

  ptrdiff_t operator-(const VectorIterator& other) const {
    return ptr_ - other.ptr_;
  }

 private:
  pointer ptr_;
};

template <typename T>
class vector<T>::VectorConstIterator {
 public:
  using value_type = typename vector<T>::const_reference;
  using pointer = typename vector<T>::const_pointer;
  using reference = typename vector<T>::const_reference;

  VectorConstIterator(const_pointer ptr) : ptr_(ptr) {}

  const_reference operator*() const { return *ptr_; }

  VectorConstIterator operator++(int) {
    VectorConstIterator temp(*this);
    ++ptr_;
    return temp;
  }

  VectorConstIterator operator--(int) {
    VectorConstIterator temp(*this);
    --ptr_;
    return temp;
  }

  VectorConstIterator& operator++() {
    ++ptr_;
    return *this;
  }

  VectorConstIterator& operator--() {
    --ptr_;
    return *this;
  }

  bool operator==(const VectorConstIterator& other) const {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const VectorConstIterator& other) const {
    return ptr_ != other.ptr_;
  }

  VectorConstIterator operator+(int n) const {
    VectorConstIterator temp(*this);
    for (int i = 0; i < n; i++) {
      temp++;
    }
    return temp;
  }

  VectorConstIterator operator-(int n) const {
    VectorConstIterator temp(*this);
    for (int i = 0; i < n; i++) {
      temp--;
    }
    return temp;
  }

  ptrdiff_t operator-(const VectorConstIterator& other) const {
    return ptr_ - other.ptr_;
  }

 private:
  const_pointer ptr_;
};
}  // namespace s21

#include "s21_vector.tpp"
#endif  // S21_VECTOR_H