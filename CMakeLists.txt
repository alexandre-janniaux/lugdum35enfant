CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(PROJECT_ROOT ${CMAKE_SOURCE_DIR})
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

PROJECT(LD35)

FIND_PACKAGE(SFML COMPONENTS audio graphics window system REQUIRED)

SET(
    SRCS
    src/main.cpp
    src/menuelements.cpp
    src/screenstack.cpp
    src/gamescreenstate.cpp
    src/menuscreenstate.cpp
    src/scene.cpp
    src/scenenode.cpp
    src/sousmenu.cpp
    src/spritescenenode.cpp
    src/messagebusqueue.cpp
    src/jsoncpp.cpp
)

ADD_EXECUTABLE(
    LD35
    ${SRCS}
)

ADD_DEFINITIONS(
    --std=c++11
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
