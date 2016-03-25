#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.0)
project(tiles)

#more portable way??
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  add_library(sfml INTERFACE IMPORTED)
  set_property(TARGET sfml PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${SFML_INCLUDE_DIR})
  set_property(TARGET sfml PROPERTY INTERFACE_LINK_LIBRARIES ${SFML_LIBRARIES})
endif()

find_package(TmxParser REQUIRED)
if(TMXPARSER_FOUND)
  add_library(tmxparser INTERFACE IMPORTED)
  set_property(TARGET tmxparser PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${TMXPARSER_INCLUDE_DIR})
  set_property(TARGET tmxparser PROPERTY INTERFACE_LINK_LIBRARIES ${TMXPARSER_LIBRARY})
endif()

add_subdirectory(tile_manager)
add_subdirectory(test)

include(CPack)
