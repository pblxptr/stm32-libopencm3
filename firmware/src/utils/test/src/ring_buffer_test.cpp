#include <utils/ring_buffer.hpp>

#include <gtest/gtest.h>
#include <string_view>
#include <algorithm>
#include <iostream>


using namespace utils::containers;

class RingBufferTest : public ::testing::Test 
{

};


TEST_F(RingBufferTest, WhenInsertinSingleByteThenRingBufferShouldHaveAppropriateCapacityAndDataShouldBeSaved)
{
  //Arrange
  uint8_t data_buffer[10];
  auto sut = RingBuffer{data_buffer, sizeof(data_buffer)};
  const uint8_t data = 'A';

  //Act
  sut.write(data);

  const auto capactity_after_write = sut.capacity();
  const auto data_from_read = sut.read();
  const auto capacity_after_read = sut.capacity();

  //Assert
  ASSERT_EQ(capactity_after_write, 1);
  ASSERT_EQ(capacity_after_read, 0);
  ASSERT_EQ(data, data_from_read);
}

TEST_F(RingBufferTest, WhenWritingInOverflowThenOldDataShouldBeOverrwritten)
{
  //Arrange
  uint8_t data_buffer[10];
  auto sut = RingBuffer{data_buffer, sizeof(data_buffer)};
  const uint8_t data_that_will_be_overrwritten = 'A';
  const uint8_t data_will_overwrite = 'B';

  //Act
  sut.write(data_that_will_be_overrwritten);

  for (size_t i = 0; i < sizeof(data_buffer); i++)
  {
    sut.write(data_will_overwrite);
  }

  const auto value_of_overwritten_index = data_buffer[0];
  const auto capacity = sut.capacity();

  //Assert
  
  ASSERT_EQ(capacity, sizeof(data_buffer));
  ASSERT_EQ(value_of_overwritten_index, data_will_overwrite);
}

TEST_F(RingBufferTest, WhenReadingInOverflowModeThenDataShouldBeReadedProperly)
{
  //Arrange
  uint8_t data_buffer[10];
  const size_t data_buffer_size = sizeof(data_buffer);

  auto sut = RingBuffer{data_buffer, data_buffer_size};
  auto token_to_store = std::string{};
  token_to_store.resize(data_buffer_size);

  std::generate(token_to_store.begin(), token_to_store.end(), [v = 'a']() mutable { return v++; });
  
  //Act

  // -> Advance internal iterators 
  for (size_t i = 0; i < data_buffer_size / 2; i++)
  {
    sut.write('A');
    sut.read();
  }
  
  // ->  Write whole token
  auto token_iter = token_to_store.begin();
  for (size_t i = 0; i < data_buffer_size; i++)
  {
    sut.write(*token_iter++);
  }
  
  // -> Read whole token
  auto stored_token = std::string{};
  for (size_t i = 0; i < data_buffer_size; i++)
  {
    stored_token += sut.read();
  }

  // Assert
  ASSERT_EQ(sut.capacity(), 0);
  ASSERT_EQ(token_to_store, stored_token);
}

TEST_F(RingBufferTest, WhenWritingMultipleDataAtTimeThenItShouldBeStored)
{
  //Arrange
  uint8_t data_buffer[10];
  const size_t data_buffer_size = sizeof(data_buffer);
  auto sut = RingBuffer{data_buffer, data_buffer_size};

  auto token_to_store = std::string{};
  token_to_store.resize(data_buffer_size);

  std::generate(token_to_store.begin(), token_to_store.end(), [v = 'a']() mutable { return v++; });

  //Act
  sut.write(reinterpret_cast<uint8_t*>(token_to_store.data()), token_to_store.size());

  //Assert
  auto stored_token = std::string{};
  for (size_t i = 0; i < data_buffer_size; i++)
  {
    stored_token += sut.read();
  }

  //Assert
  ASSERT_EQ(token_to_store, stored_token);
}