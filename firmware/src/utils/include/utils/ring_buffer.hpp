#pragma once

#include <stdint.h>
#include <cstddef>
#include <algorithm>

namespace utils::containers
{
class RingBuffer
{
public:
  class Iterator
  {
  public:
    using self = Iterator;
    using value_type = uint8_t;
    using difference_type = std::ptrdiff_t;
    using pointer = uint8_t*;
    using reference = uint8_t&;

    explicit Iterator(pointer ptr) : ptr_{ptr}  {}

    self operator++() { ptr_++; return *this; }
    self operator++(int) { ptr_++; return *this; }
    reference operator*() { return *ptr_; }
    pointer operator->() { return ptr_; }
    bool operator==(const self& rhs) { return ptr_ == rhs.ptr_; }
    bool operator!=(const self& rhs) { return ptr_ != rhs.ptr_; }
  protected:
    pointer ptr_;
  };

  class CircularIterator : public Iterator
  { 
    using self = CircularIterator;
  public:
    
    CircularIterator(pointer ptr, pointer begin, pointer end)
      : Iterator{ptr}
      , begin_{begin}
      , end_{end} { }

    self operator++() 
    {
      if (++ptr_ == end_)
      {
        ptr_ = begin_;
      }

      return *this;
    }

    self operator++(int)
    {
      if (++ptr_ == end_)
      {
        ptr_ = begin_;
      }

      return *this;
    }
    
  private:
    pointer begin_;
    pointer end_;
  };

  using iterator_t = Iterator;
  using const_iterator_t = const Iterator;

  RingBuffer(uint8_t* buffer, size_t buff_size)
    : buffer_{buffer}
    , buff_size_{buff_size}
    , capacity_{0}
    , head_{0}
    , tail_{0}
  {}

  RingBuffer() = delete;
  RingBuffer(const RingBuffer&) = delete;
  RingBuffer& operator=(const RingBuffer&) = delete;
  RingBuffer(RingBuffer&&) = default;
  RingBuffer& operator=(RingBuffer&&) = default;
  ~RingBuffer() = default;

  void clear()
  {
    std::fill(begin(), end(), '\0');
  }

  void write(uint8_t data)
  {
    buffer_[head_++ % buff_size_] = data;

    if (capacity_ != buff_size_)
    {
      ++capacity_;
    }
  }

  void write(const uint8_t* data, size_t sz)
  {
    for (size_t i = 0; i < sz; ++i) 
    {
      write(data[i]);
    }
  }

  void write(const char* data, const size_t sz) //TODO: Consiedr removing as buffer should work only with uint8_t data type.
  {
    for (size_t i = 0; i < sz; ++i) 
    {
      write(data[i]);
    }
  }

  uint8_t read()
  {
    uint8_t data = buffer_[tail_++ % buff_size_];

    if (capacity_ != 0)
    {
      --capacity_;
    }

    return data;
  }
  
  iterator_t begin() { return iterator_t{buffer_}; }
  iterator_t end() { return iterator_t{buffer_ + buff_size_};}
  const_iterator_t begin() const { return const_iterator_t{buffer_}; }
  const_iterator_t end() const { return const_iterator_t{buffer_ + buff_size_}; }
  size_t capacity() const { return capacity_; }

  CircularIterator find(const uint8_t* needle, size_t sz) const
  {
    const auto begin_ptr = buffer_;
    const auto end_ptr = buffer_ + buff_size_; 
    uint8_t* head_ptr = &buffer_[head_ % buff_size_];
    uint8_t* data_ptr = &buffer_[tail_ % buff_size_];


    auto iter = CircularIterator{end_ptr, buffer_, end_ptr};
    size_t needle_idx = 0;

    if (sz == 0)
    {
      return iter;
    }

    do 
    {
      if (*data_ptr == needle[needle_idx])
      {
        if (needle_idx == 0)
        {
          iter = CircularIterator{data_ptr, buffer_, end_ptr}; 
        }

        needle_idx++;
      }
      else
      {
        needle_idx = 0;
        iter = CircularIterator{end_ptr, buffer_, end_ptr};
      }

      if (needle_idx == sz)
      {
        return iter;
      }

      if (++data_ptr == end_ptr)
      {
        data_ptr = begin_ptr;
      }

    } while(data_ptr != head_ptr);

    return iter;
  }

private:
  uint8_t* buffer_;
  size_t buff_size_;
  size_t capacity_;
  size_t head_;
  size_t tail_;
};
}