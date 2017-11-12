cmake_minimum_required(VERSION 3.0)
project(THREAD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost
             1.57.0
             COMPONENTS 
             		thread
             REQUIRED)
            
file(GLOB THREAD_SOURCE src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${THREAD_SOURCE})

set(THREAD_MAIN_SOURCE main.cpp) 
add_executable(appThread ${THREAD_MAIN_SOURCE}) 
target_link_libraries(appThread ${PROJECT_NAME} pthread)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
