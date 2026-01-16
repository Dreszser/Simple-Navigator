#ifndef S21TREE_H_
#define S21TREE_H_

#include <iostream>
#include <limits>

namespace s21 {

enum Colour { RED, BLACK };

template <typename T>
struct Node {
  T value;
  Node* left;
  Node* right;
  Node* parent;
  Colour colour;

  /* Node constructor */
  Node(T newdata)
      : value(newdata),
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        colour(RED) {}
};

template <typename T>
class TreeIterator {
 public:
  TreeIterator() : currentNode_(nullptr){}; /* Iterator constructor */
  TreeIterator(Node<T>* current)
      : currentNode_(current){}; /* constructor based on existing node */
  TreeIterator(const TreeIterator& other); /* Copy constructor */
  TreeIterator(TreeIterator&& other);      /* Move constructor */

  TreeIterator& operator=(const TreeIterator& other);
  TreeIterator& operator=(TreeIterator&& other) noexcept;

  bool operator==(TreeIterator& other) const;
  bool operator!=(TreeIterator& other) const;
  bool operator==(const TreeIterator& other) const;
  bool operator!=(const TreeIterator& other) const;
  TreeIterator& operator++();
  TreeIterator& operator--();
  TreeIterator operator++(int);
  TreeIterator operator--(int);

  /* достает value из узла */
  T& operator*();

  Colour getColour();

  /* Получает указатель на узел на который указывает итератор для
            дальнейших операций над ним */
  Node<T>* getCurrentNode() const;

 private:
  Node<T>* currentNode_;
};

template <typename T>
class ConstTreeIterator : public TreeIterator<T> {
 public:
  using value_type = T;
  using const_reference = const value_type&;

  ConstTreeIterator() : TreeIterator<T>(){};
  ConstTreeIterator(Node<T>* node) : TreeIterator<T>(node){};
  ConstTreeIterator(const TreeIterator<T>& iter) : TreeIterator<T>(iter){};
  ConstTreeIterator(const ConstTreeIterator<T>& iter) : TreeIterator<T>(iter){};
  ConstTreeIterator(ConstTreeIterator&& iter)
      : TreeIterator<T>(std::move(iter)){};

  ConstTreeIterator& operator=(const ConstTreeIterator& other);
  ConstTreeIterator& operator=(ConstTreeIterator&& other) noexcept;

  const_reference operator*() const;

 protected:
  /* Для того, чтобы нельзя было получить текущий узел вне области
   * ConstTreeIterator */
  using TreeIterator<T>::getCurrentNode;
};

template <typename T>
class Tree {
 public:
  using iterator = TreeIterator<T>;
  using const_iterator = ConstTreeIterator<T>;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

  /* Constructors and destructor */
  Tree();
  Tree(std::initializer_list<value_type> const& items);
  Tree(const Tree& other);
  Tree(Tree&& other) noexcept;
  ~Tree();

  /* Capacity */

  /* checks whether the container is empty
   * true - container is empty
   * false - not empty */
  bool empty();
  /* returns the number of elements */
  size_type size();
  /* returns the maximum possible number of elements */
  size_type max_size();

  /* Member functions */

  /* Печать дерева для дебага */
  void print();
  void printBT(const std::string& prefix, const Node<T>* node, bool isLeft);
  void printBT(const Node<T>* node);

  Node<T>* getRoot() { return root_; }
  /* Стандартная вставка значения в дерево, сначала производится поиск
   * места, куда нужно вставить значение, потом вставка и обработка
   * указателей на родителей и детей Возвращается пара из итератора
   * указывающего на новую ноду и флаг - удачно прошла вставка или
   * нет(неудачно только если ключи в контейнере должны быть уникальными,
   * как в set, а мы попытаемся вставить знаение повторно) */
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insertNonUnique(const value_type& value);
  /* Вспомогательные функции для вставки, соответственно вставка уникальных
   * значений и вставка для мультисета которая вставит значение не смотря на
   * повторы */
  Node<T>* insert(Node<T>* node, Node<T>* newNode, bool* flag, iterator* it);
  Node<T>* insertNonUnique(Node<T>* node, Node<T>* newNode);
  /* Проверка на нарушение правил красно-черного дерева и дальнейшая
   * балансировка после вставки ноды */
  void balanceTree(Node<T>* node);
  /* Обновление крайнего левого узла(минимальное значение) и крайнего
   * правого(максимальное значение) после вставки */
  void updateExtremes(Node<T>* node);
  /* Почти то же самое, только перед удалением узла */
  void updateExtremesOnDeletion(Node<T>* node);
  /* Левый и правый поворот поддерева, node - корень поддерева, относительно
   * него и производится поворот */
  void leftRotate(Node<T>* node);
  void rightRotate(Node<T>* node);
  /* clears the contents */
  void clear();
  /* Удаление узла по итератору */
  void erase(iterator pos);
  /* Обмен содержимым между деревьями */
  void swap(Tree& other);
  /* Вставка содержимого одного дерева в другое */
  void merge(Tree& other);
  /* Вспомогательные функции для удаления узла
   * transplant - грубо говоря замена одного узла на другой,
   * но на этом этапе не обрабатываются указатели в данных узлах */
  void transplant(Node<T>* u, Node<T>* v);
  /* Основная функция по обработке нарушений правил красно-черного дерева
   * после удаления узла */
  void fixDelete(Node<T>* node);
  /* fixDelete разделенный на две функции, чтобы не было одной громоздкой
   * функции, fixLeft обрабатывает нарушения если удаленный узел был левым
   * ребенком, а fixRight - если правым */
  void fixLeft(Node<T>** node, bool* flag);
  void fixRight(Node<T>** node, bool* flag);
  /* Поиск минимального значения поддерева(самого левого узла) */
  Node<T>* minimum(Node<T>* node) const;
  /* Поиск максимального значения поддерева */
  Node<T>* maximum(Node<T>* node) const;
  /* Operators overloads */
  Tree& operator=(const Tree& other);
  Tree& operator=(Tree&& other);

  /* Iterators */

  /* begin обращается к leftMost_ узлу - самый левый узел в дереве, а
   * соответственно самое маленькое значение */
  iterator begin();
  /* end обращается к endNode_ - теоретический узел, лежащий после самого
   * правого узла. У меня в нем лежит указатель на максимальный
   * узел(endNode_->parent), для того, чтобы реализовать декремент из end() */
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  /* Поиск узла по ключу */
  iterator find(const_reference key);
  /* Checks if the container contains element with specific key */
  bool contains(const_reference key);

  iterator lower_bound(const_reference key);
  iterator upper_bound(const_reference key);

 private:
  Node<T>* root_;
  Node<T>* leftMost_;
  Node<T>* endNode_;
  size_type size_;

  /* Функция рекурсивного удаления узлов для деструктора */
  void DestroyTree(Node<T>* node);
};

}  // namespace s21

#include "S21Tree.tpp"

#endif  // S21TREE_H_