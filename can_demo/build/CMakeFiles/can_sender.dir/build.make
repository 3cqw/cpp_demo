# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cqw/github_db/cpp_demo/can_demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cqw/github_db/cpp_demo/can_demo/build

# Include any dependencies generated for this target.
include CMakeFiles/can_sender.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/can_sender.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/can_sender.dir/flags.make

CMakeFiles/can_sender.dir/can_sender.cpp.o: CMakeFiles/can_sender.dir/flags.make
CMakeFiles/can_sender.dir/can_sender.cpp.o: ../can_sender.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cqw/github_db/cpp_demo/can_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/can_sender.dir/can_sender.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/can_sender.dir/can_sender.cpp.o -c /home/cqw/github_db/cpp_demo/can_demo/can_sender.cpp

CMakeFiles/can_sender.dir/can_sender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/can_sender.dir/can_sender.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cqw/github_db/cpp_demo/can_demo/can_sender.cpp > CMakeFiles/can_sender.dir/can_sender.cpp.i

CMakeFiles/can_sender.dir/can_sender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/can_sender.dir/can_sender.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cqw/github_db/cpp_demo/can_demo/can_sender.cpp -o CMakeFiles/can_sender.dir/can_sender.cpp.s

CMakeFiles/can_sender.dir/can_sender.cpp.o.requires:

.PHONY : CMakeFiles/can_sender.dir/can_sender.cpp.o.requires

CMakeFiles/can_sender.dir/can_sender.cpp.o.provides: CMakeFiles/can_sender.dir/can_sender.cpp.o.requires
	$(MAKE) -f CMakeFiles/can_sender.dir/build.make CMakeFiles/can_sender.dir/can_sender.cpp.o.provides.build
.PHONY : CMakeFiles/can_sender.dir/can_sender.cpp.o.provides

CMakeFiles/can_sender.dir/can_sender.cpp.o.provides.build: CMakeFiles/can_sender.dir/can_sender.cpp.o


# Object files for target can_sender
can_sender_OBJECTS = \
"CMakeFiles/can_sender.dir/can_sender.cpp.o"

# External object files for target can_sender
can_sender_EXTERNAL_OBJECTS =

can_sender: CMakeFiles/can_sender.dir/can_sender.cpp.o
can_sender: CMakeFiles/can_sender.dir/build.make
can_sender: CMakeFiles/can_sender.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cqw/github_db/cpp_demo/can_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable can_sender"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/can_sender.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/can_sender.dir/build: can_sender

.PHONY : CMakeFiles/can_sender.dir/build

CMakeFiles/can_sender.dir/requires: CMakeFiles/can_sender.dir/can_sender.cpp.o.requires

.PHONY : CMakeFiles/can_sender.dir/requires

CMakeFiles/can_sender.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/can_sender.dir/cmake_clean.cmake
.PHONY : CMakeFiles/can_sender.dir/clean

CMakeFiles/can_sender.dir/depend:
	cd /home/cqw/github_db/cpp_demo/can_demo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cqw/github_db/cpp_demo/can_demo /home/cqw/github_db/cpp_demo/can_demo /home/cqw/github_db/cpp_demo/can_demo/build /home/cqw/github_db/cpp_demo/can_demo/build /home/cqw/github_db/cpp_demo/can_demo/build/CMakeFiles/can_sender.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/can_sender.dir/depend

