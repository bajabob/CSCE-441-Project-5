
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(a5-ray-tracing)

set(CMAKE_CXX_FLAGS "--Wall --pedantic")

# Check the system for Armadillo
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

# Check the system for OpenGL
include (FindOpenGL)
if (OPENGL_FOUND)
   include_directories (${OPENGL_INCLUDE_DIR})
endif (OPENGL_FOUND)

# Check the system for GLUT
include (FindGLUT)
if (GLUT_FOUND)
   include_directories (${GLUT_INCLUDE_DIR})
endif (GLUT_FOUND)

set(CMAKE_CXX_FLAGS "-Wall --pedantic -O3")

add_executable (main main.cpp
			 scene.cpp
			 plane.cpp)
target_link_libraries (main ${OPENGL_LIBRARIES}
                                ${GLUT_LIBRARIES}
                                ${ARMADILLO_LIBRARIES})
