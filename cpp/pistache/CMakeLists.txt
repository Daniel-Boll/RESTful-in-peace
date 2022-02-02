cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(PISTACHERestAPI VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(Threads REQUIRED)
add_compile_options(-DELPP_THREAD_SAFE)

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
CPMAddPackage(
  NAME nlohmann_json
  VERSION 3.10.5
  GITHUB_REPOSITORY nlohmann/json
  OPTIONS 
    "JSON_BuildTests OFF"
)
add_library(
  Pistache
  SHARED
  IMPORTED
  )
set_target_properties(Pistache PROPERTIES 
  IMPORTED_LOCATION "/usr/local/lib/libpistache.so"
  INTERFACE_INCLUDE_DIRECTORIES "/usr/local/include/pistache"
  )
# -----------------------------------------------------------------------------

# ------------------------------   Router       ----------------------------------
add_library(
  Router
  include/router.hpp
  source/router.cpp
  )
# --------------------------------------------------------------------------------

# ------------------------------   MCS (Model Controller Service)  --------------------
add_library(
  UserModel
  INTERFACE
  include/user/model.hpp
  )

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
# -------------------------------------------------------------------------------------

# ------------------------------   Utils       ----------------------------------
add_library(
  Utils
  include/utils/utils.hpp
  source/utils/utils.cpp
  )
# -------------------------------------------------------------------------------


# For every target include the directory "include/"
# target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(Router PUBLIC include/)
target_include_directories(UserController PUBLIC include/)
target_include_directories(UserService PUBLIC include/)
target_include_directories(Utils PUBLIC include/)

target_link_libraries(Router 
  PRIVATE UserController 
  PRIVATE UserService 
  PRIVATE fmt
  PRIVATE Pistache
  )
target_link_libraries(UserController 
  PRIVATE fmt 
  PRIVATE nlohmann_json
  PRIVATE Pistache
  PRIVATE Utils
  PRIVATE Threads::Threads
  )
target_link_libraries(UserService 
  PRIVATE fmt 
  PRIVATE nlohmann_json
  PRIVATE Pistache
  PRIVATE Utils
  )

add_executable(${PROJECT_NAME} source/main.cpp)
target_link_libraries(${PROJECT_NAME} 
  PRIVATE fmt
  PRIVATE Pistache
  PRIVATE Router
  )
# -----------------------------------------------------------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
