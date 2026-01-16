#ifndef S21_LIST_H
#define S21_LIST_H
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class s21_List_Node;

template <typename T>
class s21_List {
 public:
  class ListIterator;
  class ListConstIterator;

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

  // constructers
  s21_List();
  s21_List(int x);
  s21_List(std::initializer_list<T> const& items);
  s21_List(const s21_List<T>& other);
  s21_List(s21_List<T>&& other);
  ~s21_List();

  T& front();
  T& back();
  ListIterator begin();
  ListIterator end();
  const ListConstIterator cbegin();
  const ListConstIterator cend();

  void clear();
  void pop_back();
  void pop_front();
  ListIterator erase(ListIterator Where);
  ListIterator erase(ListIterator first, ListIterator last);

  void emplace(ListIterator Where, T val);
  void emplace_back(T val);
  void emplace_front(T val);
  void push_back(T val);
  void push_front(T val);

  ListIterator insert(ListIterator pos, const T& value);
  template <class... Args>
  ListIterator insert_many(ListConstIterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);

  bool empty() const;
  size_t size() const;
  size_t max_size();
  void resize(size_t Newsize);
  void resize(size_t Newsize, T val);
  void reverse();
  void swap(s21_List<T>& other);
  void merge(s21_List<T>& other);
  void splice(ListConstIterator pos, s21_List<T>& other);
  void unique();
  void sort();

 private:
  s21_List_Node<T>* tail;
  s21_List_Node<T>* head;
  size_t size_;
};

template <typename T>
class s21_List_Node {
 public:
  T value;
  s21_List_Node<T>* prev;
  s21_List_Node<T>* next;

  s21_List_Node(T value);
  s21_List_Node(s21_List_Node* prev, T value);
  s21_List_Node(T value, s21_List_Node* next);
  s21_List_Node(s21_List_Node* prev, T value, s21_List_Node* next);
  ~s21_List_Node();
};

template <typename T>
class s21_List<T>::ListIterator {
 public:
  ListIterator();
  ListIterator(s21_List_Node<T>* ptr);
  ListIterator(ListIterator* iter);
  ~ListIterator();

  T& operator*();
  ListIterator operator++(int);
  ListIterator operator--(int);
  ListIterator& operator++();
  ListIterator& operator--();
  ListIterator operator+(int i);
  ListIterator operator-(int i);
  s21_List_Node<T>* ptr() const;
  void ptr(s21_List_Node<T>* p);
  bool operator==(const ListIterator& other) const;
  bool operator!=(const ListIterator& other) const;

 private:
  s21_List_Node<T>* ptr_;
};

template <typename T>
class s21_List<T>::ListConstIterator : public ListIterator {
 public:
  ListConstIterator(const ListIterator ptr_) : ListIterator(ptr_) {}
  T operator*() const;
};
}  // namespace s21

#include "constructers.tpp"
#include "s21_list.tpp"
#include "s21_list_iterator.tpp"
#include "s21_list_node.tpp"

#endif  // S21_LIST_H
