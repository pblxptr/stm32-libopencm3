#include <ring_buffer.hpp>

#include <algorithm>

namespace utils::containers 
{
  RingBuffer::RingBuffer()
    : buff_{nullptr},
      buffSize_{0},
      head_{0},
      tail_{0},
      capacity_{0} 
    {}
  RingBuffer::RingBuffer(uint8_t* buff, size_t buffSize)
    : buff_{buff},
      buffSize_{buffSize},
      head_{0},
      tail_{0},
      capacity_{0}
    {}

  size_t RingBuffer::capacity() const
  {
    return capacity_;
  }

  uint8_t* RingBuffer::begin() const
  {
    return buff_;
  }

  uint8_t* RingBuffer::end() const
  {
    return buff_ + buffSize_ + 1;
  }

  uint8_t* RingBuffer::head() const
  {
    return &buff_[head_];
  }

  uint8_t* RingBuffer::tail() const
  {
    return &buff_[tail_];
  }

  void RingBuffer::write(const uint8_t data)
  {
    buff_[head_++ % buffSize_] = data;

    if (capacity_ != buffSize_)
    {
      ++capacity_;
    }
  }

  void RingBuffer::write(const uint8_t* data, const size_t len)
  {
    for (size_t i = 0; i < len; i++)
      write(*data++);
  }

  void RingBuffer::write(const char* data, const size_t len)
  {
    for (size_t i = 0; i < len; i++)
      write(*data++);
  }

  uint8_t RingBuffer::read()
  {
    auto ret = uint8_t{0xFF}; // temporary invalid value

    if (capacity_ == 0)
      return ret;
    
    ret = buff_[tail_++ % buffSize_];

    --capacity_;

    return ret;
  }

  void RingBuffer::clear()
  {
    std::fill_n(buff_, buffSize_, 0);
    tail_ = 0;
    head_ = 0;
    capacity_ = 0;
  }
}