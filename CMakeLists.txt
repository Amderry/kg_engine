cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME Engine)
set(CMAKE_CXX_STANDARD 20)

project(${PROJECT_NAME})

add_subdirectory(core)
add_subdirectory(editor)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT EngineEditor)
