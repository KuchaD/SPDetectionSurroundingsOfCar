# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /snap/clion/61/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/61/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DNN.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DNN.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DNN.dir/flags.make

CMakeFiles/DNN.dir/main.cpp.o: CMakeFiles/DNN.dir/flags.make
CMakeFiles/DNN.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DNN.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DNN.dir/main.cpp.o -c /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/main.cpp

CMakeFiles/DNN.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DNN.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/main.cpp > CMakeFiles/DNN.dir/main.cpp.i

CMakeFiles/DNN.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DNN.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/main.cpp -o CMakeFiles/DNN.dir/main.cpp.s

CMakeFiles/DNN.dir/src/Network.cpp.o: CMakeFiles/DNN.dir/flags.make
CMakeFiles/DNN.dir/src/Network.cpp.o: ../src/Network.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DNN.dir/src/Network.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DNN.dir/src/Network.cpp.o -c /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/src/Network.cpp

CMakeFiles/DNN.dir/src/Network.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DNN.dir/src/Network.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/src/Network.cpp > CMakeFiles/DNN.dir/src/Network.cpp.i

CMakeFiles/DNN.dir/src/Network.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DNN.dir/src/Network.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/src/Network.cpp -o CMakeFiles/DNN.dir/src/Network.cpp.s

CMakeFiles/DNN.dir/utils/Utils.cpp.o: CMakeFiles/DNN.dir/flags.make
CMakeFiles/DNN.dir/utils/Utils.cpp.o: ../utils/Utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/DNN.dir/utils/Utils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DNN.dir/utils/Utils.cpp.o -c /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/utils/Utils.cpp

CMakeFiles/DNN.dir/utils/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DNN.dir/utils/Utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/utils/Utils.cpp > CMakeFiles/DNN.dir/utils/Utils.cpp.i

CMakeFiles/DNN.dir/utils/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DNN.dir/utils/Utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/utils/Utils.cpp -o CMakeFiles/DNN.dir/utils/Utils.cpp.s

# Object files for target DNN
DNN_OBJECTS = \
"CMakeFiles/DNN.dir/main.cpp.o" \
"CMakeFiles/DNN.dir/src/Network.cpp.o" \
"CMakeFiles/DNN.dir/utils/Utils.cpp.o"

# External object files for target DNN
DNN_EXTERNAL_OBJECTS =

DNN: CMakeFiles/DNN.dir/main.cpp.o
DNN: CMakeFiles/DNN.dir/src/Network.cpp.o
DNN: CMakeFiles/DNN.dir/utils/Utils.cpp.o
DNN: CMakeFiles/DNN.dir/build.make
DNN: dlib_build/libdlib.a
DNN: /usr/lib/x86_64-linux-gnu/libnsl.so
DNN: /usr/lib/x86_64-linux-gnu/libSM.so
DNN: /usr/lib/x86_64-linux-gnu/libICE.so
DNN: /usr/lib/x86_64-linux-gnu/libX11.so
DNN: /usr/lib/x86_64-linux-gnu/libXext.so
DNN: /usr/lib/x86_64-linux-gnu/libpng.so
DNN: /usr/lib/x86_64-linux-gnu/libz.so
DNN: /usr/lib/x86_64-linux-gnu/libjpeg.so
DNN: /usr/lib/x86_64-linux-gnu/libcblas.so
DNN: /usr/lib/x86_64-linux-gnu/liblapack.so
DNN: /usr/lib/x86_64-linux-gnu/libsqlite3.so
DNN: CMakeFiles/DNN.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable DNN"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DNN.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DNN.dir/build: DNN

.PHONY : CMakeFiles/DNN.dir/build

CMakeFiles/DNN.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DNN.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DNN.dir/clean

CMakeFiles/DNN.dir/depend:
	cd /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/cmake-build-debug /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/cmake-build-debug /home/daveliinux/GIT/SPDetectionSurroundingsOfCar/Source/PROJEKT/cmake-build-debug/CMakeFiles/DNN.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DNN.dir/depend
