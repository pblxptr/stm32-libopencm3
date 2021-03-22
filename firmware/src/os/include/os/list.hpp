// #pragma once

// #define container_of(ptr, type, member) ((type*) \
//   ((const char*)ptr - \
//   (sizeof(type) - sizeof(((type*)ptr)->member))))

// namespace os::utils {
//   // struct List 
//   // {
//   //   using iter_t = List*;

//   //   struct List* next;
//   //   struct List* prev;
//   // };

//   // void list_init(List* list);
//   // List::iter_t list_begin(const List*);
//   // List::iter_t list_end(const List*);
//   // List::iter_t list_next(const List::iter_t);
//   // bool list_empty(const List*);
//   // void list_append(List* list, List* item);
//   // void list_insert(List::iter_t iter, List* item);
//   // void list_remove(List::iter_t iter);


//   class List
//   {
//     class List* next_;
//     class List* prev_;
//   public:
//     using iter_t = List*;

//     List();
//     iter_t begin() const;
//     iter_t begin();
//     iter_t end() const;
//     iter_t end();
//     iter_t next(const iter_t iter) const;
//     bool empty() const;
//     void append(List* item);
//     void insert(iter_t iter, List* item);
//     void remove(iter_t iter);
//   private:
//     void put_in_between(List::iter_t left, List::iter_t right, List* elem);
//   };

// }