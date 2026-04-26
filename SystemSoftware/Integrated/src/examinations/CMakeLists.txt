include_directories(include ${CMAKE_SOURCE_DIR}/src/utils/serial/include)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)
if (NOT TEST)
add_executable(first_examination first_examination.cpp)
add_executable(second_examination second_examination.cpp)
target_link_libraries(first_examination PRIVATE SFML::Graphics)
target_link_libraries(second_examination PRIVATE SFML::Graphics)
target_link_libraries(first_examination PUBLIC serial)
target_link_libraries(second_examination PUBLIC serial)
endif()
if(TEST)
    add_definitions(-D__TEST__)
    add_library(first_examination_library first_examination.cpp)
    add_library(second_examination_library second_examination.cpp)
    target_include_directories(first_examination_library
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/first_examination
    )
    target_include_directories(second_examination_library
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/second_examination
    )

    target_link_libraries(first_examination_library PRIVATE SFML::Graphics)
    target_link_libraries(second_examination_library PRIVATE SFML::Graphics)
    target_link_libraries(first_examination_library PUBLIC serial)
    target_link_libraries(second_examination_library PUBLIC serial)
endif()
