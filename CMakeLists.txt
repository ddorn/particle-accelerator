cmake_minimum_required(VERSION 3.12)

project(ParticleAccelerator)

set(CMAKE_CXX_STANDARD  17)
set(SOURCE_FILES src/Vector3D.cpp src/Particle.cpp src/Accelerator.cpp)

add_executable(test_vector3d test/test_vector3d.cpp ${SOURCE_FILES})
add_executable(test_particle test/test_particle.cpp ${SOURCE_FILES})
add_executable(test_accelerator test/test_accelerator.cpp ${SOURCE_FILES})
