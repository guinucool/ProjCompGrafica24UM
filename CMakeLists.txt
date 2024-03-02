cmake_minimum_required(VERSION 3.5)

project(generator)
add_executable(${PROJECT_NAME} src/generator.cpp)

project(engine)
add_executable(${PROJECT_NAME} src/engine.cpp)