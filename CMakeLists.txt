cmake_minimum_required(VERSION 3.12)
project(TrafficSimulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(TrafficSimulator main.cpp Systems/Render.cpp Systems/Render.h Systems/System.cpp Systems/System.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(TrafficSimulator ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )