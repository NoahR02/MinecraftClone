cmake_minimum_required(VERSION 3.15)
project(MinecraftClone)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(third-party)

add_executable(${PROJECT_NAME} src/main.cpp third-party/stb_image/stb_image.h third-party/stb_image/stb_image.cpp)

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(${PROJECT_NAME} copy_assets)

target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} stb_image)