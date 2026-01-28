#ifndef S21_Stack_H
#define S21_Stack_H

#include <stddef.h>

#include <iostream>

namespace s21 {

template <typename T>
class Stack {
 private:
  class Container {
   public:
    T value = T();  // Поле для хранения значения узла стека типа T,
                    // инициализируется значением по умолчанию.
    Container* next =
        nullptr;  // Указатель на следующий узел в стеке, по умолчанию nullptr.
    Container() = default;  // Конструктор по умолчанию для узла.
    Container(T value_) {
      value = value_;
    }  // Конструктор для узла, инициализирует узел значением value_.
    ~Container() = default;  // Деструктор по умолчанию
  };

 public:                 // внутриклассовые переопределения типов
  using value_type = T;  // the template parameter T
  using reference = T&;  // defines the type of the reference to an element
  using const_reference =
      const T&;              // defines the type of the constant reference
  using size_type = size_t;  //  defines the type of the container size
                             //  (standard type is size_t)

 private:
  size_type number_of_elements = 0;  // Количество узлов в стеке.
  Container* beginning =
      nullptr;  // Указатель на верхний узел стека (начало стека).

 public:
  // основные публичные методы для взаимодействия с классом

  Stack() {  // default constructor, creates empty Stack
    beginning = nullptr;
    number_of_elements = 0;
  };

  Stack(std::initializer_list<value_type> const&
            items) {  // initializer list constructor, creates Stack
                      // initizialized using std::initializer_list
    if (items.size() != 0) {
      for (auto elems : items) {  // auto позволяет определить тип переменной
                                  // elems на основе типа items
        push(elems);
      }
    }
  }

  Stack(const Stack<value_type>& s) {  // copy constructor
    /* if (s.empty()) {
      throw std::out_of_range("Unable to copy empty Stack into another");
    } */

    Container* current_other = s.beginning;
    current_other = current_other->next;
    beginning = new Container(s.beginning->value);
    Container* current_this = beginning;
    while (current_other != nullptr) {
      current_this->next = new Container(current_other->value);
      current_this = current_this->next;
      current_other = current_other->next;
    }
    number_of_elements = s.number_of_elements;
  }

  Stack(Stack<value_type>&& s) noexcept {  // move constructor
    if (this != &s) {
      beginning = s.beginning;
      s.beginning = nullptr;
      number_of_elements = s.number_of_elements;
      s.number_of_elements = 0;
    }
  }

  ~Stack() { clear(); };  // destructor

  void clear() {  // очистка стека
    while (!empty()) {
      pop();
    }
  }

  Stack<value_type>& operator=(
      Stack<value_type>&&
          s) noexcept {  // assignment operator overload for moving object
    if (this != &s) {
      if (number_of_elements > 0) {
        clear();  // освобождение текущих данных
      }
      beginning = s.beginning;
      s.beginning = nullptr;
      number_of_elements = s.number_of_elements;
      s.number_of_elements = 0;  // перемезение из стека s
    }
    return *this;
  }

  // публичные методы для доступа к элементам класса

  const_reference top() const {
    if (empty()) {
      throw std::out_of_range("Stack is empty");
    }
    return beginning->value;
  }  // возвращает ссылку на верхний элемент

  // публичные методы для доступа к информации о наполнении контейнера

  bool empty() const noexcept {  // checks whether the container is empty
    if (number_of_elements > 0) {
      return false;
    }
    return true;
  }

  size_type size() const {
    return number_of_elements;
  }  // возвращает число элементов

  // публичные методы для изменения контейнера

  void push(T data) {  // checks whether the container is empty
    auto* tmp = new Container(data);
    if (beginning == nullptr) {
      beginning = tmp;
    } else {
      tmp->next = beginning;
      beginning = tmp;
    }
    number_of_elements++;
  }

  void pop() {  // removes the top element
    if (number_of_elements == 0) {
      throw std::out_of_range("Unable to pop from an empty Stack");
    }
    Container* next_node = beginning->next;
    if (beginning != nullptr) {
      delete beginning;
      beginning = nullptr;
    }
    beginning = next_node;
    number_of_elements--;
  }

  void swap(Stack<value_type>& s) {  // swaps the contents
    std::swap(beginning, s.beginning);
    std::swap(number_of_elements, s.number_of_elements);
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push(std::forward<Args>(args)), ...);
  };
};
}  // namespace s21

#endif
