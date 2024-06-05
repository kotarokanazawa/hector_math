cmake_minimum_required(VERSION 3.8)
project(hector_math_py)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


find_package(pybind11 REQUIRED)
find_package(ament_cmake REQUIRED)
#find_package(ament_cmake_python REQUIRED)
find_package(hector_math REQUIRED)

include_directories(${hector_math_INCLUDE_DIRS})
ament_python_install_package(hector_math)

pybind11_add_module(module src/hector_math.cpp)
install(TARGETS module LIBRARY DESTINATION "${PYTHON_INSTALL_DIR}/${PROJECT_NAME}")


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
