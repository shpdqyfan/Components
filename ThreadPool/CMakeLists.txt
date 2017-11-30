cmake_minimum_required(VERSION 3.0)
project(THREADPOOL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost
             1.57.0
             COMPONENTS
             REQUIRED)
            
file(GLOB THREAD_POOL_SOURCE src/*.cpp)
set(THREAD_POOL_LIB_NAME threadpool)
add_library(${THREAD_POOL_LIB_NAME} SHARED ${THREAD_POOL_SOURCE})

set(THREADPOOL_MAIN_SOURCE main.cpp) 
add_executable(appThreadPool ${THREADPOOL_MAIN_SOURCE}) 
target_link_libraries(appThreadPool ${THREAD_POOL_LIB_NAME} pthread)
target_include_directories(${THREAD_POOL_LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

