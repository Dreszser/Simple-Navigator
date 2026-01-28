#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <stddef.h>

#include <iostream>

namespace s21 {

template <typename T>
class Queue {
 private:
  class Container {
   public:
    T value = T();  // Поле для хранения значения узла очереди типа T,
                    // инициализируется значением по умолчанию
    Container* next =
        nullptr;  // Указатель на следующий узел в очереди, по умолчанию nullptr
    Container() = default;  // Конструктор по умолчанию для узла
    explicit Container(T value_) {
      value = value_;
    }  // для предотвращения неявных преобразований типов
    ~Container() = default;  // Деструктор по умолчанию
  };

 public:                 // внутриклассовые переопределения типов
  using value_type = T;  // the template parameter T
  using reference = T&;  // defines the type of the reference to an element
  using const_reference =
      const T&;              // defines the type of the constant reference
  using size_type = size_t;  // defines the type of the container size (standard
                             // type is size_t)

 private:
  Container* beginning = nullptr;    // указатель на первый узел
  Container* end = nullptr;          // указатель на последний узел
  size_type number_of_elements = 0;  // количество узлов

 public:
  // основные публичные методы для взаимодействия с классом

  Queue() = default;  // default constructor, creates empty Queue

  Queue(const std::initializer_list<value_type>&
            items) {  // initializer list constructor, creates Queue
                      // initizialized using std::initializer_list
    if (items.size() != 0) {
      for (auto elems : items) {
        push(elems);
      }
    }
  }

  Queue(const Queue& q)
      : beginning(nullptr), end(nullptr), number_of_elements(0) {
    Container* current = q.beginning;
    while (current != nullptr) {
      push(current->value);
      current = current->next;
    }
  }

  Queue(Queue<value_type>&& q) noexcept {  // move constructor
    if (this != &q) {
      beginning = q.beginning;
      end = q.end;
      q.beginning = nullptr;
      q.end = nullptr;
      number_of_elements = q.number_of_elements;
      q.number_of_elements = 0;
    }
  }

  ~Queue() { clear(); }  // destructor

  void clear() {
    while (!empty()) {
      pop();
    }
  }

  Queue<value_type>& operator=(
      Queue<value_type>&&
          q) noexcept {  // assignment operator overload for moving object
    if (this != &q) {
      if (number_of_elements > 0) {
        clear();
      }
      beginning = q.beginning;
      end = q.end;
      q.beginning = nullptr;
      q.end = nullptr;
      number_of_elements = q.number_of_elements;
      q.number_of_elements = 0;
    }
    return *this;
  }

  // публичные методы для доступа к элементам класса

  const_reference front() {
    return beginning->value;
  }  // access the first element

  const_reference back() { return end->value; }  // access the last element

  // публичные методы для доступа к информации о наполнении контейнера

  bool empty() const noexcept {  // checks whether the container is empty
    return number_of_elements == 0;
  }

  size_type size() const noexcept {
    return number_of_elements;
  }  // returns the number of elements

  // публичные методы для изменения контейнера

  void push(T data) {  // inserts element at the end
    auto* tmp = new Container(data);
    if (end == nullptr) {
      beginning = tmp;
      end = tmp;
    } else {
      end->next = tmp;
      end = tmp;
    }
    number_of_elements++;
  }

  void pop() {  // removes the first element
    if (empty()) return;
    Container* next_node = beginning->next;
    delete beginning;
    beginning = next_node;
    number_of_elements--;

    if (number_of_elements == 0) {
      end = nullptr;
    }
  }

  void swap(Queue<value_type>& other) {  // swaps the contents
    std::swap(beginning, other.beginning);
    std::swap(end, other.end);
    std::swap(number_of_elements, other.number_of_elements);
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push(std::forward<Args>(args)), ...);
  };
};
}  // namespace s21

#endif