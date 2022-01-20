cmake_minimum_required(VERSION 3.20)
project(MinecraftClone)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(third-party)

add_executable(${PROJECT_NAME} src/main.cpp src/Renderer/VertexArray.cpp src/Renderer/IndexBuffer.cpp src/Renderer/IndexBuffer.h src/Renderer/VertexBuffer.cpp src/Renderer/VertexBuffer.h src/Renderer/Texture.cpp src/Renderer/Texture.h src/Renderer/ShaderProgram.cpp src/Renderer/ShaderProgram.h src/Window.cpp src/Window.h src/Input.cpp src/Input.h src/EventSystem/EventSystem.cpp src/EventSystem/EventSystem.h src/EventSystem/GlobalEventSystem.h src/Camera.cpp src/Camera.h src/Renderer/TextureRectangle.h src/cube.cpp src/cube.h src/Utils/ReadFile.cpp src/Utils/ReadFile.h)

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(${PROJECT_NAME} copy_assets)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/precompiledheader.h)

target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} stb_image)