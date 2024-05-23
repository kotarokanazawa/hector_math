cmake_minimum_required(VERSION 3.10)
project(hector_math VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(ament_cmake QUIET)
find_package(catkin QUIET)

if (catkin_FOUND)
  catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    DEPENDS Eigen3
  )
endif()

###########
## Build ##
###########

include_directories(
  include
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(${PROJECT_NAME} INTERFACE Eigen3::Eigen)


find_package(benchmark QUIET)
if (${benchmark_FOUND})
  message(STATUS "benchmark found. Building benchmarks.")
  # Iterator benchmark
  add_executable(benchmark_iterators benchmark/iterators.cpp)
  find_package(grid_map_core QUIET)
  if (${grid_map_core_FOUND})
    add_definitions(-DBENCHMARK_ENABLE_GRIDMAP)
    include_directories(${grid_map_core_INCLUDE_DIRS})
    target_link_libraries(benchmark_iterators ${grid_map_core_LIBRARIES})
  endif()
  target_link_libraries(benchmark_iterators ${PROJECT_NAME} ${catkin_LIBRARIES} benchmark benchmark_main pthread)

  add_executable(benchmark_caches benchmark/caches.cpp)
  target_link_libraries(benchmark_caches ${PROJECT_NAME} benchmark benchmark_main pthread)

  add_executable(quaternion_binning_modes benchmark/quaternion_binning_modes.cpp)
  target_link_libraries(quaternion_binning_modes ${PROJECT_NAME} benchmark benchmark_main pthread)

  add_executable(show_iterators scripts/show_iterators.cpp)
  target_link_libraries(show_iterators ${PROJECT_NAME})
else()
  message(WARN benchmark library not found. Not building benchmarks.)
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

if (BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif (BUILD_TESTING)

# to run: catkin build --this --no-deps -DENABLE_COVERAGE_TESTING=ON -DCMAKE_BUILD_TYPE=Debug -v --catkin-make-args hector_math_coverage
# Path to results overview will be printed in the build process
# Big thanks to the moveit people from whose docs I've obtained the information on how to get the coverage
# if (CATKIN_ENABLE_TESTING AND ENABLE_COVERAGE_TESTING)
#   find_package(code_coverage REQUIRED)   # catkin package ros-*-code-coverage
#   include(CodeCoverage)
#   APPEND_COVERAGE_COMPILER_FLAGS()
#   set(COVERAGE_EXCLUDES "*/${PROJECT_NAME}/test*" "*/build/*")
#   add_code_coverage(NAME ${PROJECT_NAME}_coverage)
# endif ()

if (ament_cmake_FOUND)
  ament_export_targets(${PROJECT_NAME}-targets)
  ament_export_dependencies(Eigen3)
  ament_export_include_directories(include)
  ament_package()
endif()
