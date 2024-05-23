cmake_minimum_required(VERSION 3.10)
project(hector_math_ros2 VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake QUIET)
if (NOT ament_cmake_FOUND)
  message(STATUS "ament_cmake not found. Not building package.")
  return()
endif()

find_package(hector_math REQUIRED)
find_package(urdf REQUIRED)

###########
## Build ##
###########


add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
ament_target_dependencies(${PROJECT_NAME} INTERFACE hector_math urdf)
target_link_libraries(${PROJECT_NAME} INTERFACE hector_math::hector_math urdf::urdf)

find_package(benchmark QUIET)
if (${benchmark_FOUND})
  add_executable(benchmark_robot_model benchmark/robot_model.cpp)
  target_link_libraries(benchmark_robot_model PUBLIC ${PROJECT_NAME} benchmark benchmark_main pthread)
endif()

#############
## Install ##
#############

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets)
install(EXPORT ${PROJECT_NAME}-targets
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION lib/cmake/${PROJECT_NAME}
)

install(DIRECTORY include/ DESTINATION include)

#############
## Testing ##
#############
# TODO
# if (CATKIN_ENABLE_TESTING)
#   find_package(roscpp REQUIRED)
#   find_package(rostest REQUIRED)
#   find_package(roslib REQUIRED) # Provides ros::package
#   set(TEST_LIBRARIES ${PROJECT_NAME} ${catkin_LIBRARIES} ${roscpp_LIBRARIES} ${roslib_LIBRARIES})

#   include_directories(
#     ${catkin_INCLUDE_DIRS}
#     ${EIGEN3_INCLUDE_DIRS}
#     ${roscpp_INCLUDE_DIRS}
#     ${roslib_INCLUDE_DIRS}
#     ${rostest_INCLUDE_DIRS}
#   )
#   ## Add gtest based cpp test target and link libraries
#   catkin_add_gtest(test_joint_state_subscriber test/test_joint_state_subscriber.cpp)
#   target_link_libraries(test_joint_state_subscriber ${TEST_LIBRARIES})
# endif ()

# # to run: catkin build --this --no-deps -DENABLE_COVERAGE_TESTING=ON -DCMAKE_BUILD_TYPE=Debug -v --catkin-make-args hector_math_coverage
# # Path to results overview will be printed in the build process
# # Big thanks to the moveit people from whose docs I've obtained the information on how to get the coverage
# if (CATKIN_ENABLE_TESTING AND ENABLE_COVERAGE_TESTING)
#   find_package(code_coverage REQUIRED)   # catkin package ros-*-code-coverage
#   include(CodeCoverage)
#   APPEND_COVERAGE_COMPILER_FLAGS()
#   set(COVERAGE_EXCLUDES "*/${PROJECT_NAME}/test*" "*/build/*")
#   add_code_coverage(NAME ${PROJECT_NAME}_coverage)
# endif ()

ament_export_targets(${PROJECT_NAME}-targets)
ament_export_dependencies(hector_math urdf)
ament_export_include_directories(include)
ament_package()
