add_definitions(-std=c++14)

# executable files
file(GLOB MAIN_FILES
	"*.cpp"
)

set(EXECUTABLE_NAME "play")
add_executable(${EXECUTABLE_NAME} ${MAIN_FILES})
target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_NAME})
