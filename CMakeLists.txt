cmake_minimum_required(VERSION 3.12)

project(ParticleAccelerator)

set(CMAKE_CXX_STANDARD  17)
include_directories(header)

set(SOURCE_FILES
        src/Accelerator.cpp
        src/CurvedElement.cpp
        src/Element.cpp
        src/Particle.cpp
        src/Vector3D.cpp
        text/TextSupport.cpp
        )

add_executable(test_vector3d test/test_vector3d.cpp ${SOURCE_FILES})
add_executable(test_particle test/test_particle.cpp ${SOURCE_FILES})
add_executable(text_accelerator text/main.cpp ${SOURCE_FILES})