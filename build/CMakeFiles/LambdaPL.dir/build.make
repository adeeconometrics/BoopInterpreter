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
CMAKE_SOURCE_DIR = /mnt/c/Users/amianadave/documents/LambdaInterpreter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/amianadave/documents/LambdaInterpreter/build

# Include any dependencies generated for this target.
include CMakeFiles/LambdaPL.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LambdaPL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LambdaPL.dir/flags.make

CMakeFiles/LambdaPL.dir/src/ErrorHandler.cpp.o: CMakeFiles/LambdaPL.dir/flags.make
CMakeFiles/LambdaPL.dir/src/ErrorHandler.cpp.o: ../src/ErrorHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/amianadave/documents/LambdaInterpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LambdaPL.dir/src/ErrorHandler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LambdaPL.dir/src/ErrorHandler.cpp.o -c /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/ErrorHandler.cpp

CMakeFiles/LambdaPL.dir/src/ErrorHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LambdaPL.dir/src/ErrorHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/ErrorHandler.cpp > CMakeFiles/LambdaPL.dir/src/ErrorHandler.cpp.i

CMakeFiles/LambdaPL.dir/src/ErrorHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LambdaPL.dir/src/ErrorHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/ErrorHandler.cpp -o CMakeFiles/LambdaPL.dir/src/ErrorHandler.cpp.s

CMakeFiles/LambdaPL.dir/src/Expr.cpp.o: CMakeFiles/LambdaPL.dir/flags.make
CMakeFiles/LambdaPL.dir/src/Expr.cpp.o: ../src/Expr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/amianadave/documents/LambdaInterpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/LambdaPL.dir/src/Expr.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LambdaPL.dir/src/Expr.cpp.o -c /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Expr.cpp

CMakeFiles/LambdaPL.dir/src/Expr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LambdaPL.dir/src/Expr.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Expr.cpp > CMakeFiles/LambdaPL.dir/src/Expr.cpp.i

CMakeFiles/LambdaPL.dir/src/Expr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LambdaPL.dir/src/Expr.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Expr.cpp -o CMakeFiles/LambdaPL.dir/src/Expr.cpp.s

CMakeFiles/LambdaPL.dir/src/FileReader.cpp.o: CMakeFiles/LambdaPL.dir/flags.make
CMakeFiles/LambdaPL.dir/src/FileReader.cpp.o: ../src/FileReader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/amianadave/documents/LambdaInterpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/LambdaPL.dir/src/FileReader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LambdaPL.dir/src/FileReader.cpp.o -c /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/FileReader.cpp

CMakeFiles/LambdaPL.dir/src/FileReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LambdaPL.dir/src/FileReader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/FileReader.cpp > CMakeFiles/LambdaPL.dir/src/FileReader.cpp.i

CMakeFiles/LambdaPL.dir/src/FileReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LambdaPL.dir/src/FileReader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/FileReader.cpp -o CMakeFiles/LambdaPL.dir/src/FileReader.cpp.s

CMakeFiles/LambdaPL.dir/src/Main.cpp.o: CMakeFiles/LambdaPL.dir/flags.make
CMakeFiles/LambdaPL.dir/src/Main.cpp.o: ../src/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/amianadave/documents/LambdaInterpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/LambdaPL.dir/src/Main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LambdaPL.dir/src/Main.cpp.o -c /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Main.cpp

CMakeFiles/LambdaPL.dir/src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LambdaPL.dir/src/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Main.cpp > CMakeFiles/LambdaPL.dir/src/Main.cpp.i

CMakeFiles/LambdaPL.dir/src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LambdaPL.dir/src/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Main.cpp -o CMakeFiles/LambdaPL.dir/src/Main.cpp.s

CMakeFiles/LambdaPL.dir/src/Scanner.cpp.o: CMakeFiles/LambdaPL.dir/flags.make
CMakeFiles/LambdaPL.dir/src/Scanner.cpp.o: ../src/Scanner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/amianadave/documents/LambdaInterpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/LambdaPL.dir/src/Scanner.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LambdaPL.dir/src/Scanner.cpp.o -c /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Scanner.cpp

CMakeFiles/LambdaPL.dir/src/Scanner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LambdaPL.dir/src/Scanner.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Scanner.cpp > CMakeFiles/LambdaPL.dir/src/Scanner.cpp.i

CMakeFiles/LambdaPL.dir/src/Scanner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LambdaPL.dir/src/Scanner.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Scanner.cpp -o CMakeFiles/LambdaPL.dir/src/Scanner.cpp.s

CMakeFiles/LambdaPL.dir/src/Stmt.cpp.o: CMakeFiles/LambdaPL.dir/flags.make
CMakeFiles/LambdaPL.dir/src/Stmt.cpp.o: ../src/Stmt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/amianadave/documents/LambdaInterpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/LambdaPL.dir/src/Stmt.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LambdaPL.dir/src/Stmt.cpp.o -c /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Stmt.cpp

CMakeFiles/LambdaPL.dir/src/Stmt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LambdaPL.dir/src/Stmt.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Stmt.cpp > CMakeFiles/LambdaPL.dir/src/Stmt.cpp.i

CMakeFiles/LambdaPL.dir/src/Stmt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LambdaPL.dir/src/Stmt.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Stmt.cpp -o CMakeFiles/LambdaPL.dir/src/Stmt.cpp.s

CMakeFiles/LambdaPL.dir/src/Token.cpp.o: CMakeFiles/LambdaPL.dir/flags.make
CMakeFiles/LambdaPL.dir/src/Token.cpp.o: ../src/Token.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/amianadave/documents/LambdaInterpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/LambdaPL.dir/src/Token.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LambdaPL.dir/src/Token.cpp.o -c /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Token.cpp

CMakeFiles/LambdaPL.dir/src/Token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LambdaPL.dir/src/Token.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Token.cpp > CMakeFiles/LambdaPL.dir/src/Token.cpp.i

CMakeFiles/LambdaPL.dir/src/Token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LambdaPL.dir/src/Token.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/Token.cpp -o CMakeFiles/LambdaPL.dir/src/Token.cpp.s

CMakeFiles/LambdaPL.dir/src/TokenType.cpp.o: CMakeFiles/LambdaPL.dir/flags.make
CMakeFiles/LambdaPL.dir/src/TokenType.cpp.o: ../src/TokenType.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/amianadave/documents/LambdaInterpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/LambdaPL.dir/src/TokenType.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LambdaPL.dir/src/TokenType.cpp.o -c /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/TokenType.cpp

CMakeFiles/LambdaPL.dir/src/TokenType.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LambdaPL.dir/src/TokenType.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/TokenType.cpp > CMakeFiles/LambdaPL.dir/src/TokenType.cpp.i

CMakeFiles/LambdaPL.dir/src/TokenType.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LambdaPL.dir/src/TokenType.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/amianadave/documents/LambdaInterpreter/src/TokenType.cpp -o CMakeFiles/LambdaPL.dir/src/TokenType.cpp.s

# Object files for target LambdaPL
LambdaPL_OBJECTS = \
"CMakeFiles/LambdaPL.dir/src/ErrorHandler.cpp.o" \
"CMakeFiles/LambdaPL.dir/src/Expr.cpp.o" \
"CMakeFiles/LambdaPL.dir/src/FileReader.cpp.o" \
"CMakeFiles/LambdaPL.dir/src/Main.cpp.o" \
"CMakeFiles/LambdaPL.dir/src/Scanner.cpp.o" \
"CMakeFiles/LambdaPL.dir/src/Stmt.cpp.o" \
"CMakeFiles/LambdaPL.dir/src/Token.cpp.o" \
"CMakeFiles/LambdaPL.dir/src/TokenType.cpp.o"

# External object files for target LambdaPL
LambdaPL_EXTERNAL_OBJECTS =

LambdaPL: CMakeFiles/LambdaPL.dir/src/ErrorHandler.cpp.o
LambdaPL: CMakeFiles/LambdaPL.dir/src/Expr.cpp.o
LambdaPL: CMakeFiles/LambdaPL.dir/src/FileReader.cpp.o
LambdaPL: CMakeFiles/LambdaPL.dir/src/Main.cpp.o
LambdaPL: CMakeFiles/LambdaPL.dir/src/Scanner.cpp.o
LambdaPL: CMakeFiles/LambdaPL.dir/src/Stmt.cpp.o
LambdaPL: CMakeFiles/LambdaPL.dir/src/Token.cpp.o
LambdaPL: CMakeFiles/LambdaPL.dir/src/TokenType.cpp.o
LambdaPL: CMakeFiles/LambdaPL.dir/build.make
LambdaPL: CMakeFiles/LambdaPL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/amianadave/documents/LambdaInterpreter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable LambdaPL"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LambdaPL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LambdaPL.dir/build: LambdaPL

.PHONY : CMakeFiles/LambdaPL.dir/build

CMakeFiles/LambdaPL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LambdaPL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LambdaPL.dir/clean

CMakeFiles/LambdaPL.dir/depend:
	cd /mnt/c/Users/amianadave/documents/LambdaInterpreter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/amianadave/documents/LambdaInterpreter /mnt/c/Users/amianadave/documents/LambdaInterpreter /mnt/c/Users/amianadave/documents/LambdaInterpreter/build /mnt/c/Users/amianadave/documents/LambdaInterpreter/build /mnt/c/Users/amianadave/documents/LambdaInterpreter/build/CMakeFiles/LambdaPL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LambdaPL.dir/depend
