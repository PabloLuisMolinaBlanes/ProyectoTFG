include_directories(include ${CMAKE_SOURCE_DIR}/src/utils/serial/include)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)
add_executable(first_examination first_examination.cpp)
add_executable(second_examination second_examination.cpp)
target_link_libraries(first_examination PRIVATE SFML::Graphics)
target_link_libraries(second_examination PRIVATE SFML::Graphics)
target_link_libraries(first_examination PRIVATE serial)
target_link_libraries(second_examination PRIVATE serial)