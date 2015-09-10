
cmake_minimum_required(VERSION 3.0.0)

set(FOO_PROJECT_NAME
    freemapper
)
set(FOO_SOURCE_DIR
    src
)

set(FOO_SOURCE
    ${FOO_SOURCE_DIR}/main.cpp
)

set(FOO_LIBRARIES_DIR
    libs
)
set(FOO_LIBRARIES 
    model
    gui
    projection
    capture
)

project(${FOO_PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -std=c++11 -Wall -Wpedantic")
set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/")

#########
# GTest #
#########
enable_testing()
add_subdirectory(libs/gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add_subdirectory(libs/opencv)
#include_directories(${opencv_SOURCE_DIR}/include ${opencv_SOURCE_DIR})

add_subdirectory(libs/SFML)
include_directories(${SFML_SOURCE_DIR}/include ${SFML_SOURCE_DIR})


#ExternalProject_Add (
#       opencv
#       GIT_REPOSITORY "https://github.com/Itseez/opencv.git"
#       GIT_TAG "master"
#       UPDATE_COMMAND ""
#       INSTALL_COMMAND "" )

###########
# Project #
###########
add_executable(${FOO_PROJECT_NAME} ${FOO_SOURCE})


foreach(LIBRARY ${FOO_LIBRARIES})
    add_subdirectory("${FOO_LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)
target_link_libraries(${FOO_PROJECT_NAME} ${FOO_LIBRARIES})


###############################################################################
### Qt
###############################################################################
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)

# Use the Widgets module from Qt 5.
target_link_libraries(${FOO_PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${FOO_PROJECT_NAME} Qt5::Quick)

configure_file(qml/main.qml qml/main.qml)

qt5_use_modules(${FOO_PROJECT_NAME} Widgets)
qt5_use_modules(${FOO_PROJECT_NAME} Qml)
qt5_use_modules(${FOO_PROJECT_NAME} Quick)
