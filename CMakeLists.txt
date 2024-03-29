cmake_minimum_required(VERSION 3.20.1)
project(madness-tactical)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH 2.5.1 "${SFML_DIR}/lib/cmake/SFML" ${CMAKE_MODULE_PATH})
find_package(SFML COMPONENTS audio graphics window system network)

include_directories(${PROJECT_SOURCE_DIR}/libs/box2d/include)
link_directories(libs/box2d)

include_directories(include)
add_subdirectory(libs/clipper2)
add_subdirectory(libs/CDT)
add_subdirectory(libs/SimplexNoise)

file(GLOB_RECURSE SOURCES "src/game_objects/*.cpp" "src/gui/*.cpp" "src/logic/*.cpp" "src/utils/*.cpp")

add_executable(madness-tactical
        src/Main.cpp
        ${SOURCES}
)

add_executable(madness-tactical-server
        src/ServerMain.cpp
        src/logic/GameServer.cpp
)

target_link_libraries(madness-tactical
        sfml-audio sfml-graphics sfml-system sfml-window sfml-network
        box2d
        clipper2
        CDT
        SimplexNoise
        )

target_link_libraries(madness-tactical-server
        sfml-network
        )