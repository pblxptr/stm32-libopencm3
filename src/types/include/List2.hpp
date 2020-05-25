#pragma once

#define container_of(ptr, type, member) ((type*) \
  ((const char*)ptr - \
  (sizeof(type) - sizeof(((type*)(ptr))->member))))

// struct List {
//   struct List* next;
//   struct List* prev;
  
//   List()
//     : next(this), prev(this) {}
// };

