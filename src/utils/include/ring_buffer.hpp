#pragma once

#include <stdint.h>
#include <cstddef>

namespace utils::containers 
{
  class RingBuffer
  {
    public:
      RingBuffer()
        : buff_{nullptr},
          buffSize_{0},
          head_{0},
          tail_{0},
          capacity_{0}
      {}
      RingBuffer(uint8_t* buff, size_t buffSize)
        : buff_{buff},
          buffSize_{buffSize},
          head_{0},
          tail_{0},
          capacity_{0}
      {}

    size_t capacity() const
    {
        return capacity_;
    }

    void write(uint8_t data)
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
  
    uint8_t read()
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
    
    private:
      uint8_t* buff_;
      size_t buffSize_;
      size_t head_;
      size_t tail_;
      size_t capacity_;
  };
}