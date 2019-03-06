cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

project(gameoflife)

file(GLOB_RECURSE GAMEOFLIFE_SOURCES *.cpp)

#add_library(${PROJECT_NAME} STATIC ${GAMEOFLIFE_SOURCES})
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

#Define the executables
add_executable(${PROJECT_NAME} ${GAMEOFLIFE_SOURCES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} gameengine_lib thirdparty_lib)

add_executable(${PROJECT_NAME}_app MACOSX_BUNDLE ${GAMEOFLIFE_SOURCES})
target_link_libraries(${PROJECT_NAME}_app ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} gameengine_lib thirdparty_lib)
set_target_properties(${PROJECT_NAME}_app PROPERTIES LINKER_LANGUAGE CXX)


file(COPY ${CMAKE_SOURCE_DIR}/src/GameOfLife/Resources  DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_app.app/Contents/ )
file(COPY ${CMAKE_SOURCE_DIR}/src/GameOfLife/Resources  DESTINATION ${CMAKE_BINARY_DIR}/ )