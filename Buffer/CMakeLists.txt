cmake_minimum_required(VERSION 3.0)
project(Buffer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost
             1.57.0
             COMPONENTS
             REQUIRED)
             
file(GLOB THREAD_SRC src/Thread/*.cpp)
set(THREAD_LIB_NAME mythread)
add_library(${THREAD_LIB_NAME} SHARED ${THREAD_SRC})

file(GLOB BUFFER_SRC src/*.cpp)
set(BUFFER_LIB_NAME buffer)
add_library(${BUFFER_LIB_NAME} SHARED ${BUFFER_SRC})

set(BUFFER_MAIN_SRC main.cpp) 
add_executable(appBuffer ${BUFFER_MAIN_SRC}) 
target_link_libraries(appBuffer ${BUFFER_LIB_NAME} ${THREAD_LIB_NAME})

