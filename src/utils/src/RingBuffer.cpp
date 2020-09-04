#include <RingBuffer.hpp>

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

  void RingBuffer::write(uint8_t data)
  {
    buff_[head_] = data;
    
    if (++head_ >= buffSize_)
    {
      head_= 0;
    }

    if (capacity_ < buffSize_) {
        capacity_++;
    }
  }

  uint8_t RingBuffer::read()
  {
    if (capacity_ == 0)
    {
        return 0;
    }

    capacity_--;

    auto ret = buff_[tail_];
    
    if (tail_++ == buffSize_)
    {
      tail_ = 0;
    }

    return ret;
  }
}