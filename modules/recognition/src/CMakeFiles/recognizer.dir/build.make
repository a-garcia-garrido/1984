# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/tester/github/1984/modules/recognition/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tester/github/1984/modules/recognition/src

# Include any dependencies generated for this target.
include CMakeFiles/recognizer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/recognizer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/recognizer.dir/flags.make

CMakeFiles/recognizer.dir/recognizer.cpp.o: CMakeFiles/recognizer.dir/flags.make
CMakeFiles/recognizer.dir/recognizer.cpp.o: recognizer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tester/github/1984/modules/recognition/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/recognizer.dir/recognizer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/recognizer.dir/recognizer.cpp.o -c /home/tester/github/1984/modules/recognition/src/recognizer.cpp

CMakeFiles/recognizer.dir/recognizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/recognizer.dir/recognizer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tester/github/1984/modules/recognition/src/recognizer.cpp > CMakeFiles/recognizer.dir/recognizer.cpp.i

CMakeFiles/recognizer.dir/recognizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/recognizer.dir/recognizer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tester/github/1984/modules/recognition/src/recognizer.cpp -o CMakeFiles/recognizer.dir/recognizer.cpp.s

CMakeFiles/recognizer.dir/recognizer.cpp.o.requires:

.PHONY : CMakeFiles/recognizer.dir/recognizer.cpp.o.requires

CMakeFiles/recognizer.dir/recognizer.cpp.o.provides: CMakeFiles/recognizer.dir/recognizer.cpp.o.requires
	$(MAKE) -f CMakeFiles/recognizer.dir/build.make CMakeFiles/recognizer.dir/recognizer.cpp.o.provides.build
.PHONY : CMakeFiles/recognizer.dir/recognizer.cpp.o.provides

CMakeFiles/recognizer.dir/recognizer.cpp.o.provides.build: CMakeFiles/recognizer.dir/recognizer.cpp.o


# Object files for target recognizer
recognizer_OBJECTS = \
"CMakeFiles/recognizer.dir/recognizer.cpp.o"

# External object files for target recognizer
recognizer_EXTERNAL_OBJECTS =

recognizer: CMakeFiles/recognizer.dir/recognizer.cpp.o
recognizer: CMakeFiles/recognizer.dir/build.make
recognizer: /usr/local/lib/libopencv_ml.so.3.2.0
recognizer: /usr/local/lib/libopencv_objdetect.so.3.2.0
recognizer: /usr/local/lib/libopencv_shape.so.3.2.0
recognizer: /usr/local/lib/libopencv_stitching.so.3.2.0
recognizer: /usr/local/lib/libopencv_superres.so.3.2.0
recognizer: /usr/local/lib/libopencv_videostab.so.3.2.0
recognizer: /usr/local/lib/libopencv_calib3d.so.3.2.0
recognizer: /usr/local/lib/libopencv_features2d.so.3.2.0
recognizer: /usr/local/lib/libopencv_flann.so.3.2.0
recognizer: /usr/local/lib/libopencv_highgui.so.3.2.0
recognizer: /usr/local/lib/libopencv_photo.so.3.2.0
recognizer: /usr/local/lib/libopencv_video.so.3.2.0
recognizer: /usr/local/lib/libopencv_videoio.so.3.2.0
recognizer: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
recognizer: /usr/local/lib/libopencv_imgproc.so.3.2.0
recognizer: /usr/local/lib/libopencv_core.so.3.2.0
recognizer: CMakeFiles/recognizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tester/github/1984/modules/recognition/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable recognizer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/recognizer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/recognizer.dir/build: recognizer

.PHONY : CMakeFiles/recognizer.dir/build

CMakeFiles/recognizer.dir/requires: CMakeFiles/recognizer.dir/recognizer.cpp.o.requires

.PHONY : CMakeFiles/recognizer.dir/requires

CMakeFiles/recognizer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/recognizer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/recognizer.dir/clean

CMakeFiles/recognizer.dir/depend:
	cd /home/tester/github/1984/modules/recognition/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tester/github/1984/modules/recognition/src /home/tester/github/1984/modules/recognition/src /home/tester/github/1984/modules/recognition/src /home/tester/github/1984/modules/recognition/src /home/tester/github/1984/modules/recognition/src/CMakeFiles/recognizer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/recognizer.dir/depend

