cmake_minimum_required(VERSION 3.20)
project(MinecraftClone)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(third-party)

add_executable(${PROJECT_NAME} src/window/window.h src/window/active_window.cpp src/window/active_window.h src/input.h src/editor_camera.h src/main.cpp src/renderer/ShaderProgram.h src/Utils/ReadFile.cpp src/Utils/ReadFile.h src/renderer/renderer.h src/renderer/mesh.h src/renderer/model.h src/renderer/primitives.h)

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(${PROJECT_NAME} copy_assets)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/precompiledheader.h)

target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} stb_image)