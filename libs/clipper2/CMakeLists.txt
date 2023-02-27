cmake_minimum_required(VERSION 3.0)

project(clipper2 CXX)

# Set up library sources and headers
set(LIB_SOURCES
        src/clipper.engine.cpp
        src/clipper.offset.cpp
        src/clipper.rectclip.cpp
        )
set(LIB_HEADERS
        include/clipper2/clipper.h
        include/clipper2/clipper.core.h
        include/clipper2/clipper.engine.h
        include/clipper2/clipper.export.h
        include/clipper2/clipper.minkowski.h
        include/clipper2/clipper.offset.h
        include/clipper2/clipper.rectclip.h
        )

# Set up library target
add_library(clipper2 STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Set up include directories
target_include_directories(clipper2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set up installation
install(TARGETS clipper2 ARCHIVE DESTINATION lib)
install(FILES ${LIB_HEADERS} DESTINATION include/clipper2)
