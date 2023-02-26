cmake_minimum_required(VERSION 3.23)
project(madness-tactical)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH 2.5.1 "${SFML_DIR}/lib/cmake/SFML" ${CMAKE_MODULE_PATH})
find_package(SFML COMPONENTS graphics window system)

include_directories(${CMAKE_SOURCE_DIR}/include)
find_library(BOX2D_LIB libbox2d.a lib)

add_executable(madness-tactical
        src/main.cpp)

target_link_libraries(madness-tactical sfml-graphics sfml-system sfml-window)
target_link_libraries(madness-tactical ${BOX2D_LIB})