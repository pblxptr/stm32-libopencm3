#include <gtest/gtest.h>
#include <utils/list.hpp>

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
  auto e1 = Dummy { 10, {} };
  auto e2 = Dummy { 20, {} };
  auto sut = List{};

  //Act
  sut.append(make_link_ptr(e1));
  auto it = sut.begin();
  sut.insert(it, make_link_ptr(e2));

  //Assert
  const auto it1 = sut.begin();
  const auto it2 = ++sut.begin();

  const Dummy* it1_elem = container_of(&*it1, Dummy, node);
  const Dummy* it2_elem = container_of(&*it2, Dummy, node);

  std::vector<uint32_t> elements{};
  for(const auto& node : sut)
  {
    const Dummy* elem = container_of(&node, Dummy, node);

    elements.push_back(elem->x);
  }

  ASSERT_EQ(elements[0], e2.x);
  ASSERT_EQ(elements[1], e1.x);
  ASSERT_EQ(it1_elem->x, e2.x);
  ASSERT_EQ(it2_elem->x, e1.x);
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
  auto sut = List{};
  sut.append(make_link_ptr(e1));
  sut.append(make_link_ptr(e2));
  sut.append(make_link_ptr(e3));

  const auto it = sut.begin();
  const auto nextIt = sut.erase(it);

  //Assert
  ASSERT_EQ(sut.size(), 2);
  ASSERT_EQ(sut.begin(), nextIt);
}

TEST_F(ListTests, WhenErasingLastElementThenItShouldBeRemovedFromListAndEndIteratorShouldBeUpdated)
{
  //Arrange
  auto e1 = Dummy{ 10, {} };
  auto e2 = Dummy{ 20, {} };
  auto e3 = Dummy{ 30, {} };

  //Act
  auto sut = List{};
  sut.append(make_link_ptr(e1));
  sut.append(make_link_ptr(e2));
  sut.append(make_link_ptr(e3));

  auto it = --(sut.end());

  sut.erase(it);

  //Assert
  ASSERT_EQ(sut.size(), 2);
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

TEST_F(ListTests, WhenInsertingElemebtsInBetweenAndErasingThisElementListShouldBeUpdated)
{
    //Arrange
  auto e1 = Dummy{ 10, {} };
  auto e2 = Dummy{ 20, {} };
  auto sut = List{};

  //Act
  sut.append(make_link_ptr(e1));
  auto it = sut.begin();
  sut.insert(it, make_link_ptr(e2));
  it = sut.begin();
  sut.erase(it);

  //Act
  std::vector<int> elements{};

  for (const auto& x : sut)
  {
    const Dummy* dummy = container_of(&x, Dummy, node);

    elements.push_back(dummy->x);
  }

  //Assert
  ASSERT_EQ(elements.size(), 1);
}

