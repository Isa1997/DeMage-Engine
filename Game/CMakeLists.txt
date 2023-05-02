cmake_minimum_required(VERSION 3.13)
project(Game VERSION 1.0.0)

set(PROJECT_NAME Game)
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
endif()


################################################################################
# Define directories
################################################################################

add_definitions(-DENGINELOG) 
add_definitions(-DSDL_MAIN_HANDLED) 

################################################################################
# Source groups
################################################################################
set(src
    "src/precomp.cpp"
    "src/precomp.h"
)
source_group("src" FILES ${src})

set(src__Core
    "src/Core/GameApp.cpp"
    "src/Core/GameApp.h"
)
source_group("Core" FILES ${Core})

set(src__Entities
    "src/Entities/Cameracontroller.cpp"
    "src/Entities/Cameracontroller.h"
    "src/Entities/playercontroller.cpp"
    "src/Entities/playercontroller.h"
    "src/Entities/gamecomponents.h"
)
source_group("src//Entities" FILES ${src__Entities})


set(ALL_FILES
    ${src}
    ${src__Core}
    ${src__Entities}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

add_precompiled_header(${PROJECT_NAME} "src/precomp.h" "src/precomp.cpp")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Game)

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR};"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME} Utils)
add_dependencies(${PROJECT_NAME} Engine)

# Link with other targets.



if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_ttf_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE "${spdlog_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE "${glm_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_mixer::SDL2_mixer)
endif()

if(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SDL2_Mixer)
    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SDL2_image)
    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SDL2_ttf)
    target_link_libraries(${PROJECT_NAME} PRIVATE m)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Engine)
target_link_libraries(${PROJECT_NAME} PRIVATE Utils)
