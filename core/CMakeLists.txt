cmake_minimum_required(VERSION 3.28)

set(CORE_PROJECT_NAME EngineCore)
set(CMAKE_CXX_STANDARD 20)

set(ENGINE_PUBLIC_INCLUDES 
	includes/core/Application.hpp
	includes/core/Event.hpp
	includes/core/Log.hpp
	includes/core/Camera.hpp
	includes/core/Input.hpp
)
set(ENGINE_PRIVATE_INCLUDES
	includes/core/Window.hpp
	includes/core/rendering/OpenGL/ShaderProgram.hpp
	includes/core/rendering/OpenGL/VertexBuffer.hpp
	includes/core/rendering/OpenGL/VertexArray.hpp
	includes/core/rendering/OpenGL/IndexBuffer.hpp
	includes/core/rendering/OpenGL/Renderer.hpp
	includes/core/modules/UIModule.hpp
)
set(ENGINE_PRIVATE_SOURCES
	src/core/Application.cpp
	src/core/Log.cpp
	src/core/Window.cpp
	src/core/Event.cpp
	src/core/Camera.cpp
	src/core/Input.cpp
	src/core/rendering/OpenGL/ShaderProgram.cpp
	src/core/rendering/OpenGL/VertexBuffer.cpp
	src/core/rendering/OpenGL/VertexArray.cpp
	src/core/rendering/OpenGL/IndexBuffer.cpp
	src/core/rendering/OpenGL/Renderer.cpp
	src/core/modules/UIModule.cpp
)

add_library(${CORE_PROJECT_NAME} STATIC 
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
	${ENGINE_PRIVATE_INCLUDES}
)
	
target_include_directories(${CORE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${CORE_PROJECT_NAME} PUBLIC includes/rendering/OpenGL)
target_include_directories(${CORE_PROJECT_NAME} PRIVATE src)
target_include_directories(${CORE_PROJECT_NAME} PRIVATE src/rendering/OpenGL)
target_compile_features(${CORE_PROJECT_NAME} PUBLIC cxx_std_20)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${CORE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${CORE_PROJECT_NAME} PRIVATE glad)

add_subdirectory(../external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${CORE_PROJECT_NAME} PRIVATE glm)


set(IMGUI_INCLUDES 
	../external/imgui/imgui.h
	../external/imgui/backends/imgui_impl_glfw.h
	../external/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_SOURCES 
	../external/imgui/imgui.cpp
	../external/imgui/backends/imgui_impl_glfw.cpp
	../external/imgui/backends/imgui_impl_opengl3.cpp
	../external/imgui/imgui_draw.cpp
	../external/imgui/imgui_tables.cpp
	../external/imgui/imgui_widgets.cpp
	../external/imgui/imgui_demo.cpp
)

add_library(imgui STATIC
	${IMGUI_INCLUDES}
	${IMGUI_SOURCES}
)

target_include_directories(imgui PUBLIC ../external)
target_include_directories(imgui PUBLIC ../external/imgui)

target_link_libraries(imgui PRIVATE glad)
target_link_libraries(imgui PRIVATE glfw)
target_link_libraries(imgui PRIVATE glm)

target_link_libraries(${CORE_PROJECT_NAME} PRIVATE imgui)