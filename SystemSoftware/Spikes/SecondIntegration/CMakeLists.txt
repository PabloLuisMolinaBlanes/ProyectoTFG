cmake_minimum_required(VERSION 3.27)
project(CMakeSFMLProject LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(FIRST_TEST ${CMAKE_SOURCE_DIR}/src/examinations/first_test.cpp)
set(SECOND_TEST ${CMAKE_SOURCE_DIR}/src/examinations/second_test.cpp)
set(SERIAL_UTIL ${CMAKE_SOURCE_DIR}/src/utils/serial.cpp)
set(GUI ${CMAKE_SOURCE_DIR}/src/gui/gui.c)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})
include_directories(include)
add_executable(first_test ${FIRST_TEST})
target_compile_features(first_test PRIVATE cxx_std_17)
target_link_libraries(first_test PRIVATE SFML::Graphics)
target_link_libraries(first_test PRIVATE ${SERIAL_UTIL})
add_executable(second_test ${SECOND_TEST})
target_compile_features(second_test PRIVATE cxx_std_17)
target_link_libraries(second_test PRIVATE SFML::Graphics)
target_link_libraries(second_test PRIVATE ${SERIAL_UTIL})
add_executable(gui ${GUI})
add_definitions(${GTK4_CFLAGS_OTHER})
target_link_libraries(gui ${GTK4_LIBRARIES})

if(MSVC)
  target_compile_options(${TARGET_NAME} first_test PRIVATE /W4 /WX)
  target_compile_options(${TARGET_NAME} second_test PRIVATE /W4 /WX)
  target_compile_options(${TARGET_NAME} gui PRIVATE /W4 /WX)
else()
  target_compile_options(${TARGET_NAME} first_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
  target_compile_options(${TARGET_NAME} second_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
  target_compile_options(${TARGET_NAME} gui PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
