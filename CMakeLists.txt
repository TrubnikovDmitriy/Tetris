cmake_minimum_required(VERSION 3.6)
project(Clion_Tetris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Werror -Wextra -Wpedantic -Ofast")

set(
        SOURCE_FILES
        main.cpp
        Field.hpp
        Field.cpp
        Figure.hpp
        Figure.cpp
        Utils.hpp
        Blocks.hpp
        Blocks.cpp
        Sounds.hpp
        Images.hpp
        Fonts.hpp)
add_executable(Clion_Tetris ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/SFML-find")
find_package(SFML REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Clion_Tetris ${SFML_LIBRARIES})
endif()