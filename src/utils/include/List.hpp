#pragma once

namespace utils::containers {
#pragma once

#include <stdint.h>

class List_t;
class ListNode_t;

#define container_of(ptr, type, member) ((type*) \
  ((const char*)ptr - \
  (sizeof(type) - sizeof(((type*)(ptr))->member))))

#define node_link(obj) (ListNode_t*)(&obj.node)

class ListIterator;

class ListNode_t 
{
  ListNode_t* prev_;
  ListNode_t* next_;
  friend List_t;
  friend ListIterator;
public:
  ListNode_t()
  {
    prev_ = this;
    next_ = this;
  }
};

class ListIterator
{
public:
    using self_type = ListIterator;
    using iterator = self_type;
    using value_type = ListNode_t;
    using reference = ListNode_t&;
    using pointer = ListNode_t*;

  ListIterator()
    : elem_(nullptr) {}
  explicit ListIterator(pointer p)
    : elem_(p) {}

  pointer operator->() const { return elem_; }
  reference operator*() const { return *elem_; }
  iterator& operator++() { elem_ = elem_->next_; return *this; }
  iterator& operator--() { elem_ = elem_->prev_; return *this; }
  bool operator==(const iterator& iterator) const { return iterator.elem_ == elem_; }
  bool operator!=(const iterator& iterator) const { return !(*this == iterator);}

  //TODO: implement post increment, decrement

private:
  pointer elem_;
}; 

class List_t 
{
public: 
  using iterator = ListIterator::iterator;
  // using const_iterator = const ListIterator::iterator;
private:
  ListNode_t* head_;
  ListNode_t* tail_;

  iterator head;
  iterator tail;

  uint32_t size_;

public:
  List_t()
    : size_{0}{}

  iterator begin() const { return head; }
  iterator end() const { return tail; }
  auto size() const { return size_; }
  bool empty() const { return size_ == 0; }

  void append(ListNode_t* node)
  { 
    if (empty())
    {
      size_++;

      head = iterator(node);
      tail = iterator(node);

      return;
    }

    node->prev_ = &*tail;
    node->next_ = &*head;

    tail = iterator(node);
  }

  void insert(iterator iter, ListNode_t* node)
  {
    if (empty())
    {
      append(node);

      return;
    }

    size_++;

    node->prev_ = iter->prev_;
    node->next_ = &*iter;

    iter->prev_->next_ = node;
    iter->prev_ = node;

    update_head_and_tail(&*iter, node);
  }

  void erase(iterator iter)
  {
    if (empty())
      return;
    
    if (size() == 1)
    {
      size_--;
      head_ = nullptr;
      tail_ = nullptr;

      return;
    }

    size_--;
    iter->prev_ = iter->next_;
    iter->next_->prev_ = iter->prev_;

    if (iter == head)
    {
      head_ = iter->next_;
    }
    else if (iter == tail)
    {
      tail_ = iter->prev_;
    }

  }

private:
  void update_head_and_tail(ListNode_t* iter, ListNode_t* node)
  {
    if (iter == head_)
    {
      head_ = node;

      return;
    }

    if (iter == tail_)
    {
      tail_ = node;
    }
  }
};
}
