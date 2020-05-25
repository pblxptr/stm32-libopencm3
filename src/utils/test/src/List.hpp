#pragma once

#include <stdint.h>

class List_t;
class ListNode_t;

#define container_of(ptr, type, member) ((type*) \
  ((const char*)ptr - \
  (sizeof(type) - sizeof(((type*)(ptr))->member))))

#define node_link(obj) (ListNode_t*)(&obj.node)



class ListNode_t 
{
  ListNode_t* prev_;
  ListNode_t* next_;
  friend List_t;
public:
  ListNode_t()
  {
    prev_ = this;
    next_ = this;
  }

  ListNode_t& operator++()
  {
    return *next_;
  }

  ListNode_t& operator--()
  {
    return *prev_;
  }
};

class List_t 
{
  ListNode_t* head_;
  ListNode_t* tail_;
  uint32_t size_;
public: 
  using iterator = ListNode_t*;
  using const_iterator = const ListNode_t*;

  List_t()
    : size_{0}, 
      head_{nullptr}, 
      tail_{nullptr} {}

  iterator begin() { return head_; }
  iterator end() { return tail_; }
  auto size() { return size_; }
  bool empty() { return size_ == 0; }

  void append(ListNode_t* node)
  {
    size_++;

    if (tail_ ==  nullptr)
    {
      head_ = node;
      tail_ = node;

      return;
    }

    node->prev_ = tail_;
    node->next_ = head_;

    tail_ = node;
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
    node->next_ = iter;

    iter->prev_->next_ = node;
    iter->prev_ = node;

    update_head_and_tail(iter, node);
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

    if (iter == head_)
    {
      head_ = iter->next_;
    }
    else if (iter == tail_)
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