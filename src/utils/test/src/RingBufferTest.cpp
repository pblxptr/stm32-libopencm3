#include <gtest/gtest.h>
#include <ring_buffer.hpp>

using namespace utils::containers;

class RingBufferTest : public ::testing::Test 
{

};


TEST_F(RingBufferTest, test)
{

static uint8_t w_buffer[1024]; // write buffer

static utils::containers::RingBuffer write_rb{w_buffer, sizeof(w_buffer)};

write_rb.write('a');
}