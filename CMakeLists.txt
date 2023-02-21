cmake_minimum_required(VERSION 3.23)
project(madness-tactical)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_MODULE_PATH 2.5.1 "${SFML_DIR}/lib/cmake/SFML" ${CMAKE_MODULE_PATH})
find_package(SFML COMPONENTS graphics window system)

add_executable(madness-tactical
        src/main.cpp)

target_link_libraries(madness-tactical sfml-graphics sfml-system sfml-window)