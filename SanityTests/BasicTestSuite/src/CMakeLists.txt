if (NOT TEST)
add_executable(class_with_main class_with_main.cpp)
endif()

if(TEST)
add_definitions(-D__TEST__)
add_library(class_without_main class_with_main.cpp)
target_include_directories(class_without_main
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
endif()