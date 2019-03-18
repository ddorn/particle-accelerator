cmake_minimum_required(VERSION 3.12)

project(ParticleAccelerator)

set(CMAKE_CXX_STANDARD  17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
include_directories(header)

set(SOURCE_FILES
        src/Accelerator.cpp
        src/CurvedElement.cpp
        src/Element.cpp
        src/Particle.cpp
        src/Vector3D.cpp)

set(TEXT_SOURCES
        text/TextSupport.cpp)

set(QT_SOURCES
        qt/GlWidget.cpp
        qt/QtSupport.cpp
        qt/GlSphere.cpp)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)

add_executable(test_vector3d test/test_vector3d.cpp ${SOURCE_FILES})
add_executable(test_particle test/test_particle.cpp ${SOURCE_FILES})
add_executable(text_accelerator text/main.cpp ${SOURCE_FILES} ${TEXT_SOURCES})

add_executable(qt_accelerator qt/qt_main.cpp ${SOURCE_FILES} ${QT_SOURCES})
target_link_libraries(qt_accelerator Qt5::Widgets)
target_link_libraries(qt_accelerator Qt5::OpenGL)