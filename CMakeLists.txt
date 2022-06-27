## Declare project
project(nxquartz)

cmake_minimum_required(VERSION 3.21)

# We set the C standard to 11.
set(CMAKE_C_STANDARD 17)

## CMake modules

# We have to add the cmake directory to have access to
# the Switch tools and also find_package for libnx.
set(SWITCH_LIB_DIR ${DEVKITPRO}/portlibs/switch/lib)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

## Required libraries and utilities

# SwitchTools provide various helper functions for building Switch file formats.
include(SwitchTools)

# Find libnx, which is required by our application.
find_package(LIBNX REQUIRED)
add_compile_definitions(HAVE_LIBNX)

## Borealis resource location
add_compile_definitions(BOREALIS_RESOURCES="romfs:/")

# Variables
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(VENDOR_DIR ${CMAKE_CURRENT_LIST_DIR}/vendor)
set(BOREALIS_DIR ${VENDOR_DIR}/borealis)

# Borealis source with dependencies
file(GLOB BOREALIS_SRC
	${BOREALIS_DIR}/library/lib/*.cpp
	${BOREALIS_DIR}/library/lib/extern/*/*.c
	${BOREALIS_DIR}/library/lib/extern/*/*/*.c
	${BOREALIS_DIR}/library/lib/*.cpp
	${BOREALIS_DIR}/library/lib/*.c
	${BOREALIS_DIR}/library/lib/extern/glad/*.c
	${BOREALIS_DIR}/library/lib/extern/nanovg/*.c
	${BOREALIS_DIR}/library/lib/extern/libretro-common/compat/*.c
	${BOREALIS_DIR}/library/lib/extern/libretro-common/encodings/*.c
	${BOREALIS_DIR}/library/lib/extern/libretro-common/features/*.c
	${BOREALIS_DIR}/library/lib/extern/fmt/src/*.cc
)

# Quartz source
file(GLOB_RECURSE SRC
	${SOURCE_DIR}/*.cpp
	${SOURCE_DIR}/*.c
	${SOURCE_DIR}/*.h
)

add_executable(nxquartz ${SRC} ${BOREALIS_SRC})

# Borealis and Quartz include directories
target_include_directories(nxquartz PUBLIC
	${INCLUDE_DIR}
	${VENDOR_DIR}/borealis/library/include
	${VENDOR_DIR}/borealis/library/include/borealis/extern
	${BOREALIS_DIR}/library/lib/extern/fmt/include
	${BOREALIS_DIR}/library/include
)

# Portlibs and libnx static libraries 
include_directories("${PORTLIBS}/include")
include_directories("${LIBNX}/include")

target_link_libraries(nxquartz 
	switch::libnx
	-L${LIBNX}/lib
	-L${PORTLIBS}/lib
	-lglfw3 -lEGL -lglapi -ldrm_nouveau -lm -lnx
)

# Application metadata
set_target_properties(nxquartz PROPERTIES
	APP_TITLE "Quartz"
	APP_AUTHOR "JSH32"
	APP_VERSION "0.1.0"
	ICON "${CMAKE_CURRENT_LIST_DIR}/resources/img/icon.jpg"
	ROMFS "${CMAKE_CURRENT_LIST_DIR}/resources"
)

# NX executable target
add_nro_target(nxquartz)