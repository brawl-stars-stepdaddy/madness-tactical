# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dmitry_malikov/CLionProjects/madness-tactical

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dmitry_malikov/CLionProjects/madness-tactical

# Include any dependencies generated for this target.
include libs/clipper2/CMakeFiles/clipper2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include libs/clipper2/CMakeFiles/clipper2.dir/compiler_depend.make

# Include the progress variables for this target.
include libs/clipper2/CMakeFiles/clipper2.dir/progress.make

# Include the compile flags for this target's objects.
include libs/clipper2/CMakeFiles/clipper2.dir/flags.make

libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.engine.cpp.o: libs/clipper2/CMakeFiles/clipper2.dir/flags.make
libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.engine.cpp.o: libs/clipper2/src/clipper.engine.cpp
libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.engine.cpp.o: libs/clipper2/CMakeFiles/clipper2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry_malikov/CLionProjects/madness-tactical/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.engine.cpp.o"
	cd /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.engine.cpp.o -MF CMakeFiles/clipper2.dir/src/clipper.engine.cpp.o.d -o CMakeFiles/clipper2.dir/src/clipper.engine.cpp.o -c /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2/src/clipper.engine.cpp

libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clipper2.dir/src/clipper.engine.cpp.i"
	cd /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2/src/clipper.engine.cpp > CMakeFiles/clipper2.dir/src/clipper.engine.cpp.i

libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clipper2.dir/src/clipper.engine.cpp.s"
	cd /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2/src/clipper.engine.cpp -o CMakeFiles/clipper2.dir/src/clipper.engine.cpp.s

libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.offset.cpp.o: libs/clipper2/CMakeFiles/clipper2.dir/flags.make
libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.offset.cpp.o: libs/clipper2/src/clipper.offset.cpp
libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.offset.cpp.o: libs/clipper2/CMakeFiles/clipper2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry_malikov/CLionProjects/madness-tactical/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.offset.cpp.o"
	cd /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.offset.cpp.o -MF CMakeFiles/clipper2.dir/src/clipper.offset.cpp.o.d -o CMakeFiles/clipper2.dir/src/clipper.offset.cpp.o -c /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2/src/clipper.offset.cpp

libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.offset.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clipper2.dir/src/clipper.offset.cpp.i"
	cd /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2/src/clipper.offset.cpp > CMakeFiles/clipper2.dir/src/clipper.offset.cpp.i

libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.offset.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clipper2.dir/src/clipper.offset.cpp.s"
	cd /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2/src/clipper.offset.cpp -o CMakeFiles/clipper2.dir/src/clipper.offset.cpp.s

libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.o: libs/clipper2/CMakeFiles/clipper2.dir/flags.make
libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.o: libs/clipper2/src/clipper.rectclip.cpp
libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.o: libs/clipper2/CMakeFiles/clipper2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry_malikov/CLionProjects/madness-tactical/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.o"
	cd /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.o -MF CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.o.d -o CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.o -c /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2/src/clipper.rectclip.cpp

libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.i"
	cd /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2/src/clipper.rectclip.cpp > CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.i

libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.s"
	cd /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2/src/clipper.rectclip.cpp -o CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.s

# Object files for target clipper2
clipper2_OBJECTS = \
"CMakeFiles/clipper2.dir/src/clipper.engine.cpp.o" \
"CMakeFiles/clipper2.dir/src/clipper.offset.cpp.o" \
"CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.o"

# External object files for target clipper2
clipper2_EXTERNAL_OBJECTS =

libs/clipper2/libclipper2.a: libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.engine.cpp.o
libs/clipper2/libclipper2.a: libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.offset.cpp.o
libs/clipper2/libclipper2.a: libs/clipper2/CMakeFiles/clipper2.dir/src/clipper.rectclip.cpp.o
libs/clipper2/libclipper2.a: libs/clipper2/CMakeFiles/clipper2.dir/build.make
libs/clipper2/libclipper2.a: libs/clipper2/CMakeFiles/clipper2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dmitry_malikov/CLionProjects/madness-tactical/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libclipper2.a"
	cd /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 && $(CMAKE_COMMAND) -P CMakeFiles/clipper2.dir/cmake_clean_target.cmake
	cd /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clipper2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/clipper2/CMakeFiles/clipper2.dir/build: libs/clipper2/libclipper2.a
.PHONY : libs/clipper2/CMakeFiles/clipper2.dir/build

libs/clipper2/CMakeFiles/clipper2.dir/clean:
	cd /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 && $(CMAKE_COMMAND) -P CMakeFiles/clipper2.dir/cmake_clean.cmake
.PHONY : libs/clipper2/CMakeFiles/clipper2.dir/clean

libs/clipper2/CMakeFiles/clipper2.dir/depend:
	cd /home/dmitry_malikov/CLionProjects/madness-tactical && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dmitry_malikov/CLionProjects/madness-tactical /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 /home/dmitry_malikov/CLionProjects/madness-tactical /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2 /home/dmitry_malikov/CLionProjects/madness-tactical/libs/clipper2/CMakeFiles/clipper2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/clipper2/CMakeFiles/clipper2.dir/depend

