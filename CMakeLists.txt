CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(PROJECT_ROOT ${CMAKE_SOURCE_DIR})
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

PROJECT(LD35)

FIND_PACKAGE(SFML COMPONENTS audio graphics window system REQUIRED)

SET(
    SRCS
    src/collisionsolver.cpp
    src/entitypool.cpp
    src/entityscene.cpp
    src/entitysystem.cpp
    src/gamescreenstate.cpp
    src/gameworld.cpp
    src/geometry.cpp
    src/hero.cpp
    src/jsoncpp.cpp
    src/lamp.cpp
    src/lampes.cpp
    src/lighthandler.cpp
    src/lightray.cpp
    src/main.cpp
    src/menuelements.cpp
    src/menuscreenstate.cpp
    src/messagebusqueue.cpp
    src/meuble.cpp
    src/physicinstance.cpp
    src/physicbody.cpp
    src/physicgeom.cpp
    src/scene.cpp
    src/scenenode.cpp
    src/screenstack.cpp
    src/sousmenu.cpp
    src/spritescenenode.cpp
    src/wallscenenode.cpp
    src/IA_familymember.cpp
    src/IA_generate_ronde.cpp
    src/IA_astar_grille.cpp
    src/IA_trouver_reseau.cpp
    src/IA_printer.cpp
    src/IA_astar_reseau.cpp
    src/IA_geometry.cpp

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
