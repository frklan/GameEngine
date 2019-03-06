cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

project(thirdparty_lib)

file(GLOB IMGUI_SOURCES Imgui/*.cpp)
file(GLOB IMGUI-SFML_SOURCES Imgui-SFML/*.cpp)

add_library(${PROJECT_NAME} STATIC ${IMGUI_SOURCES} ${IMGUI-SFML_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
