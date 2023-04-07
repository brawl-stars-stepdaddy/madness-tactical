cmake_minimum_required(VERSION 3.22.1)
project(madness-tactical)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH 2.5.1 "${SFML_DIR}/lib/cmake/SFML" ${CMAKE_MODULE_PATH})
find_package(SFML COMPONENTS graphics window system)

include_directories(${PROJECT_SOURCE_DIR}/libs/box2d/include)
link_directories(libs/box2d)

include_directories(include)
add_subdirectory(libs/clipper2)
add_subdirectory(libs/polypartition)

include_directories(include)

add_executable(madness-tactical
        src/main.cpp
        src/Game.cpp
        src/Body.cpp
        src/Entity.cpp
        src/SceneNode.cpp
        src/Unit.cpp
        src/Map.cpp
        src/WeaponEffect.cpp
        src/Character.cpp
        src/MapBody.cpp
        src/World.cpp
        src/SpriteNode.cpp
        src/RectBody.cpp
        src/UnitBody.cpp
)

target_link_libraries(madness-tactical
        sfml-graphics sfml-system sfml-window
        box2d
        clipper2
        polypartition
        )