#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.0)
project(tiletest)


# Define sources and executable
set(EXECUTABLE_NAME "tiletest")
include_directories("src/")
add_executable(${EXECUTABLE_NAME}
	src/main.cpp
)

target_link_libraries(${EXECUTABLE_NAME}
    tilemanager
    sfml
)

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets/ DESTINATION share/${CMAKE_PROJECT_NAME})

include(CPack)
