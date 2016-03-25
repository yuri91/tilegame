#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.0)
project(tile_manager VERSION 0.1 LANGUAGES CXX)

set(LIB_NAME "tile_manager")
include_directories("include/")
add_library(${LIB_NAME}
	src/tilemap.cpp
	src/tilelayer.cpp
	src/tileset.cpp
)

target_include_directories(${LIB_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
	PRIVATE src
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#more portable way??
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${LIB_NAME} ${SFML_LIBRARIES})
endif()

find_package(TmxParser REQUIRED)
if(TMXPARSER_FOUND)
  include_directories(${TMXPARSER_INCLUDE_DIR})
  target_link_libraries(${LIB_NAME} ${TMXPARSER_LIBRARY})
endif()


install(TARGETS ${LIB_NAME}
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

# This makes the project importable from the build directory
export(TARGETS ${LIB_NAME} FILE MyLibraryConfig.cmake)
