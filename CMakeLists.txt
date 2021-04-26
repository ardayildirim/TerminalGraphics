cmake_minimum_required(VERSION 3.16)
project(TerminalGraphics VERSION 1.0.0)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
set(EXECUTABLE_OUTPUT_PATH "../")

add_library(
  scenes
  ../src/vec3.h
  ../src/vec3.cpp
  
  ../src/Scene1.h
  ../src/Scene1.cpp
  ../src/Scene2.h
  ../src/Scene2.cpp
  ../src/Scene3.h
  ../src/Scene3.cpp
  ../src/Scene4.h
  ../src/Scene4.cpp
  ../src/Scene5.h
  ../src/Scene5.cpp
  )

add_executable(main.out ../src/main.cpp)

target_link_libraries(main.out PRIVATE scenes)
