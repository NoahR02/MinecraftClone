cmake_minimum_required(VERSION 3.15)
project(stb_image)

add_library(${PROJECT_NAME} STATIC stb_image.h stb_image.cpp)
target_include_directories(${PROJECT_NAME} INTERFACE ../)