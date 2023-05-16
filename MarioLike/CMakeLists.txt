cmake_minimum_required(VERSION 3.8)

project("MarioLikeB3")

set(CMAKE_CXX_STANDARD 20)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.env)
  file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/.env ENV_VARS)
  foreach(env_var ${ENV_VARS})
    string(REGEX REPLACE "^[^=]+=" "" env_value ${env_var})
    string(REGEX REPLACE "=.*$" "" env_name ${env_var})
    set(ENV{${env_name}} ${env_value})
  endforeach()
endif()

if(DEFINED ENV{PATH_VCPKG})
	include($ENV{PATH_VCPKG})
endif()

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (HEADERS
    ${HEADER_DIR}/component/BT/BoombaBT.h
    ${HEADER_DIR}/component/Animator.h
    ${HEADER_DIR}/component/BehaviorTree.h
    ${HEADER_DIR}/component/BoxColliderComponent.h
    ${HEADER_DIR}/component/Transform.h
    ${HEADER_DIR}/component/SpriteComponent.h
    ${HEADER_DIR}/component/TestComponent.h
    ${HEADER_DIR}/component/CharacterControllerComponent.h
    ${HEADER_DIR}/component/PhysicsComponent.h
    ${HEADER_DIR}/engine/GameEngine.h
    ${HEADER_DIR}/managers/EntityManager.h
    ${HEADER_DIR}/managers/AssetManager.h
    ${HEADER_DIR}/managers/LevelManager.h
    ${HEADER_DIR}/managers/RenderManager.h
    ${HEADER_DIR}/managers/InputManager.h
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
    ${HEADER_DIR}/models/Void.h
    ${HEADER_DIR}/utils/AI/Nodes/Patrol.h
    ${HEADER_DIR}/utils/AI/Node.h
    ${HEADER_DIR}/utils/AI/Selector.h
    ${HEADER_DIR}/utils/AI/Sequence.h
    ${HEADER_DIR}/utils/Anim/Link.h
    ${HEADER_DIR}/utils/Anim/Animation.h
    ${HEADER_DIR}/utils/Anim/Animations/BoombaIdle.h
    ${HEADER_DIR}/utils/Anim/Animations/BoombaRun.h
    ${HEADER_DIR}/utils/Anim/Animations/MarioIdle.h
    ${HEADER_DIR}/utils/Anim/Animations/MarioRun.h
    ${HEADER_DIR}/utils/BlackBoard/Blackboard.hpp
    ${HEADER_DIR}/utils/BlackBoard/BlackboardID.hpp
    ${HEADER_DIR}/utils/BlackBoard/BlackboardT.hpp
    ${HEADER_DIR}/utils/BlackBoard/BlackboardT.inl
    ${HEADER_DIR}/utils/BlackBoard/Valuehandle.hpp
    ${HEADER_DIR}/utils/BlackBoard/Valuehandle.inl
    ${HEADER_DIR}/utils/Rtti.h
    ${HEADER_DIR}/utils/Sling.h
    ${HEADER_DIR}/utils/Vector2.h
    ${HEADER_DIR}/utils/ISingleton.h
    ${HEADER_DIR}/utils/DrawCall.h
)

set (SOURCES
    ${SOURCE_DIR}/component/Animator.cpp
    ${SOURCE_DIR}/component/Transform.cpp
    ${SOURCE_DIR}/component/SpriteComponent.cpp
    ${SOURCE_DIR}/component/BoxColliderComponent.cpp
    ${SOURCE_DIR}/component/PhysicsComponent.cpp
    ${SOURCE_DIR}/engine/GameEngine.cpp
    ${SOURCE_DIR}/managers/EntityManager.cpp
    ${SOURCE_DIR}/managers/AssetManager.cpp
    ${SOURCE_DIR}/managers/LevelManager.cpp
    ${SOURCE_DIR}/managers/RenderManager.cpp
    ${SOURCE_DIR}/managers/InputManager.cpp
    ${SOURCE_DIR}/models/Block.cpp
    ${SOURCE_DIR}/models/Boomba.cpp
    ${SOURCE_DIR}/models/Bouseur.cpp
    ${SOURCE_DIR}/models/Coin.cpp
    ${SOURCE_DIR}/models/Component.cpp
    ${SOURCE_DIR}/models/Entity.cpp
    ${SOURCE_DIR}/models/Kupla.cpp
    ${SOURCE_DIR}/models/Level.cpp
    ${SOURCE_DIR}/models/Player.cpp
    ${SOURCE_DIR}/utils/Animation.cpp
    ${SOURCE_DIR}/utils/Link.cpp
    ${SOURCE_DIR}/utils/DrawCall.cpp
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

