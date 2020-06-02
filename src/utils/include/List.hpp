#pragma once

namespace utils::containers {
#include <stdint.h>

class List_t;
class ListNode_t;

#define container_of(ptr, type, member) ((type*) \
  ((const char*)ptr - \
  (sizeof(type) - sizeof(((type*)(ptr))->member))))

#define make_link_ptr(obj) (utils::containers::ListNode_t*)(&(obj).node)
#define make_link_ref(obj) (utils::containers::ListNode_t&)((obj).node)
#define it_to_ptr(it) (&*it)

template<class T>
constexpr inline ListNode_t* node_link_p(T& obj) 
{
  return &obj.node;
}

template<class T>
constexpr inline ListNode_t& node_link_r(T& obj)
{
  return obj.node;
}

class List_t;
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

  bool operator==(const ListNode_t& rhs) const
  {
    return this->prev_ == rhs.prev_ && 
           this->next_ == rhs.next_;
  }

  bool operator!=(const ListNode_t& rhs) const
  {
    return !(*this == rhs);
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
    : elem_{nullptr} {}
  explicit ListIterator(pointer p)
    : elem_{p} {}

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
  using const_iterator = const ListIterator::iterator;
private:
  ListNode_t shadowNode_;
  uint32_t size_;

public:
  List_t()
    : size_{0}{}
  List_t(const List_t&) = delete;
  List_t& operator=(const List_t&) = delete;

  iterator begin() { return iterator(shadowNode_.next_); }
  iterator end()  { return iterator(&shadowNode_); }
  auto size() const { return size_; }
  bool empty() const { return size_ == 0; }

  void append(ListNode_t* node)
  { 
    node->next_ = &shadowNode_;
    node->prev_ = shadowNode_.prev_;

    if (size_++ == 0)
    {
      shadowNode_.next_ = node;
      shadowNode_.prev_ = node;
      return;
    }

    shadowNode_.prev_->next_ = node;
    shadowNode_.prev_ = node;
  }

  iterator insert(iterator iter, ListNode_t* node)
  {
    if (empty() || iter == end())
    {
      append(node);

      return iterator(node);
    }


    iter->prev_->next_ = node;
    node->prev_ = iter->prev_;
    node->next_ = &*iter;

    size_++;

    return iterator(node);
  }

  iterator erase(iterator iter)
  {
    if (empty())
      return iter;

    --size_;

    iter->next_->prev_ = iter->prev_;
    iter->prev_->next_ = iter->next_;

    return iterator(iter->prev_->next_);
  }
};
}
