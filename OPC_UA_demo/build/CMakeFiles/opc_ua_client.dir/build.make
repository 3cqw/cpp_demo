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
CMAKE_SOURCE_DIR = /home/cqw/github_db/cpp_demo/OPC_UA_demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cqw/github_db/cpp_demo/OPC_UA_demo/build

# Include any dependencies generated for this target.
include CMakeFiles/opc_ua_client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/opc_ua_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/opc_ua_client.dir/flags.make

CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o: CMakeFiles/opc_ua_client.dir/flags.make
CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o: ../opc_ua_client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cqw/github_db/cpp_demo/OPC_UA_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o -c /home/cqw/github_db/cpp_demo/OPC_UA_demo/opc_ua_client.cpp

CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cqw/github_db/cpp_demo/OPC_UA_demo/opc_ua_client.cpp > CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.i

CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cqw/github_db/cpp_demo/OPC_UA_demo/opc_ua_client.cpp -o CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.s

CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o.requires:

.PHONY : CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o.requires

CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o.provides: CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o.requires
	$(MAKE) -f CMakeFiles/opc_ua_client.dir/build.make CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o.provides.build
.PHONY : CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o.provides

CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o.provides.build: CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o


# Object files for target opc_ua_client
opc_ua_client_OBJECTS = \
"CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o"

# External object files for target opc_ua_client
opc_ua_client_EXTERNAL_OBJECTS =

opc_ua_client: CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o
opc_ua_client: CMakeFiles/opc_ua_client.dir/build.make
opc_ua_client: CMakeFiles/opc_ua_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cqw/github_db/cpp_demo/OPC_UA_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable opc_ua_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opc_ua_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/opc_ua_client.dir/build: opc_ua_client

.PHONY : CMakeFiles/opc_ua_client.dir/build

CMakeFiles/opc_ua_client.dir/requires: CMakeFiles/opc_ua_client.dir/opc_ua_client.cpp.o.requires

.PHONY : CMakeFiles/opc_ua_client.dir/requires

CMakeFiles/opc_ua_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/opc_ua_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/opc_ua_client.dir/clean

CMakeFiles/opc_ua_client.dir/depend:
	cd /home/cqw/github_db/cpp_demo/OPC_UA_demo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cqw/github_db/cpp_demo/OPC_UA_demo /home/cqw/github_db/cpp_demo/OPC_UA_demo /home/cqw/github_db/cpp_demo/OPC_UA_demo/build /home/cqw/github_db/cpp_demo/OPC_UA_demo/build /home/cqw/github_db/cpp_demo/OPC_UA_demo/build/CMakeFiles/opc_ua_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/opc_ua_client.dir/depend

