# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/daniel/Códigos/CSA-Direct-Construction

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daniel/Códigos/CSA-Direct-Construction

# Include any dependencies generated for this target.
include src/CMakeFiles/csa.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/csa.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/csa.dir/flags.make

src/CMakeFiles/csa.dir/main.cpp.o: src/CMakeFiles/csa.dir/flags.make
src/CMakeFiles/csa.dir/main.cpp.o: src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/Códigos/CSA-Direct-Construction/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/csa.dir/main.cpp.o"
	cd /home/daniel/Códigos/CSA-Direct-Construction/src && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/csa.dir/main.cpp.o -c /home/daniel/Códigos/CSA-Direct-Construction/src/main.cpp

src/CMakeFiles/csa.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/csa.dir/main.cpp.i"
	cd /home/daniel/Códigos/CSA-Direct-Construction/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/daniel/Códigos/CSA-Direct-Construction/src/main.cpp > CMakeFiles/csa.dir/main.cpp.i

src/CMakeFiles/csa.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/csa.dir/main.cpp.s"
	cd /home/daniel/Códigos/CSA-Direct-Construction/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/daniel/Códigos/CSA-Direct-Construction/src/main.cpp -o CMakeFiles/csa.dir/main.cpp.s

src/CMakeFiles/csa.dir/main.cpp.o.requires:
.PHONY : src/CMakeFiles/csa.dir/main.cpp.o.requires

src/CMakeFiles/csa.dir/main.cpp.o.provides: src/CMakeFiles/csa.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/csa.dir/build.make src/CMakeFiles/csa.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/csa.dir/main.cpp.o.provides

src/CMakeFiles/csa.dir/main.cpp.o.provides.build: src/CMakeFiles/csa.dir/main.cpp.o

src/CMakeFiles/csa.dir/suffixSorting.cpp.o: src/CMakeFiles/csa.dir/flags.make
src/CMakeFiles/csa.dir/suffixSorting.cpp.o: src/suffixSorting.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/Códigos/CSA-Direct-Construction/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/csa.dir/suffixSorting.cpp.o"
	cd /home/daniel/Códigos/CSA-Direct-Construction/src && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/csa.dir/suffixSorting.cpp.o -c /home/daniel/Códigos/CSA-Direct-Construction/src/suffixSorting.cpp

src/CMakeFiles/csa.dir/suffixSorting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/csa.dir/suffixSorting.cpp.i"
	cd /home/daniel/Códigos/CSA-Direct-Construction/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/daniel/Códigos/CSA-Direct-Construction/src/suffixSorting.cpp > CMakeFiles/csa.dir/suffixSorting.cpp.i

src/CMakeFiles/csa.dir/suffixSorting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/csa.dir/suffixSorting.cpp.s"
	cd /home/daniel/Códigos/CSA-Direct-Construction/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/daniel/Códigos/CSA-Direct-Construction/src/suffixSorting.cpp -o CMakeFiles/csa.dir/suffixSorting.cpp.s

src/CMakeFiles/csa.dir/suffixSorting.cpp.o.requires:
.PHONY : src/CMakeFiles/csa.dir/suffixSorting.cpp.o.requires

src/CMakeFiles/csa.dir/suffixSorting.cpp.o.provides: src/CMakeFiles/csa.dir/suffixSorting.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/csa.dir/build.make src/CMakeFiles/csa.dir/suffixSorting.cpp.o.provides.build
.PHONY : src/CMakeFiles/csa.dir/suffixSorting.cpp.o.provides

src/CMakeFiles/csa.dir/suffixSorting.cpp.o.provides.build: src/CMakeFiles/csa.dir/suffixSorting.cpp.o

# Object files for target csa
csa_OBJECTS = \
"CMakeFiles/csa.dir/main.cpp.o" \
"CMakeFiles/csa.dir/suffixSorting.cpp.o"

# External object files for target csa
csa_EXTERNAL_OBJECTS =

src/csa: src/CMakeFiles/csa.dir/main.cpp.o
src/csa: src/CMakeFiles/csa.dir/suffixSorting.cpp.o
src/csa: src/CMakeFiles/csa.dir/build.make
src/csa: src/CMakeFiles/csa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable csa"
	cd /home/daniel/Códigos/CSA-Direct-Construction/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/csa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/csa.dir/build: src/csa
.PHONY : src/CMakeFiles/csa.dir/build

src/CMakeFiles/csa.dir/requires: src/CMakeFiles/csa.dir/main.cpp.o.requires
src/CMakeFiles/csa.dir/requires: src/CMakeFiles/csa.dir/suffixSorting.cpp.o.requires
.PHONY : src/CMakeFiles/csa.dir/requires

src/CMakeFiles/csa.dir/clean:
	cd /home/daniel/Códigos/CSA-Direct-Construction/src && $(CMAKE_COMMAND) -P CMakeFiles/csa.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/csa.dir/clean

src/CMakeFiles/csa.dir/depend:
	cd /home/daniel/Códigos/CSA-Direct-Construction && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daniel/Códigos/CSA-Direct-Construction /home/daniel/Códigos/CSA-Direct-Construction/src /home/daniel/Códigos/CSA-Direct-Construction /home/daniel/Códigos/CSA-Direct-Construction/src /home/daniel/Códigos/CSA-Direct-Construction/src/CMakeFiles/csa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/csa.dir/depend

