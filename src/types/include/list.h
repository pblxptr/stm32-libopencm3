#pragma once

#include <stdbool.h>

//TODO: Move functions to .c, remove inline static in header 

#define container_of(ptr, type, member) ((type*) \
  ((const char*)ptr - \
  (sizeof(type) - sizeof(((type*)(ptr))->member))))

typedef struct _list_t {
  struct _list_t* next;
  struct _list_t* prev;
} list_t;

static void _list_put_between(list_t* left, list_t* right, list_t* elem);

static inline void list_init(list_t* l)
{
  l->next = l;
  l->prev = l;
}

static inline list_t* list_begin(list_t* head)
{
  return head->next; 
}

static inline bool list_end(list_t* head, list_t* iter)
{
  return iter == head;
}

static void list_append(list_t* head, list_t* elem)
{
  list_t* iter = list_begin(head);

  while (!list_end(head, iter)) {
    iter = iter->next;
  }

  _list_put_between(iter, iter->next, elem);
}

static void list_remove(list_t* iter)
{
  iter->prev->next = iter->next;
  iter->next->prev = iter->prev;
}

static void _list_put_between(list_t* left, list_t* right, list_t* elem)
{
  left->next = elem;
  right->prev = elem;

  elem->next = right;
  elem->prev = left;  
}