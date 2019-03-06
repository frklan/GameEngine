cmake_minimum_required(VERSION 3.10)

project(ge)
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

# main.cpp is our only file not included in a lib 
set(SOURCES src/Game/main.cpp)

include_directories(AFTER src/lib src/lib/imgui-sfml src/lib/imgui src/lib/eventbus/src/eventbus/ src/GameEngine ${OPENGL_INCLUDE_DIR} ${SFML_INCLUDE_DIR})

add_subdirectory(src/GameEngine)
add_subdirectory(src/Game)
add_subdirectory(src/lib)

#Define the executables
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} gameengine_lib gameoflife_lib thirdparty_lib)

add_executable(${PROJECT_NAME}_app MACOSX_BUNDLE ${SOURCES})
target_link_libraries(${PROJECT_NAME}_app ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} gameengine_lib gameoflife_lib thirdparty_lib)
set_target_properties(${PROJECT_NAME}_app PROPERTIES LINKER_LANGUAGE CXX)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/Game/Resources  DESTINATION ${PROJECT_NAME}_app.app/Contents/src/Game/ )
