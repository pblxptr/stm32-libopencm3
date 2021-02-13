// #include <gtest/gtest.h>
// #include <List.hpp>
// #include <iostream>

// using namespace utils::containers;

// struct Dummy
// {
//   uint32_t x;
//   ListNode_t node;
// };

// class ListTests : public ::testing::Test 
// {

// };

// TEST_F(ListTests, ConfiureAndRunEmptyTest)
// {
//   List_t l{};

//   auto b = l.begin();
//   auto e = l.end();

//   ASSERT_EQ(b, e);

//   auto e1 = Dummy{};
//   auto e2 = Dummy{};
//   auto e3 = Dummy{};
//   auto e4 = Dummy{};

//   l.append(make_link_ptr(e1));

//   b = l.begin();
//   e = l.end();
  
//   ASSERT_NE(b, e);


//   --e;
//   ASSERT_EQ(b, e);



//   l.append(make_link_ptr(e2));
//   l.append(make_link_ptr(e3));
//   l.append(make_link_ptr(e4));

//   b = l.begin();
//   e = l.end();

//   ASSERT_NE(b, e);

//   size_t i = 0;
//   for (auto const& it : l)
//   {
//     std::cout << i << std::endl;

//     if (i++ == 20)
//       break;
//   }
// }

// TEST_F(ListTests, WhenTheListIsEmptyThenBeginAndEndShouldPointToItself)
// {
//   // Arrange & Act
//   auto list = List_t{};
//   auto b = list.begin();
//   auto e = list.end();

//   //Assert
//   ASSERT_EQ(e, b);
//   ASSERT_TRUE(list.empty());
// }

// TEST_F(ListTests, WhenAppendElementToTheListThenBeginAndEndShouldPointToIt)
// {
//   //Arrange
//   auto list = List_t{};
//   auto elem = Dummy{};

//   // //Act
//   list.append(make_link_ptr(elem));
//   auto b = list.begin();
//   auto e = list.end();

//   //Assert
//   ASSERT_EQ(list.size(), 1);
//   ASSERT_EQ(&*b, make_link_ptr(elem));
//   ASSERT_EQ(*b, node_link_r(elem));
// }

// TEST_F(ListTests, WhenInsertingItemThenItShouldReplaceThePositionOfIterator)
// {
//   auto e1 = Dummy{};
//   e1.x = 10;

//   auto e2 = Dummy{};
//   e2.x = 20;

//   auto l = List_t{};
//   l.append(make_link_ptr(e1));

//   auto b = l.begin();

//   l.insert(b, make_link_ptr(e2));

//   b = l.begin();
  
//   auto e1_it = b;
//   auto e2_it = ++b;

//   ASSERT_NE(e1_it, e2_it);

//   Dummy* e1_cof = container_of(&*e1_it, Dummy, node);
//   Dummy* e2_cof = container_of(&*e2_it, Dummy, node);

//   ASSERT_EQ(e1_cof->x, e2.x);
//   ASSERT_EQ(e2_cof->x, e1.x);
// }

// TEST_F(ListTests, WhenInsertingElementAtLastValidPositionItTheLastElementShouldBeChanged)
// {
//   auto e1 = Dummy{};
//   e1.x = 10;

//   auto e2 = Dummy{};
//   e2.x = 20;

//   auto e3 = Dummy{};
//   e3.x = 30;

//   auto l = List_t{};
//   l.append(make_link_ptr(e1));
//   l.append(make_link_ptr(e2));

//   auto it = l.begin();
//   ++it;

//   auto newIt = l.insert(it, make_link_ptr(e3));

//   Dummy* newItElem = container_of(&*newIt, Dummy, node);

//   ASSERT_EQ(newItElem->x, e3.x);
//   ASSERT_EQ(++it, l.end());
// }

// TEST_F(ListTests, WhenErasingElementFromListThenItShouldDisappearFromListAndTheNextIteratorShouldBeReturned)
// {
//   auto e1 = Dummy{};
//   e1.x = 10;

//   auto e2 = Dummy{};
//   e2.x = 20;

//   auto e3 = Dummy{};
//   e3.x = 30;

//   auto l = List_t{};
//   l.append(make_link_ptr(e1));
//   l.append(make_link_ptr(e2));
//   l.append(make_link_ptr(e3));

//   auto it = l.begin();
//   auto nextIt = l.erase(it);

//   ASSERT_EQ(l.size(), 2);
//   ASSERT_EQ(l.begin(), nextIt);

//   for (const auto& x : l)
//   {
//     Dummy* p = container_of(&x, Dummy, node);
//   }
// }

// TEST_F(ListTests, WhenErasingLastElementThenItShouldBeRemovedFromListAndEndIteratorShouldBeUpdated)
// {
//   auto e1 = Dummy{};
//   e1.x = 10;

//   auto e2 = Dummy{};
//   e2.x = 20;

//   auto e3 = Dummy{};
//   e3.x = 30;

//   auto l = List_t{};
//   l.append(make_link_ptr(e1));
//   l.append(make_link_ptr(e2));
//   l.append(make_link_ptr(e3));

//   auto it = --(l.end());

//   l.erase(it);

//   ASSERT_EQ(l.size(), 2);

//   for (const auto& x : l)
//   {
//     Dummy* p = container_of(&x, Dummy, node);
//   }
// }

// TEST_F(ListTests, WhenInsertingElementToTheEndThenTheItratorsShouldPointCorrectly)
// {
//   auto e1 = Dummy{};
//   e1.x = 10;

//   auto e2 = Dummy{};
//   e2.x = 20;

//   auto e3 = Dummy{};
//   e3.x = 30;

//   auto l = List_t{};

//   auto it = l.end();
//   l.insert(it, make_link_ptr(e1));

//   it = l.end();
//   l.insert(it, make_link_ptr(e2));

//   it = l.end();
//   l.insert(it, make_link_ptr(e3));

//   for (const auto& x : l)
//   {
//     Dummy* p = container_of(&x, Dummy, node);
//   }
// }

// //Todo: DOpisac test
// TEST_F(ListTests, Wheee)
// {
//   std::cout << "Dupa\n";
//   auto e1 = Dummy{};
//   e1.x = 10;

//   auto e2 = Dummy{};
//   e2.x = 20;

//   auto l = List_t{};
//   l.append(make_link_ptr(e1));

//   for (auto& xd : l)
//   {
//     Dummy* t = container_of(&xd, Dummy, node);
//     std::cout << t->x << std::endl;
//   }

//   const auto& it= l.begin();

//   l.insert(it, make_link_ptr(e2));

//   for (auto& xd : l)
//   {
//     Dummy* t = container_of(&xd, Dummy, node);
//     std::cout << t->x << std::endl;
//   }

//   l.erase(it);

//    Dummy* t = container_of(it_to_ptr(l.begin()), Dummy, node);
//    Dummy* t2 = container_of(it_to_ptr(l.end()), Dummy, node);


//   size_t i = 0;

//   for (auto& xd : l)
//   {
//     i++;
//     Dummy* t = container_of(&xd, Dummy, node);
//     std::cout << t->x << std::endl;
//   }

// }


