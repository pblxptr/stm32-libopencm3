#include <gtest/gtest.h>
#include <utils/list.hpp>
#include <iostream>

using namespace utils::containers;

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
  List l{};

  auto b = l.begin();
  auto e = l.end();

  ASSERT_EQ(b, e);

  auto e1 = Dummy{};
  auto e2 = Dummy{};
  auto e3 = Dummy{};
  auto e4 = Dummy{};

  l.append(make_link_ptr(e1));

  b = l.begin();
  e = l.end();
  
  ASSERT_NE(b, e);


  --e;
  ASSERT_EQ(b, e);



  l.append(make_link_ptr(e2));
  l.append(make_link_ptr(e3));
  l.append(make_link_ptr(e4));

  b = l.begin();
  e = l.end();

  ASSERT_NE(b, e);
}

TEST_F(ListTests, WhenTheListIsEmptyThenBeginAndEndShouldPointToItself)
{
  // Arrange
  auto list = List{};
  
  //Act
  auto b = list.begin();
  auto e = list.end();

  //Assert
  ASSERT_EQ(e, b);
  ASSERT_TRUE(list.empty());
}

TEST_F(ListTests, WhenAppendElementToTheListThenBeginAndEndShouldPointToIt)
{
  //Arrange
  auto list = List{};
  auto elem = Dummy{};

  //Act
  list.append(make_link_ptr(elem));
  auto b = list.begin();

  //Assert
  ASSERT_EQ(list.size(), 1);
  ASSERT_EQ(&*b, make_link_ptr(elem));
  ASSERT_EQ(*b, node_link_r(elem));
}

TEST_F(ListTests, WhenInsertingItemThenItShouldReplaceThePositionOfIterator)
{
  //Arrange
  auto e1 = Dummy{ 10, {} };
  auto e2 = Dummy{ 20, {} };

  //Act
  auto l = List{};
  l.append(make_link_ptr(e1));

  auto b = l.begin();

  l.insert(b, make_link_ptr(e2));

  b = l.begin();
  
  const auto e1_it = b;
  const auto e2_it = ++b;
  const Dummy* e1_cof = container_of(&*e1_it, Dummy, node);
  const Dummy* e2_cof = container_of(&*e2_it, Dummy, node);

  //Assert
  ASSERT_NE(e1_it, e2_it);
  ASSERT_EQ(e1_cof->x, e2.x);
  ASSERT_EQ(e2_cof->x, e1.x);
}

TEST_F(ListTests, WhenInsertingElementAtLastValidPositionItTheLastElementShouldBeChanged)
{
  //Arrange
  auto e1 = Dummy{ 10, {} };
  auto e2 = Dummy{ 20, {} };
  auto e3 = Dummy{ 30, {} };
  auto l = List{};

  //Act
  l.append(make_link_ptr(e1));
  l.append(make_link_ptr(e2));

  auto it = ++l.begin();
  const auto newIt = l.insert(it, make_link_ptr(e3));
  const Dummy* newItElem = container_of(&*newIt, Dummy, node);

  //Assert
  ASSERT_EQ(newItElem->x, e3.x);
  ASSERT_EQ(++it, l.end());
}

TEST_F(ListTests, WhenErasingElementFromListThenItShouldDisappearFromListAndTheNextIteratorShouldBeReturned)
{
  //Arrange
  auto e1 = Dummy{ 10, {} };
  auto e2 = Dummy{ 20, {} };
  auto e3 = Dummy{ 30, {} };

  //Act
  auto l = List{};
  l.append(make_link_ptr(e1));
  l.append(make_link_ptr(e2));
  l.append(make_link_ptr(e3));

  const auto it = l.begin();
  const auto nextIt = l.erase(it);

  //Assert
  ASSERT_EQ(l.size(), 2);
  ASSERT_EQ(l.begin(), nextIt);
}

TEST_F(ListTests, WhenErasingLastElementThenItShouldBeRemovedFromListAndEndIteratorShouldBeUpdated)
{
  //Arrange
  auto e1 = Dummy{ 10, {} };
  auto e2 = Dummy{ 20, {} };
  auto e3 = Dummy{ 30, {} };

  //Act
  auto l = List{};
  l.append(make_link_ptr(e1));
  l.append(make_link_ptr(e2));
  l.append(make_link_ptr(e3));

  auto it = --(l.end());

  l.erase(it);

  //Assert
  ASSERT_EQ(l.size(), 2);
}

TEST_F(ListTests, WhenInsertingElementToTheEndThenTheItratorsShouldPointCorrectly) //TODO: Dokonczyc implementacje
{
  //Arrange
  auto e1 = Dummy{ 10, {} };
  auto e2 = Dummy{ 20, {} };
  auto e3 = Dummy{ 30, {} };
  auto l = List{};

  auto it = l.end();
  l.insert(it, make_link_ptr(e1));

  it = l.end();
  l.insert(it, make_link_ptr(e2));

  it = l.end();
  l.insert(it, make_link_ptr(e3));
}


