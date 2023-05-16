# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adminpc/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adminpc/catkin_ws/src/build

# Utility rule file for depthai_ros_msgs_generate_messages_cpp.

# Include any custom commands dependencies for this target.
include sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp.dir/compiler_depend.make

# Include the progress variables for this target.
include sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp.dir/progress.make

sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/AutoFocusCtrl.h
sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/HandLandmark.h
sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/HandLandmarkArray.h
sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/SpatialDetection.h
sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/SpatialDetectionArray.h
sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/TriggerNamed.h
sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/NormalizedImageCrop.h

devel/include/depthai_ros_msgs/AutoFocusCtrl.h: /opt/ros/noetic/lib/gencpp/gen_cpp.py
devel/include/depthai_ros_msgs/AutoFocusCtrl.h: /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg/AutoFocusCtrl.msg
devel/include/depthai_ros_msgs/AutoFocusCtrl.h: /opt/ros/noetic/share/gencpp/msg.h.template
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/adminpc/catkin_ws/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating C++ code from depthai_ros_msgs/AutoFocusCtrl.msg"
	cd /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs && /home/adminpc/catkin_ws/src/build/catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/gencpp/cmake/../../../lib/gencpp/gen_cpp.py /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg/AutoFocusCtrl.msg -Idepthai_ros_msgs:/home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Ivision_msgs:/opt/ros/noetic/share/vision_msgs/cmake/../msg -p depthai_ros_msgs -o /home/adminpc/catkin_ws/src/build/devel/include/depthai_ros_msgs -e /opt/ros/noetic/share/gencpp/cmake/..

devel/include/depthai_ros_msgs/HandLandmark.h: /opt/ros/noetic/lib/gencpp/gen_cpp.py
devel/include/depthai_ros_msgs/HandLandmark.h: /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg/HandLandmark.msg
devel/include/depthai_ros_msgs/HandLandmark.h: /opt/ros/noetic/share/geometry_msgs/msg/Pose2D.msg
devel/include/depthai_ros_msgs/HandLandmark.h: /opt/ros/noetic/share/geometry_msgs/msg/Point.msg
devel/include/depthai_ros_msgs/HandLandmark.h: /opt/ros/noetic/share/gencpp/msg.h.template
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/adminpc/catkin_ws/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating C++ code from depthai_ros_msgs/HandLandmark.msg"
	cd /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs && /home/adminpc/catkin_ws/src/build/catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/gencpp/cmake/../../../lib/gencpp/gen_cpp.py /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg/HandLandmark.msg -Idepthai_ros_msgs:/home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Ivision_msgs:/opt/ros/noetic/share/vision_msgs/cmake/../msg -p depthai_ros_msgs -o /home/adminpc/catkin_ws/src/build/devel/include/depthai_ros_msgs -e /opt/ros/noetic/share/gencpp/cmake/..

devel/include/depthai_ros_msgs/HandLandmarkArray.h: /opt/ros/noetic/lib/gencpp/gen_cpp.py
devel/include/depthai_ros_msgs/HandLandmarkArray.h: /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg/HandLandmarkArray.msg
devel/include/depthai_ros_msgs/HandLandmarkArray.h: /opt/ros/noetic/share/std_msgs/msg/Header.msg
devel/include/depthai_ros_msgs/HandLandmarkArray.h: /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg/HandLandmark.msg
devel/include/depthai_ros_msgs/HandLandmarkArray.h: /opt/ros/noetic/share/geometry_msgs/msg/Pose2D.msg
devel/include/depthai_ros_msgs/HandLandmarkArray.h: /opt/ros/noetic/share/geometry_msgs/msg/Point.msg
devel/include/depthai_ros_msgs/HandLandmarkArray.h: /opt/ros/noetic/share/gencpp/msg.h.template
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/adminpc/catkin_ws/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating C++ code from depthai_ros_msgs/HandLandmarkArray.msg"
	cd /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs && /home/adminpc/catkin_ws/src/build/catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/gencpp/cmake/../../../lib/gencpp/gen_cpp.py /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg/HandLandmarkArray.msg -Idepthai_ros_msgs:/home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Ivision_msgs:/opt/ros/noetic/share/vision_msgs/cmake/../msg -p depthai_ros_msgs -o /home/adminpc/catkin_ws/src/build/devel/include/depthai_ros_msgs -e /opt/ros/noetic/share/gencpp/cmake/..

devel/include/depthai_ros_msgs/NormalizedImageCrop.h: /opt/ros/noetic/lib/gencpp/gen_cpp.py
devel/include/depthai_ros_msgs/NormalizedImageCrop.h: /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/srv/NormalizedImageCrop.srv
devel/include/depthai_ros_msgs/NormalizedImageCrop.h: /opt/ros/noetic/share/geometry_msgs/msg/Pose2D.msg
devel/include/depthai_ros_msgs/NormalizedImageCrop.h: /opt/ros/noetic/share/gencpp/msg.h.template
devel/include/depthai_ros_msgs/NormalizedImageCrop.h: /opt/ros/noetic/share/gencpp/srv.h.template
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/adminpc/catkin_ws/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Generating C++ code from depthai_ros_msgs/NormalizedImageCrop.srv"
	cd /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs && /home/adminpc/catkin_ws/src/build/catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/gencpp/cmake/../../../lib/gencpp/gen_cpp.py /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/srv/NormalizedImageCrop.srv -Idepthai_ros_msgs:/home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Ivision_msgs:/opt/ros/noetic/share/vision_msgs/cmake/../msg -p depthai_ros_msgs -o /home/adminpc/catkin_ws/src/build/devel/include/depthai_ros_msgs -e /opt/ros/noetic/share/gencpp/cmake/..

devel/include/depthai_ros_msgs/SpatialDetection.h: /opt/ros/noetic/lib/gencpp/gen_cpp.py
devel/include/depthai_ros_msgs/SpatialDetection.h: /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg/SpatialDetection.msg
devel/include/depthai_ros_msgs/SpatialDetection.h: /opt/ros/noetic/share/vision_msgs/msg/BoundingBox2D.msg
devel/include/depthai_ros_msgs/SpatialDetection.h: /opt/ros/noetic/share/geometry_msgs/msg/Pose2D.msg
devel/include/depthai_ros_msgs/SpatialDetection.h: /opt/ros/noetic/share/vision_msgs/msg/ObjectHypothesis.msg
devel/include/depthai_ros_msgs/SpatialDetection.h: /opt/ros/noetic/share/geometry_msgs/msg/Point.msg
devel/include/depthai_ros_msgs/SpatialDetection.h: /opt/ros/noetic/share/gencpp/msg.h.template
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/adminpc/catkin_ws/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Generating C++ code from depthai_ros_msgs/SpatialDetection.msg"
	cd /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs && /home/adminpc/catkin_ws/src/build/catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/gencpp/cmake/../../../lib/gencpp/gen_cpp.py /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg/SpatialDetection.msg -Idepthai_ros_msgs:/home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Ivision_msgs:/opt/ros/noetic/share/vision_msgs/cmake/../msg -p depthai_ros_msgs -o /home/adminpc/catkin_ws/src/build/devel/include/depthai_ros_msgs -e /opt/ros/noetic/share/gencpp/cmake/..

devel/include/depthai_ros_msgs/SpatialDetectionArray.h: /opt/ros/noetic/lib/gencpp/gen_cpp.py
devel/include/depthai_ros_msgs/SpatialDetectionArray.h: /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg/SpatialDetectionArray.msg
devel/include/depthai_ros_msgs/SpatialDetectionArray.h: /opt/ros/noetic/share/geometry_msgs/msg/Point.msg
devel/include/depthai_ros_msgs/SpatialDetectionArray.h: /opt/ros/noetic/share/vision_msgs/msg/ObjectHypothesis.msg
devel/include/depthai_ros_msgs/SpatialDetectionArray.h: /opt/ros/noetic/share/std_msgs/msg/Header.msg
devel/include/depthai_ros_msgs/SpatialDetectionArray.h: /opt/ros/noetic/share/geometry_msgs/msg/Pose2D.msg
devel/include/depthai_ros_msgs/SpatialDetectionArray.h: /opt/ros/noetic/share/vision_msgs/msg/BoundingBox2D.msg
devel/include/depthai_ros_msgs/SpatialDetectionArray.h: /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg/SpatialDetection.msg
devel/include/depthai_ros_msgs/SpatialDetectionArray.h: /opt/ros/noetic/share/gencpp/msg.h.template
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/adminpc/catkin_ws/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Generating C++ code from depthai_ros_msgs/SpatialDetectionArray.msg"
	cd /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs && /home/adminpc/catkin_ws/src/build/catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/gencpp/cmake/../../../lib/gencpp/gen_cpp.py /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg/SpatialDetectionArray.msg -Idepthai_ros_msgs:/home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Ivision_msgs:/opt/ros/noetic/share/vision_msgs/cmake/../msg -p depthai_ros_msgs -o /home/adminpc/catkin_ws/src/build/devel/include/depthai_ros_msgs -e /opt/ros/noetic/share/gencpp/cmake/..

devel/include/depthai_ros_msgs/TriggerNamed.h: /opt/ros/noetic/lib/gencpp/gen_cpp.py
devel/include/depthai_ros_msgs/TriggerNamed.h: /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/srv/TriggerNamed.srv
devel/include/depthai_ros_msgs/TriggerNamed.h: /opt/ros/noetic/share/gencpp/msg.h.template
devel/include/depthai_ros_msgs/TriggerNamed.h: /opt/ros/noetic/share/gencpp/srv.h.template
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/adminpc/catkin_ws/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Generating C++ code from depthai_ros_msgs/TriggerNamed.srv"
	cd /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs && /home/adminpc/catkin_ws/src/build/catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/gencpp/cmake/../../../lib/gencpp/gen_cpp.py /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/srv/TriggerNamed.srv -Idepthai_ros_msgs:/home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs/msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -Ivision_msgs:/opt/ros/noetic/share/vision_msgs/cmake/../msg -p depthai_ros_msgs -o /home/adminpc/catkin_ws/src/build/devel/include/depthai_ros_msgs -e /opt/ros/noetic/share/gencpp/cmake/..

depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/AutoFocusCtrl.h
depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/HandLandmark.h
depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/HandLandmarkArray.h
depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/NormalizedImageCrop.h
depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/SpatialDetection.h
depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/SpatialDetectionArray.h
depthai_ros_msgs_generate_messages_cpp: devel/include/depthai_ros_msgs/TriggerNamed.h
depthai_ros_msgs_generate_messages_cpp: sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp
depthai_ros_msgs_generate_messages_cpp: sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp.dir/build.make
.PHONY : depthai_ros_msgs_generate_messages_cpp

# Rule to build all files generated by this target.
sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp.dir/build: depthai_ros_msgs_generate_messages_cpp
.PHONY : sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp.dir/build

sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp.dir/clean:
	cd /home/adminpc/catkin_ws/src/build/sp_vision/depthai-ros/depthai_ros_msgs && $(CMAKE_COMMAND) -P CMakeFiles/depthai_ros_msgs_generate_messages_cpp.dir/cmake_clean.cmake
.PHONY : sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp.dir/clean

sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp.dir/depend:
	cd /home/adminpc/catkin_ws/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adminpc/catkin_ws/src /home/adminpc/catkin_ws/src/sp_vision/depthai-ros/depthai_ros_msgs /home/adminpc/catkin_ws/src/build /home/adminpc/catkin_ws/src/build/sp_vision/depthai-ros/depthai_ros_msgs /home/adminpc/catkin_ws/src/build/sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sp_vision/depthai-ros/depthai_ros_msgs/CMakeFiles/depthai_ros_msgs_generate_messages_cpp.dir/depend

