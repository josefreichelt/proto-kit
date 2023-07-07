cmake_minimum_required(VERSION 3.20)

# Helper cmake modules
include(cmake/varprinter.cmake)

# Init settings and variables
include(cmake/init.cmake)

project(
    ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    DESCRIPTION ${PROJECT_DESCRIPTION}
    LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${SRC_FILES})

# Find and set third party libraries
include(cmake/libs.cmake)

# Web specific settings
include(cmake/webconfig.cmake)

# Find and copy assets
include(cmake/assets.cmake)

varprinter(PLATFORM CMAKE_RUNTIME_OUTPUT_DIRECTORY WIN32 MSYS UNIX)
