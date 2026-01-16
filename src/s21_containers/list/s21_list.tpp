namespace s21 {

template <typename T>
T& s21_List<T>::back() {
  if (empty()) throw std::out_of_range("List is empty");
  return tail->value;
}

template <typename T>
T& s21_List<T>::front() {
  if (empty()) throw std::out_of_range("List is empty");
  return head->value;
}

template <typename T>
void s21_List<T>::clear() {
  while (tail != nullptr) pop_front();
  size_ = 0;
}

template <typename T>
void s21_List<T>::pop_back() {
  if (tail != nullptr) {
    s21_List_Node<T>* temp = tail->prev;
    delete tail;
    tail = temp;
    size_--;
    if (!size_) head = nullptr;
  }
}

template <typename T>
void s21_List<T>::pop_front() {
  if (head != nullptr) {
    s21_List_Node<T>* temp = head->next;
    delete head;
    head = temp;
    size_--;
    if (!size_) tail = nullptr;
  }
}

template <typename T>
bool s21_List<T>::empty() const {
  if (tail == head && tail == nullptr)
    return true;
  else
    return false;
}

template <typename T>
size_t s21_List<T>::size() const {
  return size_;
}

template <typename T>
size_t s21_List<T>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(T);
}

template <typename T>
void s21_List<T>::emplace(ListIterator Where, T val) {
  if (Where.ptr() == this->head) {
    emplace_front(val);
    Where = begin();
  } else {
    s21_List_Node<T>* el =
        new s21_List_Node<T>(Where.ptr()->prev, val, Where.ptr());
    el->next = Where.ptr();  // to avoid error message
    size_++;
  }
}

template <typename T>
void s21_List<T>::emplace_back(T val) {
  push_back(val);
}

template <typename T>
void s21_List<T>::emplace_front(T val) {
  push_front(val);
}

template <typename T>
typename s21_List<T>::ListIterator s21_List<T>::erase(ListIterator Where) {
  if (Where == begin()) {
    pop_front();
    Where = begin();
  } else if (Where == end()) {
    pop_back();
    Where = end() + 1;
  } else {
    s21_List_Node<T>* temp = Where.ptr()->next;
    delete Where.ptr();
    Where.ptr(temp);
    this->size_--;
  }
  return Where;
}

template <typename T>
typename s21_List<T>::ListIterator s21_List<T>::erase(ListIterator first,
                                                      ListIterator last) {
  while (first != last) first = erase(first);
  return first;
}

template <typename T>
void s21_List<T>::push_back(T val) {
  if (size_) {
    s21_List_Node<T>* el = new s21_List_Node<T>(tail, val);
    tail = el;
  } else {
    s21_List_Node<T>* el = new s21_List_Node<T>(val);
    head = el;
    tail = el;
  }
  size_++;
}

template <typename T>
void s21_List<T>::push_front(T val) {
  if (size_) {
    s21_List_Node<T>* el = new s21_List_Node<T>(val, head);
    head = el;
  } else {
    s21_List_Node<T>* el = new s21_List_Node<T>(val);
    head = el;
    tail = el;
  }
  size_++;
}

template <typename T>
void s21_List<T>::resize(size_t Newsize) {
  while (Newsize > size_) push_back(T());
  while (Newsize < size_) pop_back();
}

template <typename T>
void s21_List<T>::resize(size_t Newsize, T val) {
  while (Newsize > size_) push_back(val);
  while (Newsize < size_) pop_back();
}

template <typename T>
void s21_List<T>::reverse() {
  s21_List<T>* temp = new s21_List<T>();
  while (size()) {
    temp->push_front(head->value);
    pop_front();
  }
  while (temp->size()) {
    push_front(temp->tail->value);
    temp->pop_back();
  }
  delete temp;
}

template <typename T>
void s21_List<T>::swap(s21_List<T>& other) {
  int temp = (int)other.size();
  while (!this->empty()) {
    other.push_back(this->head->value);
    pop_front();
  }
  for (int i = 0; i < temp; i++) {
    push_back(other.head->value);
    other.pop_front();
  }
}

template <typename T>
void s21_List<T>::merge(s21_List<T>& other) {
  while (!other.empty()) {
    push_back(other.head->value);
    other.pop_front();
  }
  sort();
}

template <typename T>
void s21_List<T>::splice(typename s21_List<T>::ListConstIterator pos,
                         s21_List<T>& other) {
  while (!other.empty()) {
    emplace(pos, other.front());
    other.pop_front();
  }
}

template <typename T>
void s21_List<T>::unique() {
  ListIterator pos = begin();
  for (int j = 0; j < (int)size(); j++) {
    T val = *pos;
    for (int i = 1; i < (int)size() - j; i++) {
      if (val == *(pos + i)) {
        erase(pos + i);
        i--;
      }
    }
    pos++;
  }
}

template <typename T>
void s21_List<T>::sort() {
  if (size() < 2) return;
  for (int i = 0; i < (int)size(); i++) {
    ListIterator pos = begin() + i;
    for (int j = 0; j < (int)size() - 1; j++) {
      ListIterator temp = begin() + j;
      if (*temp > *(temp + 1)) {
        emplace(temp, *(temp + 1));
        temp = erase(temp + 1);
      }
    }
  }
}

template <typename T>
typename s21_List<T>::ListIterator s21_List<T>::begin() {
  return ListIterator(head);
}

template <typename T>
typename s21_List<T>::ListIterator s21_List<T>::end() {
  return ListIterator(tail);
}

template <typename T>
const typename s21_List<T>::ListConstIterator s21_List<T>::cbegin() {
  return ListConstIterator(head);
}

template <typename T>
const typename s21_List<T>::ListConstIterator s21_List<T>::cend() {
  return ListConstIterator(tail);
}

template <typename T>
typename s21_List<T>::ListIterator s21_List<T>::insert(
    typename s21_List<T>::ListIterator pos, const T& value) {
  if (pos == begin()) {
    emplace_front(value);
    pos = begin();
  } else {
    emplace(pos, value);
  }
  return pos;
}

template <typename T>
template <typename... Args>
typename s21_List<T>::ListIterator s21_List<T>::insert_many(
    typename s21_List<T>::ListConstIterator pos, Args&&... args) {
  ListIterator it(pos.ptr());
  for (const auto& arg : {args...}) {
    insert(it, arg);
  }
  return it;
}

template <typename T>
template <typename... Args>
void s21_List<T>::insert_many_back(Args&&... args) {
  if constexpr (sizeof...(args) > 0) {
    for (const auto& arg : {args...}) {
      push_back(arg);
    }
  }
}

template <typename T>
template <typename... Args>
void s21_List<T>::insert_many_front(Args&&... args) {
  if constexpr (sizeof...(args) > 0) {
    for (const auto& arg : {args...}) {
      push_front(arg);
    }
  }
}

}  // namespace s21