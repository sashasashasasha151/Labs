# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.10

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\sasha\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\181.4096.19\bin\cmake\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\sasha\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\181.4096.19\bin\cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Code\Labs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Code\Labs\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Labs.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Labs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Labs.dir/flags.make

CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj: CMakeFiles/Labs.dir/flags.make
CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj: ../Algorithms/Streams/flow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Code\Labs\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj"
	C:\MinGW\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Labs.dir\Algorithms\Streams\flow.cpp.obj -c C:\Code\Labs\Algorithms\Streams\flow.cpp

CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.i"
	C:\MinGW\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Code\Labs\Algorithms\Streams\flow.cpp > CMakeFiles\Labs.dir\Algorithms\Streams\flow.cpp.i

CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.s"
	C:\MinGW\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Code\Labs\Algorithms\Streams\flow.cpp -o CMakeFiles\Labs.dir\Algorithms\Streams\flow.cpp.s

CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj.requires:

.PHONY : CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj.requires

CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj.provides: CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj.requires
	$(MAKE) -f CMakeFiles\Labs.dir\build.make CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj.provides.build
.PHONY : CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj.provides

CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj.provides.build: CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj


# Object files for target Labs
Labs_OBJECTS = \
"CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj"

# External object files for target Labs
Labs_EXTERNAL_OBJECTS =

Labs.exe: CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj
Labs.exe: CMakeFiles/Labs.dir/build.make
Labs.exe: CMakeFiles/Labs.dir/linklibs.rsp
Labs.exe: CMakeFiles/Labs.dir/objects1.rsp
Labs.exe: CMakeFiles/Labs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Code\Labs\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Labs.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Labs.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Labs.dir/build: Labs.exe

.PHONY : CMakeFiles/Labs.dir/build

CMakeFiles/Labs.dir/requires: CMakeFiles/Labs.dir/Algorithms/Streams/flow.cpp.obj.requires

.PHONY : CMakeFiles/Labs.dir/requires

CMakeFiles/Labs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Labs.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Labs.dir/clean

CMakeFiles/Labs.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Code\Labs C:\Code\Labs C:\Code\Labs\cmake-build-debug C:\Code\Labs\cmake-build-debug C:\Code\Labs\cmake-build-debug\CMakeFiles\Labs.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Labs.dir/depend

