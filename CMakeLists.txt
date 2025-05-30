cmake_minimum_required(VERSION 3.31)
project(cppBlog)

set(CMAKE_CXX_STANDARD 20)

add_library(bloglib STATIC
        src/Post.cpp
        src/Post.h
        src/Stats.cpp
        src/Stats.h
)

target_include_directories(bloglib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/class)

add_library(blogutils STATIC
        src/util/blogutils.cpp
)

add_executable(adminapp src/adminapp.cpp)
target_link_libraries(adminapp PRIVATE bloglib blogutils)

add_executable(userapp src/userapp.cpp)
target_link_libraries(userapp PRIVATE bloglib blogutils)
