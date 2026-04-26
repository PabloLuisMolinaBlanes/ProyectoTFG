include(FetchContent)
include_directories(${CMAKE_SOURCE_DIR}/src/utils/serial/include)
include_directories(${CMAKE_SOURCE_DIR}/src/examinations/include)
FetchContent_Declare(
    googletest
    GIT_TAG v1.17.0
    GIT_REPOSITORY https://github.com/google/googletest.git
    FIND_PACKAGE_ARGS 1.17.0 NAMES GTest COMPONENTS gmain_main
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(googletest)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)
add_executable(first_examination_test first_examination_test.cpp)
add_executable(second_examination_test second_examination_test.cpp)
add_executable(serial_test serial_test.cpp)
target_link_libraries(first_examination_test PUBLIC GTest::gtest_main)
target_link_libraries(second_examination_test PUBLIC GTest::gtest_main)
target_link_libraries(first_examination_test  PRIVATE SFML::Graphics)
target_link_libraries(second_examination_test  PRIVATE SFML::Graphics)
target_link_libraries(serial_test PUBLIC GTest::gtest_main)
target_link_libraries(serial_test PUBLIC serial)
target_link_libraries(first_examination_test PUBLIC first_examination_library)
add_test(NAME first_examination_test COMMAND first_examination_test)
add_test(NAME second_examination_test COMMAND second_examination_test)