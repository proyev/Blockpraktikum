# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/139/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/139/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/jason/Desktop/Courses/Uni-stuff/Block C++/day_5/5_1_1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/jason/Desktop/Courses/Uni-stuff/Block C++/day_5/5_1_1/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/5_1_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/5_1_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/5_1_1.dir/flags.make

CMakeFiles/5_1_1.dir/main.cpp.o: CMakeFiles/5_1_1.dir/flags.make
CMakeFiles/5_1_1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/jason/Desktop/Courses/Uni-stuff/Block C++/day_5/5_1_1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/5_1_1.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/5_1_1.dir/main.cpp.o -c "/home/jason/Desktop/Courses/Uni-stuff/Block C++/day_5/5_1_1/main.cpp"

CMakeFiles/5_1_1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/5_1_1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/jason/Desktop/Courses/Uni-stuff/Block C++/day_5/5_1_1/main.cpp" > CMakeFiles/5_1_1.dir/main.cpp.i

CMakeFiles/5_1_1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/5_1_1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/jason/Desktop/Courses/Uni-stuff/Block C++/day_5/5_1_1/main.cpp" -o CMakeFiles/5_1_1.dir/main.cpp.s

# Object files for target 5_1_1
5_1_1_OBJECTS = \
"CMakeFiles/5_1_1.dir/main.cpp.o"

# External object files for target 5_1_1
5_1_1_EXTERNAL_OBJECTS =

5_1_1: CMakeFiles/5_1_1.dir/main.cpp.o
5_1_1: CMakeFiles/5_1_1.dir/build.make
5_1_1: CMakeFiles/5_1_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/jason/Desktop/Courses/Uni-stuff/Block C++/day_5/5_1_1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 5_1_1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/5_1_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/5_1_1.dir/build: 5_1_1

.PHONY : CMakeFiles/5_1_1.dir/build

CMakeFiles/5_1_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/5_1_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/5_1_1.dir/clean

CMakeFiles/5_1_1.dir/depend:
	cd "/home/jason/Desktop/Courses/Uni-stuff/Block C++/day_5/5_1_1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/jason/Desktop/Courses/Uni-stuff/Block C++/day_5/5_1_1" "/home/jason/Desktop/Courses/Uni-stuff/Block C++/day_5/5_1_1" "/home/jason/Desktop/Courses/Uni-stuff/Block C++/day_5/5_1_1/cmake-build-debug" "/home/jason/Desktop/Courses/Uni-stuff/Block C++/day_5/5_1_1/cmake-build-debug" "/home/jason/Desktop/Courses/Uni-stuff/Block C++/day_5/5_1_1/cmake-build-debug/CMakeFiles/5_1_1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/5_1_1.dir/depend

