add_library(bloglib STATIC
        shared/classes/Post.cpp
        shared/classes/Post.h
        shared/classes/Comment.cpp
        shared/classes/Comment.h
        shared/classes/Date.cpp
        shared/classes/Date.h
        shared/classes/Stats.cpp
        shared/classes/Stats.h
)

add_executable(adminapp adminapp.cpp
)
target_link_libraries(adminapp bloglib)

add_executable(userapp userapp.cpp)
target_link_libraries(userapp bloglib)
