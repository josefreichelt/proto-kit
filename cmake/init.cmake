# Initialize some variables
set(PROJECT_NAME "proto-kit")
set(PROJECT_VERSION "1.0.0")
set(PROJECT_DESCRIPTION "Gamedev starter project()")
set(THIRD_PARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty")
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

if(${PLATFORM} STREQUAL "Web")
    unset(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin_web")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin_web")
    set(CMAKE_INSTALL_BINDIR "${CMAKE_SOURCE_DIR}/bin_web")
endif()

# Fetch Content
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_BASE_DIR ${THIRD_PARTY_DIR})

# M1 mac
if(APPLE AND NOT CMAKE_SYSTEM_PROCESSOR STREQUAL arm64)
    set(CMAKE_OSX_ARCHITECTURES arm64)
endif()

# Hide console on windows release
if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release" AND NOT ${PLATFORM} STREQUAL "Web")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--subsystem,windows")
endif()

# Source and include files, hpp files put to sources for intellisense
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/source/*?(cpp|hpp))

# Exlude test files from build
list(FILTER SRC_FILES EXCLUDE REGEX "\_test\.?(cpp|hpp)")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()
