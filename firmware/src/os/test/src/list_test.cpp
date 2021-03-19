#include <gtest/gtest.h>
#include <list.hpp>

using namespace os::utils;

struct ListTest : public ::testing::Test
{

};

TEST_F(ListTest, WhenListIsInitializedItShouldBeEmpty)
{
  //Arrange
  List sut;
  list_init(&sut);
  
  //Act

  //Assert
}