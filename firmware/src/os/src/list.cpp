#include <list.hpp>

using namespace os::utils;

namespace 
{

}

namespace os::utils
{
  List::List()
  {
    prev_ = this;
    next_ = this;
  }

  List::iter_t List::begin() const
  {
    return next_;
  }

  List::iter_t List::begin()
  {
    return next_;
  }

  List::iter_t List::end()
  {
    return this;
  }

  List::iter_t List::next(const iter_t iter) const
  {
    return iter->next_;
  }

  bool List::empty() const
  {
    return next_ == this;
  }
  
  void List::append(List* item)
  {
    const List::iter_t e = end();

    put_in_between(e->prev_, e, item);
  }

  void List::insert(List::iter_t iter, List* item)
  {
    item->prev_ = iter->prev_;
    item->next_ = iter;

    iter->prev_->next_ = item;
  }

  void List::remove(List::iter_t iter)
  {
    // i1 -> i2 -> i3
    // i1 -> i3

    iter->prev_->next_ = iter->next_;
    iter->next_->prev_ = iter->prev_;
  }

  void List::put_in_between(List::iter_t left, List::iter_t right, List* elem)
  {
    left->next_ = elem;
    right->prev_ = elem;

    elem->prev_ = left;
    elem->next_ = right; 
  }
}