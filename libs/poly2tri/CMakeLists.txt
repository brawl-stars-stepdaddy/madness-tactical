cmake_minimum_required(VERSION 3.0)

project(poly2tri CXX)

# Set up library sources and headers
set(LIB_SOURCES
        src/advancing_front.cc
        src/cdt.cc
        src/shapes.cc
        src/sweep.cc
        src/sweep_context.cc
        )
set(LIB_HEADERS
        include/poly2tri/advancing_front.h
        include/poly2tri/cdt.h
        include/poly2tri/dll_symbol.h
        include/poly2tri/poly2tri.h
        include/poly2tri/shapes.h
        include/poly2tri/sweep.h
        include/poly2tri/sweep_context.h
        include/poly2tri/utils.h
        )

# Set up library target
add_library(poly2tri STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Set up include directories
target_include_directories(poly2tri PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set up installation
install(TARGETS poly2tri ARCHIVE DESTINATION lib)
install(FILES ${LIB_HEADERS} DESTINATION include/clipper2)
