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
CMAKE_SOURCE_DIR = /home/jiajun/workspace/demos_of_cplusplus/LRU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jiajun/workspace/demos_of_cplusplus/LRU/build

# Include any dependencies generated for this target.
include CMakeFiles/lru.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lru.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lru.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lru.dir/flags.make

CMakeFiles/lru.dir/lru.cpp.o: CMakeFiles/lru.dir/flags.make
CMakeFiles/lru.dir/lru.cpp.o: ../lru.cpp
CMakeFiles/lru.dir/lru.cpp.o: CMakeFiles/lru.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiajun/workspace/demos_of_cplusplus/LRU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lru.dir/lru.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lru.dir/lru.cpp.o -MF CMakeFiles/lru.dir/lru.cpp.o.d -o CMakeFiles/lru.dir/lru.cpp.o -c /home/jiajun/workspace/demos_of_cplusplus/LRU/lru.cpp

CMakeFiles/lru.dir/lru.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lru.dir/lru.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiajun/workspace/demos_of_cplusplus/LRU/lru.cpp > CMakeFiles/lru.dir/lru.cpp.i

CMakeFiles/lru.dir/lru.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lru.dir/lru.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiajun/workspace/demos_of_cplusplus/LRU/lru.cpp -o CMakeFiles/lru.dir/lru.cpp.s

# Object files for target lru
lru_OBJECTS = \
"CMakeFiles/lru.dir/lru.cpp.o"

# External object files for target lru
lru_EXTERNAL_OBJECTS =

../bin/lru: CMakeFiles/lru.dir/lru.cpp.o
../bin/lru: CMakeFiles/lru.dir/build.make
../bin/lru: CMakeFiles/lru.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jiajun/workspace/demos_of_cplusplus/LRU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/lru"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lru.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lru.dir/build: ../bin/lru
.PHONY : CMakeFiles/lru.dir/build

CMakeFiles/lru.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lru.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lru.dir/clean

CMakeFiles/lru.dir/depend:
	cd /home/jiajun/workspace/demos_of_cplusplus/LRU/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jiajun/workspace/demos_of_cplusplus/LRU /home/jiajun/workspace/demos_of_cplusplus/LRU /home/jiajun/workspace/demos_of_cplusplus/LRU/build /home/jiajun/workspace/demos_of_cplusplus/LRU/build /home/jiajun/workspace/demos_of_cplusplus/LRU/build/CMakeFiles/lru.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lru.dir/depend

