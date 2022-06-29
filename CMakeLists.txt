cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-02 -Wall -Wextra -Werror -pedantic")

project(LambdaPL)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(LambdaPL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
