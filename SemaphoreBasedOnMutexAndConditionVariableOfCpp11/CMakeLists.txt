cmake_minimum_required(VERSION 3.0)
project(Semaphore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost
             1.57.0
             COMPONENTS 
             		thread
             REQUIRED)
            
file(GLOB SEMAPHORE_SOURCE src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SEMAPHORE_SOURCE})

set(SEMAPHORE_MAIN_SOURCE main.cpp) 
add_executable(appSemaphore ${SEMAPHORE_MAIN_SOURCE}) 
target_link_libraries(appSemaphore ${PROJECT_NAME} pthread)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

