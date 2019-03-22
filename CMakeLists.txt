cmake_minimum_required(VERSION 3.12)

project(ParticleAccelerator)

set(CMAKE_CXX_STANDARD  17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
include_directories(header)

set(SOURCE_FILES
        src/Vector3D.cpp
        src/Particle.cpp
        src/Accelerator.cpp
        src/Element.cpp
        src/CurvedElement.cpp
        src/StraightElement.cpp)

add_executable(test_vector3d test/test_vector3d.cpp ${SOURCE_FILES})
add_executable(test_particle test/test_particle.cpp ${SOURCE_FILES})
add_executable(test_accelerator test/test_accelerator.cpp ${SOURCE_FILES})
