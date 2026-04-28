cmake_minimum_required(VERSION 3.27)
set(TEST TRUE)
project(FOSSPsychotechnicalExaminationSystemSoftware LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)

if(TEST)
 add_subdirectory(test)
endif()