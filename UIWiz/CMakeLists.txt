cmake_minimum_required(VERSION 3.13)
project(UIWiz VERSION 1.0.0)

set(PROJECT_NAME UIWiz)
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

################################################################################
# Source groups
################################################################################
set(precomp
    "precomp.cpp"
    "precomp.h"
)

source_group("." FILES ${precomp})

set(src
    "src/widget.cpp"
    "src/widget.h"
)

source_group("src" FILES ${src})

set(ALL_FILES
    ${precomp}
    ${src}
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
add_dependencies(${PROJECT_NAME} Engine )

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE Utils)
target_link_libraries(${PROJECT_NAME} PRIVATE Engine)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_ttf_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_mixer::SDL2_mixer)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${spdlog_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE "${glm_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
endif()

if(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SDL2_Mixer)
    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SDL2_image)
    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SDL2_ttf)
     target_link_libraries(${PROJECT_NAME} PRIVATE m)
endif()