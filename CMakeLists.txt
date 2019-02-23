cmake_minimum_required(VERSION 3.1)

project(ge)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED audio graphics window system)
find_package(OpenGL REQUIRED OpenGL)

#Add files
set(SOURCES 
    src/Game/Scenes/Common/DebugView/debugview.cpp
    src/Game/Scenes/Game/cursor.cpp
    src/Game/Scenes/Game/gameoflife.cpp
    src/Game/Scenes/Game/gamescene.cpp
    src/Game/Scenes/Game/grid.cpp
    src/Game/Scenes/Game/gui.cpp
    src/Game/Scenes/Game/statusdisplay.cpp
    src/Game/Scenes/Intro/backgroundquad.cpp
    src/Game/Scenes/Intro/gui.cpp
    src/Game/Scenes/Intro/introscene.cpp
    src/Game/Scenes/Intro/sincurve.cpp
    src/Game/main.cpp
    src/GameEngine/GameEngine.cpp
    src/GameEngine/Scene.cpp
    src/lib/imgui/imgui.cpp
    src/lib/imgui/imgui_demo.cpp
    src/lib/imgui/imgui_draw.cpp
    src/lib/imgui/imgui_widgets.cpp
    src/lib/imgui-sfml/imgui-SFML.cpp
)

include_directories(AFTER src/lib src/lib/imgui-sfml src/lib/imgui src/lib/eventbus/src/eventbus/ src/GameEngine ${OPENGL_INCLUDE_DIR})

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#Define the executable
add_executable(
    ${PROJECT_NAME} 
    ${SOURCES} 
)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${OPENGL_LIBRARIES})