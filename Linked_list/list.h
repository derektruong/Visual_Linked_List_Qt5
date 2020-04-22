#ifndef LIST_H
#define LIST_H
#include <iostream>
#include<main_widget.h>

template<class T>
class Element {
 public:
  Element(const T& value) : data_(value), next_(NULL) {}
  ~Element() {}

  void        SetValue(const T& value) { data_ = value; }
  const T&    GetValue() const { return data_; }
  void        SetNext(Element<T>* next) { next_ = next; }
  Element<T>* GetNext() const { return next_; }
    friend class Widgets;
  void        Print() const { std::cout << data_ << "\t"; }

 private:
  Element();  // Prevent calling the default ctor

  T           data_;
  Element<T>* next_;
};

template <class T>
class List {
 public:
  List(): head_(NULL), tail_(NULL), size(0) {}
  ~List();

  void resize(int size);
  void PushFront(const T& value);
  void PushBack (const T& value);
  void PopFront(T* value);
  void PopBack (T* value);

  const T& pos(int index);
  void Print() const;

  void insert(const int& pos,const T& value);
  void replace(int index,const T& value);
  void remove(const int& position);
  void clear();


  int  Find(const int& value) const;
  const T& Get (const int& position, T* value);

  friend class Widgets;
private:
  int size=0;
  Element<T>* head_;
  Element<T>* tail_;
};

template <class T>
List<T>::~List() {
  Element<T>* current = head_;

  while ( current ) {
    Element<T>* next = current->GetNext();
    delete(current);
    current = next;
  }
}
template <class T>
void List<T>::resize(int sizee){
    for(int i=0;i<sizee;++i){
        insert(i,0);
    }
}
// O(1)
template <class T>
void List<T>::PushFront(const T& value) {
  Element<T>* element = new( std::nothrow ) Element<T>(value);

  if( element ) {
    if( !head_ ) {
      // Special case, list is empty
        size++;
      head_ = element;
      tail_ = element;
    }
    else {
        size++;
      element->SetNext(head_);
      head_ = element;
    }
    return;
  }
  else {
    return; // Error allocating memory
  }
}

// O(1)
template <class T>
void List<T>::PushBack(const T& value) {
  Element<T>* element = new (std::nothrow) Element<T>(value);

  if( element ) {
    if( !head_ ) {
      // Special case, list is empty
        size++;
      head_ = element;
      tail_ = element;
    }
    else {
        size++;
      tail_->SetNext(element);
      tail_ = element;
    }
    return;
  }
  else {
    return;
  }
}

// O(1)
template <class T>
void List<T>::PopFront(T* value) {
  if( value && head_ ) {
    *value = head_->GetValue();

    Element<T>* new_head = head_->GetNext();
    size--;
    delete head_;
    head_ = new_head;

    return;
  }
  else
    return; // Error: nullptr passed as parameter or list empty
}

// O(n)
template <class T>
void List<T>::PopBack(T* value) {
  if( value && tail_ ) {
    *value = tail_->GetValue();

    // Special case: one element list
    if( head_ == tail_ ) {
      size--;
      delete head_;
      head_ = NULL;
      tail_ = NULL;
    }
    else {
      Element<T>* new_tail;

      new_tail = head_;

      while( new_tail->GetNext() != tail_ ) // Skip elements till the element before tail
        new_tail = new_tail->GetNext();

      new_tail->SetNext(NULL);
      size--;
      delete tail_;
      tail_ = new_tail;
    }
    return;
  }
  else
    return; // Error: nullptr passed as parameter or list empty
}

template <class T>
const T& List<T>::pos(int index){
    int i=0;
    Element<T>* pTemp = head_;
    while(pTemp!=nullptr){
      if(i==index){
          return pTemp->GetValue();
          break;
      }
      pTemp=pTemp->GetNext();
      i++;
    }
}
// O(n)
template <class T>
void List<T>::Print() const {
  Element<T>* e;
  for(e = head_; e; e = e->GetNext() )
    e->Print();
}

// best O(1), avg O(n), wst O(n)
template <class T>
void List<T>::insert(const int& pos,const T& value) {
    if( pos < 0 )
        return;

      if (pos == 0) { // Special case: position = 0, insert into head
          PushFront(value);
          return;
      }

      Element<T>* element_before = head_;

      for(int count = 0; count < pos-1 ; ++count ) {
        element_before = element_before->GetNext();

        if( !element_before )
          return; // Out of bounds
      }

      Element<T>* new_element = new (std::nothrow) Element<T>(value);
      if( !new_element ) return;
      size++;
      new_element->SetNext(element_before->GetNext());
      element_before->SetNext(new_element);

      if( element_before == tail_ ) // Special case: insert at the end
        tail_ = new_element;

      return;

}
//replace
template <class T>
void List<T>::replace(int index,const T& value){
    if(index<size){
        insert(index,value);
        remove(index+1);
    }
    else insert(index,value);
}
//remove
template <class T>
void List<T>::remove(const int& position) {
  if( position < 0 )
    return;

  if( !head_ )
    return; // List empty

  Element<T>* target = head_;

  if( position==0 ) {// Special case: position = 0, delete head
    head_ = head_->GetNext();
    size--;
    delete target;

    return;
  }

  Element<T>* element_before = head_;
  for(int count = 0; count < position - 1; ++count ) {
    element_before = element_before->GetNext();

    if( !element_before )
      return; // Out of bounds
  }

  target = element_before->GetNext();

  if( !target )
    return; // Out of bounds

  element_before->SetNext(target->GetNext());
  size--;
  if( target == tail_ )
      size--;
    tail_ = element_before;

  delete target;

  return;
}

template <class T>
void List<T>::clear(){
    for(int i=0;i<size;i++){
        remove(i);
    }
    size=0;
}

template <class T>
int List<T>::Find(const int& value) const {
  int position = -1;

  Element<T>* e = head_;

  for(int count = 0; e; e = e->GetNext(), ++count ) {
    if( e->GetValue() == value ) {
      position = count;
      break;
    }
  }

  return position;
}

template <class T>
const T& List<T>::Get(const int& position, T* value) {
  if( position < 0 || !value )
    return true; // invalid input

  Element<T>* e = head_;

  for(int count = 0; e && count < position; e = e->GetNext(), ++count ) ;

  if( !e )
    return true;

  *value = e->GetValue();

  return false;
}

#endif // LIST_H
