#include <gtest/gtest.h>
#include <List.hpp>

struct Dummy
{
  uint32_t x;
  ListNode_t node;
};

class ListTests : public ::testing::Test 
{

};

TEST_F(ListTests, ConfiureAndRunEmptyTest)
{

}

TEST_F(ListTests, WhenTheListIsEmptyThenBeginAndEndShouldPointToItself)
{
  //Arrange & Act
  auto list = List_t{};
  auto b = list.begin();
  auto e = list.end();

  //Assert
  ASSERT_EQ(e, b);
  ASSERT_TRUE(list.empty());
}

TEST_F(ListTests, WhenAppendElementToTheListThenBeginAndEndShouldPointToIt)
{
  //Arrange
  auto list = List_t{};
  auto elem = Dummy{};

  //Act
  list.append(node_link(elem));
  auto b = list.begin();
  auto e = list.end();

  //Assert
  ASSERT_EQ(list.size(), 1);
  ASSERT_EQ(b, node_link(elem));
  ASSERT_EQ(e, node_link(elem));
}

TEST_F(ListTests, WhenErasingOneElementFromListThatHasOnlySingleElementThenTheListShouldBeEmpty)
{
  //Arrange
  auto list = List_t{};
  auto elem = Dummy{};

  //Act
  list.append(node_link(elem));
  auto it = list.begin();
  list.erase(it);
  auto b = list.begin();
  auto e = list.end();

  //Assert
  ASSERT_TRUE(list.empty());
  ASSERT_EQ(b, e);
}

TEST_F(ListTests, WhenAddintElementsToListThenWhenAccessingTheseElementsTheyShouldSetAppropriateValues)
{
  //Arrange
  auto list = List_t{};
  const size_t numberOfElements = 10;
  auto elements = std::vector<Dummy>(numberOfElements);
  for(size_t i = 0; i < numberOfElements; ++i)
  {
    elements[i].x = i;
  }

  //Act
  for (const auto& e : elements)
  {
    list.append(node_link(e));
  }

  //Assert
  ASSERT_EQ(list.size(), numberOfElements);

  auto it = list.begin();
  Dummy* elem = container_of(it, Dummy, node);
  ASSERT_EQ(elem->x, 0);

  it = &(++(*it));
  elem = container_of(it, Dummy, node);
  ASSERT_EQ(elem->x, 1);


  // for (size_t i = 0; i < numberOfElements; ++i)
  // {
  //   Dummy* elem = container_of(it, Dummy, node);
  //   ASSERT_EQ(elem->x, elements[i].x);

  //   ++it;
  // }
}