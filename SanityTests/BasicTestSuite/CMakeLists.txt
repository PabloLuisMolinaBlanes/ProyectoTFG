cmake_minimum_required(VERSION 3.27)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(TEST TRUE)
project(BasicTestSuite LANGUAGES C CXX)


add_subdirectory(src)

if(TEST)
 add_subdirectory(tests)
endif()