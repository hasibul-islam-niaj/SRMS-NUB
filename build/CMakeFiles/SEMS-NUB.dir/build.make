# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /workspaces/SRMS-NUB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/SRMS-NUB/build

# Include any dependencies generated for this target.
include CMakeFiles/SEMS-NUB.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SEMS-NUB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SEMS-NUB.dir/flags.make

CMakeFiles/SEMS-NUB.dir/main.c.o: CMakeFiles/SEMS-NUB.dir/flags.make
CMakeFiles/SEMS-NUB.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/SRMS-NUB/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SEMS-NUB.dir/main.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SEMS-NUB.dir/main.c.o   -c /workspaces/SRMS-NUB/main.c

CMakeFiles/SEMS-NUB.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SEMS-NUB.dir/main.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/SRMS-NUB/main.c > CMakeFiles/SEMS-NUB.dir/main.c.i

CMakeFiles/SEMS-NUB.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SEMS-NUB.dir/main.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/SRMS-NUB/main.c -o CMakeFiles/SEMS-NUB.dir/main.c.s

# Object files for target SEMS-NUB
SEMS__NUB_OBJECTS = \
"CMakeFiles/SEMS-NUB.dir/main.c.o"

# External object files for target SEMS-NUB
SEMS__NUB_EXTERNAL_OBJECTS =

SEMS-NUB: CMakeFiles/SEMS-NUB.dir/main.c.o
SEMS-NUB: CMakeFiles/SEMS-NUB.dir/build.make
SEMS-NUB: CMakeFiles/SEMS-NUB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/SRMS-NUB/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable SEMS-NUB"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SEMS-NUB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SEMS-NUB.dir/build: SEMS-NUB

.PHONY : CMakeFiles/SEMS-NUB.dir/build

CMakeFiles/SEMS-NUB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SEMS-NUB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SEMS-NUB.dir/clean

CMakeFiles/SEMS-NUB.dir/depend:
	cd /workspaces/SRMS-NUB/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/SRMS-NUB /workspaces/SRMS-NUB /workspaces/SRMS-NUB/build /workspaces/SRMS-NUB/build /workspaces/SRMS-NUB/build/CMakeFiles/SEMS-NUB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SEMS-NUB.dir/depend
