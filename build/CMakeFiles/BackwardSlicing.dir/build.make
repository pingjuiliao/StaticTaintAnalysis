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
CMAKE_SOURCE_DIR = /home/pingjui/StaticTaintAnalysis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pingjui/StaticTaintAnalysis/build

# Include any dependencies generated for this target.
include CMakeFiles/BackwardSlicing.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BackwardSlicing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BackwardSlicing.dir/flags.make

CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o: CMakeFiles/BackwardSlicing.dir/flags.make
CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o: ../script/pass.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pingjui/StaticTaintAnalysis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o -c /home/pingjui/StaticTaintAnalysis/script/pass.cpp

CMakeFiles/BackwardSlicing.dir/script/pass.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BackwardSlicing.dir/script/pass.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pingjui/StaticTaintAnalysis/script/pass.cpp > CMakeFiles/BackwardSlicing.dir/script/pass.cpp.i

CMakeFiles/BackwardSlicing.dir/script/pass.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BackwardSlicing.dir/script/pass.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pingjui/StaticTaintAnalysis/script/pass.cpp -o CMakeFiles/BackwardSlicing.dir/script/pass.cpp.s

CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o.requires:

.PHONY : CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o.requires

CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o.provides: CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o.requires
	$(MAKE) -f CMakeFiles/BackwardSlicing.dir/build.make CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o.provides.build
.PHONY : CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o.provides

CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o.provides.build: CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o


# Object files for target BackwardSlicing
BackwardSlicing_OBJECTS = \
"CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o"

# External object files for target BackwardSlicing
BackwardSlicing_EXTERNAL_OBJECTS =

libBackwardSlicing.so: CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o
libBackwardSlicing.so: CMakeFiles/BackwardSlicing.dir/build.make
libBackwardSlicing.so: CMakeFiles/BackwardSlicing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pingjui/StaticTaintAnalysis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module libBackwardSlicing.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BackwardSlicing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BackwardSlicing.dir/build: libBackwardSlicing.so

.PHONY : CMakeFiles/BackwardSlicing.dir/build

CMakeFiles/BackwardSlicing.dir/requires: CMakeFiles/BackwardSlicing.dir/script/pass.cpp.o.requires

.PHONY : CMakeFiles/BackwardSlicing.dir/requires

CMakeFiles/BackwardSlicing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BackwardSlicing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BackwardSlicing.dir/clean

CMakeFiles/BackwardSlicing.dir/depend:
	cd /home/pingjui/StaticTaintAnalysis/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pingjui/StaticTaintAnalysis /home/pingjui/StaticTaintAnalysis /home/pingjui/StaticTaintAnalysis/build /home/pingjui/StaticTaintAnalysis/build /home/pingjui/StaticTaintAnalysis/build/CMakeFiles/BackwardSlicing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BackwardSlicing.dir/depend

