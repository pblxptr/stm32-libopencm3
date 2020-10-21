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

  uint8_t& head();
  uint8_t& tail();
  void write(const uint8_t data);
  void write(const uint8_t* data, const size_t len);
  uint8_t read();
  
  private:
    uint8_t* buff_;
    size_t buffSize_;
    size_t head_; 
    size_t tail_;
    size_t capacity_;
  };
}