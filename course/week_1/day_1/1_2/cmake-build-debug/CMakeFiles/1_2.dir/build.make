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
CMAKE_SOURCE_DIR = "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/1_2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/1_2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1_2.dir/flags.make

CMakeFiles/1_2.dir/numberGame.cpp.o: CMakeFiles/1_2.dir/flags.make
CMakeFiles/1_2.dir/numberGame.cpp.o: ../numberGame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1_2.dir/numberGame.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/1_2.dir/numberGame.cpp.o -c "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/numberGame.cpp"

CMakeFiles/1_2.dir/numberGame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1_2.dir/numberGame.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/numberGame.cpp" > CMakeFiles/1_2.dir/numberGame.cpp.i

CMakeFiles/1_2.dir/numberGame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1_2.dir/numberGame.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/numberGame.cpp" -o CMakeFiles/1_2.dir/numberGame.cpp.s

CMakeFiles/1_2.dir/getNumber.cpp.o: CMakeFiles/1_2.dir/flags.make
CMakeFiles/1_2.dir/getNumber.cpp.o: ../getNumber.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/1_2.dir/getNumber.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/1_2.dir/getNumber.cpp.o -c "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/getNumber.cpp"

CMakeFiles/1_2.dir/getNumber.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1_2.dir/getNumber.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/getNumber.cpp" > CMakeFiles/1_2.dir/getNumber.cpp.i

CMakeFiles/1_2.dir/getNumber.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1_2.dir/getNumber.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/getNumber.cpp" -o CMakeFiles/1_2.dir/getNumber.cpp.s

CMakeFiles/1_2.dir/playGame.cpp.o: CMakeFiles/1_2.dir/flags.make
CMakeFiles/1_2.dir/playGame.cpp.o: ../playGame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/1_2.dir/playGame.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/1_2.dir/playGame.cpp.o -c "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/playGame.cpp"

CMakeFiles/1_2.dir/playGame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1_2.dir/playGame.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/playGame.cpp" > CMakeFiles/1_2.dir/playGame.cpp.i

CMakeFiles/1_2.dir/playGame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1_2.dir/playGame.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/playGame.cpp" -o CMakeFiles/1_2.dir/playGame.cpp.s

# Object files for target 1_2
1_2_OBJECTS = \
"CMakeFiles/1_2.dir/numberGame.cpp.o" \
"CMakeFiles/1_2.dir/getNumber.cpp.o" \
"CMakeFiles/1_2.dir/playGame.cpp.o"

# External object files for target 1_2
1_2_EXTERNAL_OBJECTS =

1_2: CMakeFiles/1_2.dir/numberGame.cpp.o
1_2: CMakeFiles/1_2.dir/getNumber.cpp.o
1_2: CMakeFiles/1_2.dir/playGame.cpp.o
1_2: CMakeFiles/1_2.dir/build.make
1_2: CMakeFiles/1_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable 1_2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/1_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1_2.dir/build: 1_2

.PHONY : CMakeFiles/1_2.dir/build

CMakeFiles/1_2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/1_2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/1_2.dir/clean

CMakeFiles/1_2.dir/depend:
	cd "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2" "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2" "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/cmake-build-debug" "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/cmake-build-debug" "/home/jason/Desktop/Courses/Uni-stuff/Block C++/1_2/cmake-build-debug/CMakeFiles/1_2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/1_2.dir/depend
