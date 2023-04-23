cmake_minimum_required(VERSION 3.8)

project("MarioLikeB3")

set(CMAKE_CXX_STANDARD 20)

include(C:/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (HEADERS
    ${HEADER_DIR}/component/Animator.h
    ${HEADER_DIR}/component/Transform.h
    ${HEADER_DIR}/component/SpriteComponent.h
    ${HEADER_DIR}/component/TestComponent.h
    ${HEADER_DIR}/engine/GameEngine.h
    ${HEADER_DIR}/engine/EntityManager.h
    ${HEADER_DIR}/managers/AssetManager.h
    ${HEADER_DIR}/managers/LevelManager.h
    ${HEADER_DIR}/managers/RenderManager.h
    ${HEADER_DIR}/models/Block.h
    ${HEADER_DIR}/models/Boomba.h
    ${HEADER_DIR}/models/Bouseur.h
    ${HEADER_DIR}/models/Coin.h
    ${HEADER_DIR}/models/Component.h
    ${HEADER_DIR}/models/Ennemy.h
    ${HEADER_DIR}/models/Entity.h
    ${HEADER_DIR}/models/GameObject.h
    ${HEADER_DIR}/models/Kupla.h
    ${HEADER_DIR}/models/Level.h
    ${HEADER_DIR}/models/Player.h
    ${HEADER_DIR}/models/toto.h
    ${HEADER_DIR}/utils/Anim/Link.h
    ${HEADER_DIR}/utils/Anim/Animation.h
    ${HEADER_DIR}/utils/Rtti.h
    ${HEADER_DIR}/utils/Sling.h
    ${HEADER_DIR}/utils/Vector2.h
)

set (SOURCES
    ${SOURCE_DIR}/component/Animator.cpp
    ${SOURCE_DIR}/component/Transform.cpp
    ${SOURCE_DIR}/component/SpriteComponent.cpp
    ${SOURCE_DIR}/engine/EntityManager.cpp
    ${SOURCE_DIR}/engine/GameEngine.cpp
    ${SOURCE_DIR}/managers/AssetManager.cpp
    ${SOURCE_DIR}/managers/LevelManager.cpp
    ${SOURCE_DIR}/managers/RenderManager.cpp
    ${SOURCE_DIR}/models/Block.cpp
    ${SOURCE_DIR}/models/Boomba.cpp
    ${SOURCE_DIR}/models/Bouseur.cpp
    ${SOURCE_DIR}/models/Coin.cpp
    ${SOURCE_DIR}/models/Component.cpp
    ${SOURCE_DIR}/models/Ennemy.cpp
    ${SOURCE_DIR}/models/Entity.cpp
    ${SOURCE_DIR}/models/Kupla.cpp
    ${SOURCE_DIR}/models/Level.cpp
    ${SOURCE_DIR}/models/Player.cpp
    ${SOURCE_DIR}/utils/Animation.cpp
    ${SOURCE_DIR}/utils/Link.cpp
    main.cpp
)

#find_package(sfml REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MarioLikeB3 PROPERTY CXX_STANDARD 20)
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_auto_type)

#target_link_libraries(${PROJECT_NAME}
#  PRIVATE
#    sfml::sfml)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${HEADER_DIR}>
  PRIVATE
    ${SOURCE_DIR}
)

