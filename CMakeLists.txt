cmake_minimum_required(VERSION 2.8.12)

project(PFDScreen)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(PROJECT_SOURCES
                ${PROJECT_SOURCE_DIR}/main.cpp
                ${PROJECT_SOURCE_DIR}/shaderProgram.cpp
                ${PROJECT_SOURCE_DIR}/landscape.cpp
                ${PROJECT_SOURCE_DIR}/AttitudeIndicator.cpp
                ${PROJECT_SOURCE_DIR}/aircraft.cpp
                ${PROJECT_SOURCE_DIR}/altimeter.cpp
                ${PROJECT_SOURCE_DIR}/TextureManager.cpp
                ${PROJECT_SOURCE_DIR}/UserInterface.cpp
                ${PROJECT_SOURCE_DIR}/SpeedIndicator.cpp
                ${PROJECT_SOURCE_DIR}/verticalspeed.cpp
                ${PROJECT_SOURCE_DIR}/verticalspeedindis.cpp
                ${PROJECT_SOURCE_DIR}/HeadingIndicator.cpp
                )


set(PROJECT_HEADERS
                ${PROJECT_INCLUDE_DIR}/shaderProgram.hpp
                ${PROJECT_INCLUDE_DIR}/VertexTypes.hpp
                ${PROJECT_INCLUDE_DIR}/landscape.hpp
                ${PROJECT_INCLUDE_DIR}/AttitudeIndicator.hpp
                ${PROJECT_INCLUDE_DIR}/aircraft.hpp
                ${PROJECT_INCLUDE_DIR}/altimeter.hpp
                ${PROJECT_INCLUDE_DIR}/TextureManager.hpp
                ${PROJECT_INCLUDE_DIR}/stb_image.h
                ${PROJECT_INCLUDE_DIR}/UserInterface.hpp
                ${PROJECT_INCLUDE_DIR}/SpeedIndicator.hpp
                ${PROJECT_SOURCE_DIR}/verticalspeed.hpp
                ${PROJECT_SOURCE_DIR}/verticalspeedindis.hpp
                ${PROJECT_SOURCE_DIR}/HeadingIndicator.hpp
                )



find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

include_directories(${PROJECT_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw GLESv2 )



