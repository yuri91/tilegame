#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)
project(tiletest)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#more portable way??
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)


# Define sources and executable
set(EXECUTABLE_NAME "tiletest")
include_directories("src/")
add_executable(${EXECUTABLE_NAME} src/main.cpp src/tilemap.cpp src/tilelayer.cpp src/tileset.cpp)


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

find_package(TmxParser REQUIRED)
if(TMXPARSER_FOUND)
  include_directories(${TMXPARSER_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${TMXPARSER_LIBRARY})
endif()


install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets/ DESTINATION share/${CMAKE_PROJECT_NAME})

include(CPack)
