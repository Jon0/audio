cmake_minimum_required (VERSION 2.6)

project (Audio)

# TODO: generate errors when not found
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(ALSA REQUIRED)
find_package(Threads REQUIRED)

include_directories(${ALSA_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

# build main library
set(LIBRARY_NAME "audio")
add_subdirectory(src)
include_directories("${PROJECT_SOURCE_DIR}/src")


#build executable
add_subdirectory(bin)
