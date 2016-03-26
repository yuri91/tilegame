#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.0)
project(tile_manager VERSION 0.1 LANGUAGES CXX)

set(LIB_NAME "tilemanager")
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

target_link_libraries(${LIB_NAME}
	sfml
	tmxparser
)

install(TARGETS ${LIB_NAME}
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

# This makes the project importable from the build directory
export(TARGETS ${LIB_NAME} FILE TileManagerConfig.cmake)
