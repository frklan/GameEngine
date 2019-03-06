cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

project(gameengine_lib)

file(GLOB_RECURSE GAMEENGINE_SOURCES *.cpp)

add_library(${PROJECT_NAME} STATIC ${GAMEENGINE_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
