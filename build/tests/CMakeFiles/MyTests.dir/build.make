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
CMAKE_SOURCE_DIR = /home/zpr/Documents/Tiding/zpr

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zpr/Documents/Tiding/zpr/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/MyTests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/MyTests.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/MyTests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/MyTests.dir/flags.make

tests/CMakeFiles/MyTests.dir/test.cpp.o: tests/CMakeFiles/MyTests.dir/flags.make
tests/CMakeFiles/MyTests.dir/test.cpp.o: ../tests/test.cpp
tests/CMakeFiles/MyTests.dir/test.cpp.o: tests/CMakeFiles/MyTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zpr/Documents/Tiding/zpr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/MyTests.dir/test.cpp.o"
	cd /home/zpr/Documents/Tiding/zpr/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/MyTests.dir/test.cpp.o -MF CMakeFiles/MyTests.dir/test.cpp.o.d -o CMakeFiles/MyTests.dir/test.cpp.o -c /home/zpr/Documents/Tiding/zpr/tests/test.cpp

tests/CMakeFiles/MyTests.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyTests.dir/test.cpp.i"
	cd /home/zpr/Documents/Tiding/zpr/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zpr/Documents/Tiding/zpr/tests/test.cpp > CMakeFiles/MyTests.dir/test.cpp.i

tests/CMakeFiles/MyTests.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyTests.dir/test.cpp.s"
	cd /home/zpr/Documents/Tiding/zpr/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zpr/Documents/Tiding/zpr/tests/test.cpp -o CMakeFiles/MyTests.dir/test.cpp.s

# Object files for target MyTests
MyTests_OBJECTS = \
"CMakeFiles/MyTests.dir/test.cpp.o"

# External object files for target MyTests
MyTests_EXTERNAL_OBJECTS =

tests/MyTests: tests/CMakeFiles/MyTests.dir/test.cpp.o
tests/MyTests: tests/CMakeFiles/MyTests.dir/build.make
tests/MyTests: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so.1.74.0
tests/MyTests: tests/CMakeFiles/MyTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zpr/Documents/Tiding/zpr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MyTests"
	cd /home/zpr/Documents/Tiding/zpr/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/MyTests.dir/build: tests/MyTests
.PHONY : tests/CMakeFiles/MyTests.dir/build

tests/CMakeFiles/MyTests.dir/clean:
	cd /home/zpr/Documents/Tiding/zpr/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/MyTests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/MyTests.dir/clean

tests/CMakeFiles/MyTests.dir/depend:
	cd /home/zpr/Documents/Tiding/zpr/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zpr/Documents/Tiding/zpr /home/zpr/Documents/Tiding/zpr/tests /home/zpr/Documents/Tiding/zpr/build /home/zpr/Documents/Tiding/zpr/build/tests /home/zpr/Documents/Tiding/zpr/build/tests/CMakeFiles/MyTests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/MyTests.dir/depend

