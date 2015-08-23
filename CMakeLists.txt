CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(LD35)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})


FIND_PACKAGE(SFML COMPONENTS audio graphics window system REQUIRED)

SET(
    SRCS
    src/main.cpp
    src/menuelements.cpp
    src/level.cpp
    src/screenstack.cpp
    src/gamescreenstate.cpp
    src/menuscreenstate.cpp
    src/scene.cpp
    src/scenenode.cpp
    src/sousmenu.cpp
    src/spritescenenode.cpp
    src/lamp.cpp
    src/lighthandler.cpp
    src/geometry.cpp
)

ADD_EXECUTABLE(
    LD35
    ${SRCS}
)

ADD_DEFINITIONS(
    --std=c++11
    -g
)

INCLUDE_DIRECTORIES(
    ${SFML_INCLUDE_DIR}
)

TARGET_LINK_LIBRARIES(
    LD35
    ${SFML_AUDIO_LIBRARY}
    ${SFML_GRAPHICS_LIBRARY}
    ${SFML_WINDOW_LIBRARY}
    ${SFML_SYSTEM_LIBRARY}
)
