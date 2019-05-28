cmake_minimum_required(VERSION 3.12)

project(ParticleAccelerator)

set(CMAKE_CXX_STANDARD  17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
include_directories(header)

set(SOURCE_FILES
		src/Vector3D.cpp
		src/Particle.cpp
		src/Element.cpp
		src/CurvedElement.cpp
		src/StraightElement.cpp
		src/Accelerator.cpp
		src/Dipole.cpp
		src/Segment.cpp
		src/Quadrupole.cpp
        src/CircularBeam.cpp
		src/Beam.cpp
		src/Sextupole.cpp
		src/Node.cpp)

set(TEXT_SOURCES
        text/TextSupport.cpp)

set(QT_SOURCES
        qt/GlWidget.cpp
        qt/QtSupport.cpp
        qt/GlSphere.cpp
		qt/ScatterPlot.cpp)


add_executable(test_vector3d test/test_vector3d.cpp ${SOURCE_FILES})
add_executable(test_particle test/test_particle.cpp ${SOURCE_FILES})
add_executable(text_accelerator text/text_accelerator.cpp ${SOURCE_FILES} ${TEXT_SOURCES})
add_executable(p10 text/p10.cpp ${SOURCE_FILES} ${TEXT_SOURCES})
add_executable(testModele text/testModel.cpp ${SOURCE_FILES} ${TEXT_SOURCES})

if (NOT WIN32)  # So Gabin can use cmake without problems with qt
	# This doesn't compile as I don't know how to add files like
	# shaders with cmake. It's sole purpose it to make clion functional.
	add_executable(qt_accelerator qt/qt_main.cpp ${SOURCE_FILES} ${QT_SOURCES})
	find_package(Qt5Core REQUIRED)
	find_package(Qt5Widgets REQUIRED)
	find_package(Qt5Gui REQUIRED)
	find_package(Qt5Charts REQUIRED)
	find_package(Qt5OpenGL REQUIRED)
	target_link_libraries(qt_accelerator Qt5::Widgets)
	target_link_libraries(qt_accelerator Qt5::Charts)
	target_link_libraries(qt_accelerator Qt5::OpenGL)
endif()