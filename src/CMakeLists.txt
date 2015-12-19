
add_definitions(-std=c++14)
set(CPP_PATH ".")


file(GLOB SRC_FILES
    "${CPP_PATH}/*.cpp"
    "${CPP_PATH}/buffer/*.cpp"
    "${CPP_PATH}/device/*.cpp"
    "${CPP_PATH}/display/*.cpp"
    "${CPP_PATH}/fft/*.cpp"
    "${CPP_PATH}/math/*.cpp"
    "${CPP_PATH}/process/*.cpp"
    "${CPP_PATH}/score/*.cpp"
    "${CPP_PATH}/view/*.cpp"
    "${CPP_PATH}/window/*.cpp"
)


file(GLOB INCLUDE_FILES
    "${CPP_PATH}/*.h"
    "${CPP_PATH}/buffer/*.h"
    "${CPP_PATH}/device/*.h"
    "${CPP_PATH}/display/*.h"
    "${CPP_PATH}/fft/*.h"
    "${CPP_PATH}/math/*.h"
    "${CPP_PATH}/process/*.h"
    "${CPP_PATH}/score/*.h"
    "${CPP_PATH}/view/*.h"
    "${CPP_PATH}/window/*.h"
)


add_library(
    ${LIBRARY_NAME}
    SHARED
    ${SRC_FILES}
    ${INCLUDE_FILES}
)


target_link_libraries (${LIBRARY_NAME} ${CMAKE_THREAD_LIBS_INIT} ${ALSA_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
