add_library(serial serial.cpp)

include_directories(include)

target_include_directories(serial
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)