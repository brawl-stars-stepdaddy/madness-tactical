cmake_minimum_required(VERSION 3.0)

project(polypartition CXX)

# Set up library sources and headers
set(LIB_SOURCES
        polypartition.cpp
        )
set(LIB_HEADERS
        polypartition.h
        )

# Set up library target
add_library(polypartition STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Set up include directories
target_include_directories(polypartition PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set up installation
install(TARGETS polypartition ARCHIVE DESTINATION lib)
install(FILES ${LIB_HEADERS} DESTINATION polypartition)
