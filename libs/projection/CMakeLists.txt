
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_AUTOMOC ON)

set(PROJECT_NAME
    freemapper-projection
)
set(LIBRARY_NAME
    projection
)
set(LIBRARY_HEADERS_DIR
    include/${LIBRARY_NAME}
)
set(LIBRARY_HEADERS
    ${LIBRARY_HEADERS_DIR}/Projection.h
)
set(LIBRARY_SOURCE_DIR
    src
)
set(LIBRARY_SOURCE
    ${LIBRARY_SOURCE_DIR}/Projection.cpp
)

project(${PROJECT_NAME})

add_library(${LIBRARY_NAME} STATIC
    ${LIBRARY_HEADERS}
    ${LIBRARY_SOURCE}
)

target_include_directories(${LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# See http://en.sfml-dev.org/forums/index.php?topic=11372.0 for explaination
target_link_libraries(${LIBRARY_NAME}
    sfml-graphics
    model
)

add_subdirectory(test)

#####
# Qt
#####


# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Multimedia REQUIRED)

qt5_use_modules(${LIBRARY_NAME} Widgets)
qt5_use_modules(${LIBRARY_NAME} Qml)
qt5_use_modules(${LIBRARY_NAME} Quick)
qt5_use_modules(${LIBRARY_NAME} Multimedia)
