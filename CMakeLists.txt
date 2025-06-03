add_library(bloglib STATIC
        src/Post.cpp
        src/Post.h
        src/Comment.cpp
        src/Comment.h
        src/Date.cpp
        src/Date.h
        src/Stats.cpp
        src/Stats.h
)

add_executable(adminapp src/adminapp.cpp)
target_link_libraries(adminapp bloglib)

add_executable(userapp src/userapp.cpp)
target_link_libraries(userapp bloglib)
