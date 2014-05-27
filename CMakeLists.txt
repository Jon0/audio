# cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER_ARG1=-std=c++11
cmake_minimum_required (VERSION 2.6)

project (Audio)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(ALSA REQUIRED)
find_package(Threads REQUIRED)

include_directories( ${ALSA_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )




#include_directories ("${PROJECT_BINARY_DIR}")


file(GLOB SRC_FILES
    "src/*.cpp"
    "src/buffer/*.cpp"
    "src/display/*.cpp"
    "src/fft/*.cpp"
    "src/math/*.cpp"
    "src/playback/*.cpp"
    "src/process/*.cpp"
    "src/view/*.cpp"
    "src/window/*.cpp"
)

add_definitions(-std=c++11)
add_executable (AudioMain ${SRC_FILES})
target_link_libraries (AudioMain ${CMAKE_THREAD_LIBS_INIT} ${ALSA_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
