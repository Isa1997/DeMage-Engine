cmake_minimum_required(VERSION 3.13)
project(Engine VERSION 1.0.0)

set(PROJECT_NAME Engine)
set(CMAKE_CXX_STANDARD 20)

################################################################################
# Module Imports
################################################################################

if(UNIX)

    #Unix specific flags 
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra --coverage -g -Wno-unused-variable")
    
    #Unix module import (using pkg_config)
    include(FindPkgConfig)
    find_package(SDL2 REQUIRED)
    pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
    pkg_check_modules(SDL2_image REQUIRED IMPORTED_TARGET SDL2_image)
    pkg_check_modules(SDL2_ttf REQUIRED IMPORTED_TARGET SDL2_ttf)
endif()

if(WIN32)
        find_package(SDL2 REQUIRED)
        include_directories(${SDL2_INCLUDE_DIRS})
        
        find_package(SDL2_image REQUIRED)
        include_directories(${SDL2_image_INCLUDE_DIRS})
        
        find_package(SDL2_mixer REQUIRED)
        include_directories(${SDL2_mixer_INCLUDE_DIRS})

        find_package(SDL2_ttf REQUIRED)
        include_directories(${SDL2_ttf_INCLUDE_DIRS})
        
        find_package(glm REQUIRED)
        include_directories(${glm_INCLUDE_DIRS})
        
        find_package(spdlog REQUIRED)
        include_directories(${spdlog_INCLUDE_DIRS})
        
        find_package(fmt REQUIRED)
        include_directories(${fmt_INCLUDE_DIRS})
        
        find_package(ImGui REQUIRED)
        include_directories(${ImGui_INCLUDE_DIRS})
endif()


################################################################################
# Define directories
################################################################################

add_definitions(-DENGINELOG) 

################################################################################
# Source groups
################################################################################
set(src
    "precomp.cpp"
    "precomp.h"
    "src/Engine.h"
)

source_group("src" FILES ${src})

set(src__Audio
    "src/Audio/AudioSystem.cpp"
    "src/Audio/AudioSystem.h"
)

source_group("src\\Audio" FILES ${src__Audio})

set(src__Controller
    "src/Controller/IController.cpp"
    "src/Controller/IController.h"
)

source_group("src\\Controller" FILES ${src__Controller})

set(src__Core
    "src/Core/Application.cpp"
    "src/Core/Application.h"
    "src/Core/EngineSystems.cpp"
    "src/Core/EngineSystems.h"
    "src/Core/EntryPoint.h"
)

source_group("src\\Core" FILES ${src__Core})

set(src__ECS
    "src/ECS/Component.cpp"
    "src/ECS/Component.h"
    "src/ECS/Entity.cpp"
    "src/ECS/Entity.h"
    "src/ECS/EntityManager.cpp"
    "src/ECS/EntityManager.h"
)

source_group("src\\ECS" FILES ${src__ECS})

set(src__Input
    "src/Input/InputAction.h"
    "src/Input/InputManager.cpp"
    "src/Input/InputManager.h"
)

source_group("src\\Input" FILES ${src__Input})

set(src__Logger
    "src/Logger/Logger.cpp"
    "src/Logger/Logger.h"
)

source_group("src\\Logger" FILES ${src__Logger})

set(src__PhysicsSystem
    "src/Physics/PhysicsSystem.cpp"
    "src/Physics/PhysicsSystem.h"
)

source_group("src\\PhysicsSystem" FILES ${src__PhysicsSystem})

set(src__Render
    "src/Render/Renderer.cpp"
    "src/Render/Renderer.h"
    "src/Render/RenderSystem.cpp"
    "src/Render/RenderSystem.h"
    "src/Render/Texture.cpp"
    "src/Render/Texture.h"
    "src/Render/TextureManager.cpp"
    "src/Render/TextureManager.h"
    "src/Render/Window.cpp"
    "src/Render/Window.h"
    "src/Render/WindowData.h"
)

source_group("src\\Render" FILES ${src__Render})

set(ALL_FILES
    ${src}
    ${src__Controller}
    ${src__Core}
    ${src__Audio}
    ${src__ECS}
    ${src__Input}
    ${src__Logger}
    ${src__PhysicsSystem}
    ${src__Render}
)

################################################################################
# Target
################################################################################
if(UNIX)
    add_definitions(-DLINUX)
endif()

if(WIN32)
    add_definitions(-DWINDOWS)
endif()

add_definitions(-DLOGFPS)

add_definitions(-DDEBUGLOG)
add_definitions(-DDEBUGENTITY)


add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

add_precompiled_header(${PROJECT_NAME} "precomp.h" "precomp.cpp")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Engine)

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR};"
    "${CMAKE_CURRENT_SOURCE_DIR}/src;"
)



################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME} Utils )

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE Utils)


if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_ttf_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_mixer::SDL2_mixer)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${spdlog_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE "${glm_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
    target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
endif()

if(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SDL2_Mixer)
    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SDL2_image)
    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SDL2_ttf)
     target_link_libraries(${PROJECT_NAME} PRIVATE m)
endif()