include_directories(include)
add_library(serial serial.cpp)
target_include_directories(serial
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)