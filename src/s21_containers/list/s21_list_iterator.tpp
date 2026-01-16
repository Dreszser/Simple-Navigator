namespace s21 {

template <typename T>
s21_List<T>::ListIterator::ListIterator() : ptr_(nullptr) {}

template <typename T>
s21_List<T>::ListIterator::ListIterator(s21_List_Node<T>* ptr) : ptr_(ptr) {}

template <typename T>
s21_List<T>::ListIterator::ListIterator(ListIterator* iter)
    : ptr_(iter->ptr_) {}

template <typename T>
s21_List<T>::ListIterator::~ListIterator() {}

template <typename T>
T& s21_List<T>::ListIterator::operator*() {
  return this->ptr_->value;
}

template <typename T>
T s21_List<T>::ListConstIterator::operator*() const {
  return this->ptr()->value;
}

template <typename T>
s21_List_Node<T>* s21_List<T>::ListIterator::ptr() const {
  return ptr_;
}

template <typename T>
void s21_List<T>::ListIterator::ptr(s21_List_Node<T>* p) {
  ptr_ = p;
}

template <typename T>
typename s21_List<T>::ListIterator s21_List<T>::ListIterator::operator++(int) {
  ListIterator temp(this->ptr_);
  this->ptr_ = this->ptr_->next;
  return temp.ptr_;
}

template <typename T>
typename s21_List<T>::ListIterator s21_List<T>::ListIterator::operator--(int) {
  ListIterator temp(this->ptr_);
  this->ptr_ = this->ptr_->prev;
  return temp.ptr_;
}

template <typename T>
typename s21_List<T>::ListIterator& s21_List<T>::ListIterator::operator++() {
  if (this->ptr_ != nullptr && this->ptr_->next != nullptr)
    this->ptr_ = this->ptr_->next;
  return *this;
}

template <typename T>
typename s21_List<T>::ListIterator& s21_List<T>::ListIterator::operator--() {
  this->ptr_ = this->ptr_->prev;
  return *this;
}

template <typename T>
bool s21_List<T>::ListIterator::operator==(
    const s21_List<T>::ListIterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename T>
bool s21_List<T>::ListIterator::operator!=(
    const s21_List<T>::ListIterator& other) const {
  return ptr_ != other.ptr_;
}

template <typename T>
typename s21_List<T>::ListIterator s21_List<T>::ListIterator::operator+(int i) {
  ListIterator temp(this->ptr_);
  while (i > 0) {
    temp++;
    i--;
  }
  return temp.ptr_;
}

template <typename T>
typename s21_List<T>::ListIterator s21_List<T>::ListIterator::operator-(int i) {
  ListIterator temp(this->ptr_);
  while (i > 0) {
    temp--;
    i--;
  }
  return temp.ptr_;
}

}  // namespace s21