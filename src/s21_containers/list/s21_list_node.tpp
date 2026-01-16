namespace s21 {

template <typename T>
s21_List_Node<T>::s21_List_Node(T value) {
  this->value = value;
  prev = nullptr;
  next = nullptr;
}

template <typename T>
s21_List_Node<T>::s21_List_Node(s21_List_Node* prev, T value) {
  this->value = value;
  this->prev = prev;
  if (prev != nullptr) prev->next = this;
  this->next = nullptr;
}

template <typename T>
s21_List_Node<T>::s21_List_Node(T value, s21_List_Node* next) {
  this->value = value;
  this->prev = nullptr;
  if (next != nullptr) next->prev = this;
  this->next = next;
}

template <typename T>
s21_List_Node<T>::s21_List_Node(s21_List_Node* prev, T value,
                                s21_List_Node* next) {
  this->value = value;
  this->prev = prev;
  this->next = next;
  if (next != nullptr) next->prev = this;
  if (prev != nullptr) prev->next = this;
}

template <typename T>
s21_List_Node<T>::~s21_List_Node() {
  if (prev) prev->next = next;
  if (next) next->prev = prev;
  prev = nullptr;
  next = nullptr;
}
}  // namespace s21