cmake_minimum_required(VERSION 3.10)
project(hector_math_py)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(hector_math REQUIRED)

include_directories(${hector_math_INCLUDE_DIRS})
ament_python_install_package(hector_math)

pybind11_add_module(impl src/hector_math.cpp)
install(TARGETS impl LIBRARY DESTINATION "${PYTHON_INSTALL_DIR}/${PROJECT_NAME}")

ament_package()
