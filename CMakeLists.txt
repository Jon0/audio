cmake_minimum_required (VERSION 2.6)

project (Audio)

# TODO: generate errors when not found
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/")
find_package(ALSA REQUIRED)
find_package(Threads REQUIRED)

# rendering
find_package(Epoxy REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_package(Freetype REQUIRED)

# includes for dependencies
include_directories(
	${ALSA_INCLUDE_DIR}
	${EPOXY_INCLUDE_DIRS}
	${FREETYPE_INCLUDE_DIRS}
)

# build main library
set(LIBRARY_NAME "audio")
add_subdirectory(src)
include_directories("${PROJECT_SOURCE_DIR}/src")


#build executable
add_subdirectory(bin)

# write src path to binary dir
configure_file (
  "${CMAKE_MODULE_PATH}/src_path.in"
  "${PROJECT_BINARY_DIR}/src_path"
)