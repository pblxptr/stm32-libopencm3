#pragma once

#include <stdint.h>
#include <type_traits>
#include <iterator>

namespace utils::containers {

class List;
class ListNode_t;

#define container_of(ptr, type, member) ((type*) \
  ((const char*)ptr - \
  (sizeof(type) - sizeof(((type*)(ptr))->member))))

#define make_link(obj) (utils::containers::ListNode_t*)(&(obj)->node)
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

class List;
class ListIterator;

class ListNode_t 
{
  ListNode_t* prev_;
  ListNode_t* next_;
  friend List;
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
    using iterator_category = std::bidirectional_iterator_tag;
    using self_type = ListIterator;
    using iterator = self_type;
    using value_type = ListNode_t;
    using reference = ListNode_t&;
    using pointer = ListNode_t*;
    using difference_type = std::ptrdiff_t;

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

class List //Rename to List
{
public: 
  using iterator = ListIterator::iterator;
  using const_iterator = const ListIterator::iterator;
private:
  ListNode_t shadowNode_;
  uint32_t size_;

public:
  List()
    : size_{0}{}
  List(const List&) = delete;
  List& operator=(const List&) = delete;

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

    // prev - iter - next
    // prev - node - iter - next

    iter->prev_->next_ = node;
    node->prev_ = iter->prev_;
    iter->prev_ = node;
    node->next_ = it_to_ptr(iter);

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
