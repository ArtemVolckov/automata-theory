# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/artem/ta/lab2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/artem/ta/lab2/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/test/catch2.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/test/catch2.cpp.o: /home/artem/ta/lab2/test/catch2.cpp
CMakeFiles/main.dir/test/catch2.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/artem/ta/lab2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/test/catch2.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/test/catch2.cpp.o -MF CMakeFiles/main.dir/test/catch2.cpp.o.d -o CMakeFiles/main.dir/test/catch2.cpp.o -c /home/artem/ta/lab2/test/catch2.cpp

CMakeFiles/main.dir/test/catch2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/test/catch2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artem/ta/lab2/test/catch2.cpp > CMakeFiles/main.dir/test/catch2.cpp.i

CMakeFiles/main.dir/test/catch2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/test/catch2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artem/ta/lab2/test/catch2.cpp -o CMakeFiles/main.dir/test/catch2.cpp.s

CMakeFiles/main.dir/regex/regex.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/regex/regex.cpp.o: /home/artem/ta/lab2/regex/regex.cpp
CMakeFiles/main.dir/regex/regex.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/artem/ta/lab2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/regex/regex.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/regex/regex.cpp.o -MF CMakeFiles/main.dir/regex/regex.cpp.o.d -o CMakeFiles/main.dir/regex/regex.cpp.o -c /home/artem/ta/lab2/regex/regex.cpp

CMakeFiles/main.dir/regex/regex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/regex/regex.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artem/ta/lab2/regex/regex.cpp > CMakeFiles/main.dir/regex/regex.cpp.i

CMakeFiles/main.dir/regex/regex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/regex/regex.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artem/ta/lab2/regex/regex.cpp -o CMakeFiles/main.dir/regex/regex.cpp.s

CMakeFiles/main.dir/ast/ast.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/ast/ast.cpp.o: /home/artem/ta/lab2/ast/ast.cpp
CMakeFiles/main.dir/ast/ast.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/artem/ta/lab2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/ast/ast.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/ast/ast.cpp.o -MF CMakeFiles/main.dir/ast/ast.cpp.o.d -o CMakeFiles/main.dir/ast/ast.cpp.o -c /home/artem/ta/lab2/ast/ast.cpp

CMakeFiles/main.dir/ast/ast.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/ast/ast.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artem/ta/lab2/ast/ast.cpp > CMakeFiles/main.dir/ast/ast.cpp.i

CMakeFiles/main.dir/ast/ast.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/ast/ast.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artem/ta/lab2/ast/ast.cpp -o CMakeFiles/main.dir/ast/ast.cpp.s

CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.o: /home/artem/ta/lab2/nfa_dfa/nfa_dfa.cpp
CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/artem/ta/lab2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.o -MF CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.o.d -o CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.o -c /home/artem/ta/lab2/nfa_dfa/nfa_dfa.cpp

CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artem/ta/lab2/nfa_dfa/nfa_dfa.cpp > CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.i

CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artem/ta/lab2/nfa_dfa/nfa_dfa.cpp -o CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/test/catch2.cpp.o" \
"CMakeFiles/main.dir/regex/regex.cpp.o" \
"CMakeFiles/main.dir/ast/ast.cpp.o" \
"CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/test/catch2.cpp.o
main: CMakeFiles/main.dir/regex/regex.cpp.o
main: CMakeFiles/main.dir/ast/ast.cpp.o
main: CMakeFiles/main.dir/nfa_dfa/nfa_dfa.cpp.o
main: CMakeFiles/main.dir/build.make
main: /usr/local/lib/libCatch2Main.a
main: /usr/local/lib/libCatch2.a
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/artem/ta/lab2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/artem/ta/lab2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/artem/ta/lab2 /home/artem/ta/lab2 /home/artem/ta/lab2/build /home/artem/ta/lab2/build /home/artem/ta/lab2/build/CMakeFiles/main.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/main.dir/depend

