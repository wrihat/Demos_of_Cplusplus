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
CMAKE_SOURCE_DIR = /home/jiajun/workspace/demos_of_cplusplus/TopK

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jiajun/workspace/demos_of_cplusplus/TopK/build

# Include any dependencies generated for this target.
include CMakeFiles/program_exe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/program_exe.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/program_exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/program_exe.dir/flags.make

CMakeFiles/program_exe.dir/heap.cpp.o: CMakeFiles/program_exe.dir/flags.make
CMakeFiles/program_exe.dir/heap.cpp.o: ../heap.cpp
CMakeFiles/program_exe.dir/heap.cpp.o: CMakeFiles/program_exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiajun/workspace/demos_of_cplusplus/TopK/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/program_exe.dir/heap.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/program_exe.dir/heap.cpp.o -MF CMakeFiles/program_exe.dir/heap.cpp.o.d -o CMakeFiles/program_exe.dir/heap.cpp.o -c /home/jiajun/workspace/demos_of_cplusplus/TopK/heap.cpp

CMakeFiles/program_exe.dir/heap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/program_exe.dir/heap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiajun/workspace/demos_of_cplusplus/TopK/heap.cpp > CMakeFiles/program_exe.dir/heap.cpp.i

CMakeFiles/program_exe.dir/heap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/program_exe.dir/heap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiajun/workspace/demos_of_cplusplus/TopK/heap.cpp -o CMakeFiles/program_exe.dir/heap.cpp.s

# Object files for target program_exe
program_exe_OBJECTS = \
"CMakeFiles/program_exe.dir/heap.cpp.o"

# External object files for target program_exe
program_exe_EXTERNAL_OBJECTS =

../bin/program_exe: CMakeFiles/program_exe.dir/heap.cpp.o
../bin/program_exe: CMakeFiles/program_exe.dir/build.make
../bin/program_exe: CMakeFiles/program_exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jiajun/workspace/demos_of_cplusplus/TopK/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/program_exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/program_exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/program_exe.dir/build: ../bin/program_exe
.PHONY : CMakeFiles/program_exe.dir/build

CMakeFiles/program_exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/program_exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/program_exe.dir/clean

CMakeFiles/program_exe.dir/depend:
	cd /home/jiajun/workspace/demos_of_cplusplus/TopK/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jiajun/workspace/demos_of_cplusplus/TopK /home/jiajun/workspace/demos_of_cplusplus/TopK /home/jiajun/workspace/demos_of_cplusplus/TopK/build /home/jiajun/workspace/demos_of_cplusplus/TopK/build /home/jiajun/workspace/demos_of_cplusplus/TopK/build/CMakeFiles/program_exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/program_exe.dir/depend

