#pragma once

#include <stdint.h>
#include <cstddef>

namespace utils::containers
{
  class RingBuffer //TODO: Add static polimorphizm. Divide that class into two implementation: volatile and non volatile
  {
  public:
    RingBuffer();
    RingBuffer(uint8_t* buff, size_t buffSize);
    size_t capacity() const;

  using iterator = uint8_t*;
  using const_iterator = uint8_t*;
  using vaule_type = uint8_t;

  const_iterator begin() const;
  const_iterator end() const;
  const_iterator head() const;
  const_iterator tail() const;
  void write(const vaule_type data);
  void write(const vaule_type* data, const size_t len);
  void write(const char* data, const size_t len);
  vaule_type read();
  void clear();
  
  private:
    vaule_type* buff_;
    size_t buffSize_;
    size_t head_; 
    size_t tail_;
    size_t capacity_;
  };
}