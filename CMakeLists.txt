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
        src/Body.cpp
        src/CircleBody.cpp
        src/Entity.cpp
        src/EventManager.cpp
        src/Explosion.cpp
        src/ExplosionEventData.cpp
        src/ExplosionEventListener.cpp
        src/Game.cpp
        src/main.cpp
        src/Map.cpp
        src/MapBody.cpp
        src/RectBody.cpp
        src/SceneNode.cpp
        src/SpriteNode.cpp
        src/Unit.cpp
        src/World.cpp
)

target_link_libraries(madness-tactical
        sfml-graphics sfml-system sfml-window
        box2d
        clipper2
        polypartition
        )