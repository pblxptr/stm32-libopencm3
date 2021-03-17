#include <list.hpp>

using namespace os::utils;

namespace 
{
  void put_in_between(List::iter_t left, List::iter_t right, List* elem)
  {
    left->next = elem;
    right->prev = elem;

    elem->prev = left;
    elem->next = right; 
  }
}

namespace os::utils::list 
{
  void list_init(List* l)
  {
    l->prev = l;
    l->next = l;
  }

  List::iter_t list_begin(List* l)
  {
    return l->next;
  }

  List::iter_t list_end(List* l)
  {
    return l;
  }

  List::iter_t list_next(List::iter_t iter)
  {
    return iter->next;
  }

  bool list_empty(const List* l)
  {
    return l->next == l;
  }

  void list_append(List* l, List* item)
  {
    const List::iter_t e = list_end(l);

    put_in_between(e->prev, e, item);
  }

  void list_insert(List::iter_t iter, List* item)
  {
    item->prev = iter->prev;
    item->next = iter;

    iter->prev->next = item;
  }

  void list_remove(List::iter_t iter)
  {
    // i1 -> i2 -> i3
    // i1 -> i3

    iter->prev->next = iter->next;
    iter->next->prev = iter->prev;
  }
}