# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /snap/clion/235/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/235/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alberto/CLionProjects/HUGO1.1/source/hugo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alberto/CLionProjects/HUGO1.1/source/hugo/cmake-build-debug

# Utility rule file for hugo_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/hugo_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/hugo_autogen.dir/progress.make

CMakeFiles/hugo_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/alberto/CLionProjects/HUGO1.1/source/hugo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target hugo"
	/snap/clion/235/bin/cmake/linux/x64/bin/cmake -E cmake_autogen /home/alberto/CLionProjects/HUGO1.1/source/hugo/cmake-build-debug/CMakeFiles/hugo_autogen.dir/AutogenInfo.json Debug

hugo_autogen: CMakeFiles/hugo_autogen
hugo_autogen: CMakeFiles/hugo_autogen.dir/build.make
.PHONY : hugo_autogen

# Rule to build all files generated by this target.
CMakeFiles/hugo_autogen.dir/build: hugo_autogen
.PHONY : CMakeFiles/hugo_autogen.dir/build

CMakeFiles/hugo_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hugo_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hugo_autogen.dir/clean

CMakeFiles/hugo_autogen.dir/depend:
	cd /home/alberto/CLionProjects/HUGO1.1/source/hugo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alberto/CLionProjects/HUGO1.1/source/hugo /home/alberto/CLionProjects/HUGO1.1/source/hugo /home/alberto/CLionProjects/HUGO1.1/source/hugo/cmake-build-debug /home/alberto/CLionProjects/HUGO1.1/source/hugo/cmake-build-debug /home/alberto/CLionProjects/HUGO1.1/source/hugo/cmake-build-debug/CMakeFiles/hugo_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hugo_autogen.dir/depend
