cmake_minimum_required(VERSION 3.13)
project(Utils VERSION 1.0.0)

set(PROJECT_NAME Utils)
set(CMAKE_CXX_STANDARD 20)

if(UNIX)
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra --coverage -g -Wno-unused-variable")
endif()

################################################################################
# Module Imports
################################################################################

#No modules to import 

################################################################################
# Define directories
################################################################################

#add_definitions(-DUTILSLOG) 

################################################################################
# Source groups
################################################################################

set(src
    "precomp.cpp"
    "precomp.h"
)
source_group("src" FILES ${src})

set(src__Event
    "Event/channel.cpp"
    "Event/channel.h"
    "Event/event.h"
    "Event/eventlistener.cpp"
    "Event/eventlistener.h"
)

source_group("Event" FILES ${src__Event})

set(src__Map
    "Map/unorderedcastmap.h"
)

source_group("Map" FILES ${src__Map})

set(src__Proxy
    "Proxy/singletonproxy.h"
)

source_group("Proxy" FILES ${src__Proxy})

set(ALL_FILES
    ${src}
    ${src__Event}   
    ${src__Map}
    ${src__Proxy}  
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

add_precompiled_header(${PROJECT_NAME} "precomp.h" "precomp.cpp")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Utils)

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR};"
)

################################################################################
# Dependencies
################################################################################
IF (UNIX)
  target_link_libraries(${PROJECT_NAME} PRIVATE m)
ENDIF()
