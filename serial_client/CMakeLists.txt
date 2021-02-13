cmake_minimum_required(VERSION 3.16)
project(serial_client VERSION 0.1.0)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.71 COMPONENTS thread) 

if(Boost_FOUND)
  add_executable(serial_client main.cpp)
  set_property(TARGET  serial_client PROPERTY CXX_STANDARD 17)

  include_directories(${Boost_INCLUDE_DIRS}) 
  target_link_libraries(serial_client ${Boost_LIBRARIES})
endif()



