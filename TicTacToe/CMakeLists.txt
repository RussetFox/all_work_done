cmake_minimum_required(VERSION 3.22)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 14)

add_executable(TicTacToe main.cpp AI.cpp AI.h gameUI.cpp gameUI.h gameHandling.cpp gameHandling.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(TicTacToe sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
