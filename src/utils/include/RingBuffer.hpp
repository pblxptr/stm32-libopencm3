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

  void write(uint8_t data);
  uint8_t read();
  
  private:
    uint8_t* buff_;
    size_t buffSize_;
    volatile size_t head_; 
    volatile size_t tail_;
    volatile size_t capacity_;
  };
}