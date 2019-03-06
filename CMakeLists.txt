cmake_minimum_required(VERSION 3.10)

gitproject(GameEngine)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML REQUIRED audio graphics window system)
find_package(OpenGL REQUIRED OpenGL)

find_package(Boost 1.67 REQUIRED COMPONENTS system date_time filesystem iostreams)
include_directories(${Boost_INCLUDE_DIRS})

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "-Weverything -Wno-weak-vtables -Wno-padded -Wno-conversion -Wno-zero-as-null-pointer-constant \
    -Wno-old-style-cast -Wno-double-promotion -Wno-global-constructors -Wno-switch-enum -Wno-cast-qual -Wno-shadow \
    -Wno-cast-qual -Wno-c++98-compat -Wno-c++98-compat-pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(AFTER src/lib src/lib/imgui-sfml src/lib/imgui src/lib/eventbus/src/eventbus/ src/GameEngine ${OPENGL_INCLUDE_DIR} ${SFML_INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src/GameEngine)
add_subdirectory(src/lib)
add_subdirectory(src/Game)