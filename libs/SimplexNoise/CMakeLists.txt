cmake_minimum_required(VERSION 3.0)

project(SimplexNoise CXX)

# Set up library sources and headers
set(LIB_SOURCES
        SimplexNoise.cpp
        )
set(LIB_HEADERS
        SimplexNoise.h
        )

# Set up library target
add_library(SimplexNoise STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Set up include directories
target_include_directories(SimplexNoise PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set up installation
install(TARGETS SimplexNoise ARCHIVE DESTINATION lib)
install(FILES ${LIB_HEADERS} DESTINATION SimplexNoise)
