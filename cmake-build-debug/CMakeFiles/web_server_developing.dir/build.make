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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/web_server_developing.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/web_server_developing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/web_server_developing.dir/flags.make

CMakeFiles/web_server_developing.dir/src/main.cpp.o: CMakeFiles/web_server_developing.dir/flags.make
CMakeFiles/web_server_developing.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/web_server_developing.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server_developing.dir/src/main.cpp.o -c /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/main.cpp

CMakeFiles/web_server_developing.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server_developing.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/main.cpp > CMakeFiles/web_server_developing.dir/src/main.cpp.i

CMakeFiles/web_server_developing.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server_developing.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/main.cpp -o CMakeFiles/web_server_developing.dir/src/main.cpp.s

CMakeFiles/web_server_developing.dir/src/Util.cpp.o: CMakeFiles/web_server_developing.dir/flags.make
CMakeFiles/web_server_developing.dir/src/Util.cpp.o: ../src/Util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/web_server_developing.dir/src/Util.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server_developing.dir/src/Util.cpp.o -c /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/Util.cpp

CMakeFiles/web_server_developing.dir/src/Util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server_developing.dir/src/Util.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/Util.cpp > CMakeFiles/web_server_developing.dir/src/Util.cpp.i

CMakeFiles/web_server_developing.dir/src/Util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server_developing.dir/src/Util.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/Util.cpp -o CMakeFiles/web_server_developing.dir/src/Util.cpp.s

CMakeFiles/web_server_developing.dir/src/Socket.cpp.o: CMakeFiles/web_server_developing.dir/flags.make
CMakeFiles/web_server_developing.dir/src/Socket.cpp.o: ../src/Socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/web_server_developing.dir/src/Socket.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server_developing.dir/src/Socket.cpp.o -c /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/Socket.cpp

CMakeFiles/web_server_developing.dir/src/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server_developing.dir/src/Socket.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/Socket.cpp > CMakeFiles/web_server_developing.dir/src/Socket.cpp.i

CMakeFiles/web_server_developing.dir/src/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server_developing.dir/src/Socket.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/Socket.cpp -o CMakeFiles/web_server_developing.dir/src/Socket.cpp.s

CMakeFiles/web_server_developing.dir/src/Timer.cpp.o: CMakeFiles/web_server_developing.dir/flags.make
CMakeFiles/web_server_developing.dir/src/Timer.cpp.o: ../src/Timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/web_server_developing.dir/src/Timer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server_developing.dir/src/Timer.cpp.o -c /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/Timer.cpp

CMakeFiles/web_server_developing.dir/src/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server_developing.dir/src/Timer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/Timer.cpp > CMakeFiles/web_server_developing.dir/src/Timer.cpp.i

CMakeFiles/web_server_developing.dir/src/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server_developing.dir/src/Timer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/Timer.cpp -o CMakeFiles/web_server_developing.dir/src/Timer.cpp.s

CMakeFiles/web_server_developing.dir/src/Epoll.cpp.o: CMakeFiles/web_server_developing.dir/flags.make
CMakeFiles/web_server_developing.dir/src/Epoll.cpp.o: ../src/Epoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/web_server_developing.dir/src/Epoll.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server_developing.dir/src/Epoll.cpp.o -c /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/Epoll.cpp

CMakeFiles/web_server_developing.dir/src/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server_developing.dir/src/Epoll.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/Epoll.cpp > CMakeFiles/web_server_developing.dir/src/Epoll.cpp.i

CMakeFiles/web_server_developing.dir/src/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server_developing.dir/src/Epoll.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/Epoll.cpp -o CMakeFiles/web_server_developing.dir/src/Epoll.cpp.s

CMakeFiles/web_server_developing.dir/src/ThreadPool.cpp.o: CMakeFiles/web_server_developing.dir/flags.make
CMakeFiles/web_server_developing.dir/src/ThreadPool.cpp.o: ../src/ThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/web_server_developing.dir/src/ThreadPool.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server_developing.dir/src/ThreadPool.cpp.o -c /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/ThreadPool.cpp

CMakeFiles/web_server_developing.dir/src/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server_developing.dir/src/ThreadPool.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/ThreadPool.cpp > CMakeFiles/web_server_developing.dir/src/ThreadPool.cpp.i

CMakeFiles/web_server_developing.dir/src/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server_developing.dir/src/ThreadPool.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/ThreadPool.cpp -o CMakeFiles/web_server_developing.dir/src/ThreadPool.cpp.s

CMakeFiles/web_server_developing.dir/src/http/HttpData.cpp.o: CMakeFiles/web_server_developing.dir/flags.make
CMakeFiles/web_server_developing.dir/src/http/HttpData.cpp.o: ../src/http/HttpData.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/web_server_developing.dir/src/http/HttpData.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server_developing.dir/src/http/HttpData.cpp.o -c /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/HttpData.cpp

CMakeFiles/web_server_developing.dir/src/http/HttpData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server_developing.dir/src/http/HttpData.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/HttpData.cpp > CMakeFiles/web_server_developing.dir/src/http/HttpData.cpp.i

CMakeFiles/web_server_developing.dir/src/http/HttpData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server_developing.dir/src/http/HttpData.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/HttpData.cpp -o CMakeFiles/web_server_developing.dir/src/http/HttpData.cpp.s

CMakeFiles/web_server_developing.dir/src/http/HttpParse.cpp.o: CMakeFiles/web_server_developing.dir/flags.make
CMakeFiles/web_server_developing.dir/src/http/HttpParse.cpp.o: ../src/http/HttpParse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/web_server_developing.dir/src/http/HttpParse.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server_developing.dir/src/http/HttpParse.cpp.o -c /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/HttpParse.cpp

CMakeFiles/web_server_developing.dir/src/http/HttpParse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server_developing.dir/src/http/HttpParse.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/HttpParse.cpp > CMakeFiles/web_server_developing.dir/src/http/HttpParse.cpp.i

CMakeFiles/web_server_developing.dir/src/http/HttpParse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server_developing.dir/src/http/HttpParse.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/HttpParse.cpp -o CMakeFiles/web_server_developing.dir/src/http/HttpParse.cpp.s

CMakeFiles/web_server_developing.dir/src/http/HttpRequest.cpp.o: CMakeFiles/web_server_developing.dir/flags.make
CMakeFiles/web_server_developing.dir/src/http/HttpRequest.cpp.o: ../src/http/HttpRequest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/web_server_developing.dir/src/http/HttpRequest.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server_developing.dir/src/http/HttpRequest.cpp.o -c /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/HttpRequest.cpp

CMakeFiles/web_server_developing.dir/src/http/HttpRequest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server_developing.dir/src/http/HttpRequest.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/HttpRequest.cpp > CMakeFiles/web_server_developing.dir/src/http/HttpRequest.cpp.i

CMakeFiles/web_server_developing.dir/src/http/HttpRequest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server_developing.dir/src/http/HttpRequest.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/HttpRequest.cpp -o CMakeFiles/web_server_developing.dir/src/http/HttpRequest.cpp.s

CMakeFiles/web_server_developing.dir/src/http/HttpResponse.cpp.o: CMakeFiles/web_server_developing.dir/flags.make
CMakeFiles/web_server_developing.dir/src/http/HttpResponse.cpp.o: ../src/http/HttpResponse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/web_server_developing.dir/src/http/HttpResponse.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server_developing.dir/src/http/HttpResponse.cpp.o -c /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/HttpResponse.cpp

CMakeFiles/web_server_developing.dir/src/http/HttpResponse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server_developing.dir/src/http/HttpResponse.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/HttpResponse.cpp > CMakeFiles/web_server_developing.dir/src/http/HttpResponse.cpp.i

CMakeFiles/web_server_developing.dir/src/http/HttpResponse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server_developing.dir/src/http/HttpResponse.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/HttpResponse.cpp -o CMakeFiles/web_server_developing.dir/src/http/HttpResponse.cpp.s

CMakeFiles/web_server_developing.dir/src/http/Server.cpp.o: CMakeFiles/web_server_developing.dir/flags.make
CMakeFiles/web_server_developing.dir/src/http/Server.cpp.o: ../src/http/Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/web_server_developing.dir/src/http/Server.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server_developing.dir/src/http/Server.cpp.o -c /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/Server.cpp

CMakeFiles/web_server_developing.dir/src/http/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server_developing.dir/src/http/Server.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/Server.cpp > CMakeFiles/web_server_developing.dir/src/http/Server.cpp.i

CMakeFiles/web_server_developing.dir/src/http/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server_developing.dir/src/http/Server.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/src/http/Server.cpp -o CMakeFiles/web_server_developing.dir/src/http/Server.cpp.s

# Object files for target web_server_developing
web_server_developing_OBJECTS = \
"CMakeFiles/web_server_developing.dir/src/main.cpp.o" \
"CMakeFiles/web_server_developing.dir/src/Util.cpp.o" \
"CMakeFiles/web_server_developing.dir/src/Socket.cpp.o" \
"CMakeFiles/web_server_developing.dir/src/Timer.cpp.o" \
"CMakeFiles/web_server_developing.dir/src/Epoll.cpp.o" \
"CMakeFiles/web_server_developing.dir/src/ThreadPool.cpp.o" \
"CMakeFiles/web_server_developing.dir/src/http/HttpData.cpp.o" \
"CMakeFiles/web_server_developing.dir/src/http/HttpParse.cpp.o" \
"CMakeFiles/web_server_developing.dir/src/http/HttpRequest.cpp.o" \
"CMakeFiles/web_server_developing.dir/src/http/HttpResponse.cpp.o" \
"CMakeFiles/web_server_developing.dir/src/http/Server.cpp.o"

# External object files for target web_server_developing
web_server_developing_EXTERNAL_OBJECTS =

web_server_developing: CMakeFiles/web_server_developing.dir/src/main.cpp.o
web_server_developing: CMakeFiles/web_server_developing.dir/src/Util.cpp.o
web_server_developing: CMakeFiles/web_server_developing.dir/src/Socket.cpp.o
web_server_developing: CMakeFiles/web_server_developing.dir/src/Timer.cpp.o
web_server_developing: CMakeFiles/web_server_developing.dir/src/Epoll.cpp.o
web_server_developing: CMakeFiles/web_server_developing.dir/src/ThreadPool.cpp.o
web_server_developing: CMakeFiles/web_server_developing.dir/src/http/HttpData.cpp.o
web_server_developing: CMakeFiles/web_server_developing.dir/src/http/HttpParse.cpp.o
web_server_developing: CMakeFiles/web_server_developing.dir/src/http/HttpRequest.cpp.o
web_server_developing: CMakeFiles/web_server_developing.dir/src/http/HttpResponse.cpp.o
web_server_developing: CMakeFiles/web_server_developing.dir/src/http/Server.cpp.o
web_server_developing: CMakeFiles/web_server_developing.dir/build.make
web_server_developing: CMakeFiles/web_server_developing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable web_server_developing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/web_server_developing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/web_server_developing.dir/build: web_server_developing

.PHONY : CMakeFiles/web_server_developing.dir/build

CMakeFiles/web_server_developing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/web_server_developing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/web_server_developing.dir/clean

CMakeFiles/web_server_developing.dir/depend:
	cd /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug /Users/twintails/Desktop/乱七八糟练习一堆/web_server_developing/cmake-build-debug/CMakeFiles/web_server_developing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/web_server_developing.dir/depend
