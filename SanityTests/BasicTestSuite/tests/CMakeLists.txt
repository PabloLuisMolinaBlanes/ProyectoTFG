include(FetchContent)
include_directories(${CMAKE_SOURCE_DIR}/src/include)
FetchContent_Declare(
    googletest
    GIT_TAG v1.17.0
    GIT_REPOSITORY https://github.com/google/googletest.git
    FIND_PACKAGE_ARGS 1.17.0 NAMES GTest COMPONENTS gmain_main
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(googletest)
add_executable(test test.cpp)
target_link_libraries(test PUBLIC GTest::gtest_main)
target_link_libraries(test PUBLIC class_without_main)
add_test(NAME test COMMAND test)