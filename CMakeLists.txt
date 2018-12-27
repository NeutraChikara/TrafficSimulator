cmake_minimum_required(VERSION 3.10.2)
project(TrafficSimulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(TrafficSimulator main.cpp Systems/Render.cpp Systems/Render.h Systems/System.cpp Systems/System.h Components/Component.h Components/ComponentUtility.cpp Components/ComponentUtility.h Entities/Entity.cpp Entities/Entity.h Managers/World.cpp Managers/World.h Systems/Logger.h Systems/Drive.cpp Systems/Drive.h Components/Transform.h Components/SpeedAndAcceleration.h Components/Path.h Components/Node.h Components/TrafficLight.h Systems/TrafficLight.cpp Systems/TrafficLight.h Components/Render.h Systems/Logger.cpp Components/Node.cpp Components/Transform.cpp Components/SpeedAndAcceleration.cpp Helpers/Visitor.h Systems/VehicleCollisionPrevention.cpp Systems/VehicleCollisionPrevention.h Components/Path.cpp Helpers/Color.cpp Helpers/Color.h Components/Render.cpp Components/RoadGraph.cpp Components/RoadGraph.h Helpers/Roads.cpp Helpers/Roads.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED) # Disable when GLUT is not installed, only need for OpenGL code
find_package(Boost REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(TrafficSimulator ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )