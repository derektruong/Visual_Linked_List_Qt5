//Các Element là các phần tử(nút) của một List(danh sách liên kết đơn)
/***Trong header này sẽ xây dựng 2 class:
 * class Element để quản lý trường dữ liệu của một nút.
 * class List để quản lý các Element liên kết với nhau.
 * Dslk này là dslk đơn được quản lý bởi 2 con trỏ *pHead(nút đầu tiên) và *pTail(nút cuối cùng).
 * DSLK này được thiết kế để có thể phù hợp với mọi kiểu dữ liệu mà các nút muốn lưu trữ.
    -Điều này là nhờ sử dụng lập trình tổng quát(templates) trong ngôn ngữ C++.
    -Có thể lưu trữ cả những đối tượng từ các Class khác.
*/

#ifndef LIST_H
#define LIST_H
#include <iostream>
#include<main_widget.h>

template<class T>
class Element {
 public:
  Element(const T& value) : data_(value), pNext(NULL) {}
  ~Element() {}

  void        SetValue(const T& value) { data_ = value; }//Thay đổi "data_" của phần tử bằng "value" mới
  const T&    GetValue() const { return data_; }//Lấy dữ liệu từ một Element
  void        SetNext(Element<T>* next) { pNext = next; }//Thay đổi "data_" của phần tử mà con trỏ pNext đang trỏ tới
  Element<T>* GetNext() const { return pNext; }//Lấy dữ liệu từ một Element mà con trỏ pNext đang trỏ tới
    friend class Widget;//Tạo lớp bạn là Widgets

 private:
  Element();  // Ngăn chặn gọi constructor mặc định

  T           data_;
  Element<T>* pNext;
};

template <class T>
class List {
  public:
  List(): pHead(NULL), pTail(NULL), size(0) {}//Phương thức khởi tạo
  ~List();

  void resize(int size);
  void PushFront(const T& value);
  void PushBack (const T& value);
  void PopFront(T* value);
  void PopBack (T* value);

  const T& pos(int index);//Trả về phần tử tại vị trí "index"

  void insert(const int& pos,const T& value);
  void replace(int index,const T& value);
  void remove(const int& position);
  void clear();

  friend class Widget;//Tạo lớp bạn là Widgets
  private:
  int size=0;
  Element<T>* pHead;
  Element<T>* pTail;
};

template <class T>
List<T>::~List() {
  Element<T>* current = pHead;

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
// Thêm vào đầu
template <class T>
void List<T>::PushFront(const T& value) {
  Element<T>* element = new( std::nothrow ) Element<T>(value);

  if( element ) {
    if( !pHead ) {
      // Special case, list is empty
        size++;
      pHead = element;
      pTail = element;
    }
    else {
        size++;
      element->SetNext(pHead);
      pHead = element;
    }
    return;
  }
  else {
    return; // Error allocating memory
  }
}

// Thêm vào cuối
template <class T>
void List<T>::PushBack(const T& value) {
  Element<T>* element = new (std::nothrow) Element<T>(value);

  if( element ) {
    if( !pHead ) {
      // Special case, list is empty
        size++;
      pHead = element;
      pTail = element;
    }
    else {
        size++;
      pTail->SetNext(element);
      pTail = element;
    }
    return;
  }
  else {
    return;
  }
}

// Lấy phần tử đầu
template <class T>
void List<T>::PopFront(T* value) {
  if( value && pHead ) {
    *value = pHead->GetValue();

    Element<T>* new_head = pHead->GetNext();
    size--;
    delete pHead;
    pHead = new_head;

    return;
  }
  else
    return; // Error: nullptr passed as parameter or list empty
}

// Lấy phần tử cuối
template <class T>
void List<T>::PopBack(T* value) {
  if( value && pTail ) {
    *value = pTail->GetValue();

    // Special case: one element list
    if( pHead == pTail ) {
      size--;
      delete pHead;
      pHead = NULL;
      pTail = NULL;
    }
    else {
      Element<T>* new_tail;

      new_tail = pHead;

      while( new_tail->GetNext() != pTail ) // Skip elements till the element before tail
        new_tail = new_tail->GetNext();

      new_tail->SetNext(NULL);
      size--;
      delete pTail;
      pTail = new_tail;
    }
    return;
  }
  else
    return; // Error: nullptr passed as parameter or list empty
}

template <class T>
const T& List<T>::pos(int index){
    int i=0;
    Element<T>* pTemp = pHead;
    while(pTemp!=nullptr){
      if(i==index){
          return pTemp->GetValue();
          break;
      }
      pTemp=pTemp->GetNext();
      i++;
    }
}

// Thêm phần tử bất kỳ vào vị trí "pos"
template <class T>
void List<T>::insert(const int& pos,const T& value) {
    if( pos < 0 )
        return;

      if (pos == 0) { // Special case: position = 0, insert into head
          PushFront(value);
          return;
      }

      Element<T>* element_before = pHead;

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

      if( element_before == pTail ) // Special case: insert at the end
        pTail = new_element;

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

  if( !pHead )
    return; // List empty

  Element<T>* target = pHead;

  if( position==0 ) {// Special case: position = 0, delete head
    pHead = pHead->GetNext();
    size--;
    delete target;

    return;
  }

  Element<T>* element_before = pHead;
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
  if( target == pTail )
      size--;
    pTail = element_before;

  delete target;

  return;
}
//Clear all
template <class T>
void List<T>::clear(){
    for(int i=0;i<size;i++){
        remove(i);
    }
    size=0;
}

#endif // LIST_H
