cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(PISTACHERestAPI VERSION 1.0.0 LANGUAGES CXX)

# ---------------------- Include guards --------------------------
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR
    "Please make a new directory (build directory) and run CMake from there."
  )
endif()
# ----------------------------------------------------------------

# --------------------------- Dependencies (CPM) --------------------------
include(cmake/CPM.cmake)
CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.4
)
CPMAddPackage(
  NAME Ccache.cmake
  GITHUB_REPOSITORY TheLartians/Ccache.cmake
  VERSION 1.2
)
CPMAddPackage("gh:fmtlib/fmt#8.1.0@8.1.0")
# -----------------------------------------------------------------------------

add_library(
  Router
  include/router.hpp
  source/router.cpp
  )

# ------------------------------   Controllers       ----------------------------------
add_library(
  UserController
  include/user/controller.hpp
  source/user/controller.cpp
  )

add_library(
  UserService
  include/user/service.hpp
  source/user/service.cpp
  )
# -----------------------------------------------------------------------------

# For every target include the directory "include/"
# target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(Router PUBLIC include/)
target_include_directories(UserController PUBLIC include/)
target_include_directories(UserService PUBLIC include/)

target_link_libraries(Router UserController UserService fmt)
target_link_libraries(UserService fmt)

add_executable(${PROJECT_NAME} source/main.cpp)
target_link_libraries(${PROJECT_NAME} 
  PRIVATE fmt
  PRIVATE pistache
  PRIVATE Router
  )
# -----------------------------------------------------------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
