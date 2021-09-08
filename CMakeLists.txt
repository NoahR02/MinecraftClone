cmake_minimum_required(VERSION 3.15)
project(MinecraftClone)

add_subdirectory(third-party)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)