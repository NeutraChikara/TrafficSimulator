cmake_minimum_required(VERSION 3.12)
project(TrafficSimulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(TrafficSimulator main.cpp Systems/Render.cpp Systems/Render.h Systems/System.cpp Systems/System.h Components/Component.h Components/ComponentUtility.cpp Components/ComponentUtility.h Entities/Entity.cpp Entities/Entity.h Managers/World.cpp Managers/World.h Systems/Logger.h Systems/Move.cpp Systems/Move.h Components/Transform.h Components/Velocity.h Components/Path.h Components/Node.h Components/TrafficLight.h Systems/TrafficLightControl.cpp Systems/TrafficLightControl.h Components/Render.h Systems/Logger.cpp Components/Node.cpp Components/Transform.cpp Components/Velocity.cpp Help/Visitors.cpp Help/Visitors.h Systems/VehicleCollisionPrevention.cpp Systems/VehicleCollisionPrevention.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED) # Disable when GLUT is not installed, only need for OpenGL code
find_package(Boost REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(TrafficSimulator ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )