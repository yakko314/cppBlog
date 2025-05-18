cmake_minimum_required(VERSION 3.31)
project(cppBlog)

set(CMAKE_CXX_STANDARD 20)

add_library(bloglib STATIC
        class/Post.cpp
        class/Post.h
        class/Stats.cpp
        class/Stats.h
)

target_include_directories(bloglib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/class)

add_library(blogutils STATIC
        libs/blogutils.cpp
)

add_executable(adminapp adminapp.cpp)
target_link_libraries(adminapp PRIVATE bloglib blogutils)

add_executable(userapp userapp.cpp)
target_link_libraries(userapp PRIVATE bloglib blogutils)
