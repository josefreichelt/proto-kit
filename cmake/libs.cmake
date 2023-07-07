# Fetch dependencies
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib"
    GIT_TAG "4.5.0"
)

FetchContent_Declare(
    raygui
    GIT_REPOSITORY "https://github.com/raysan5/raygui"
    GIT_TAG "3.5"
    INSTALL_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)

FetchContent_MakeAvailable(raylib raygui)

# Main raylib
# include_directories("${raylib_BINARY_DIR}/raylib/include")
# include_directories("${raygui_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PRIVATE "${raylib_BINARY_DIR}/raylib/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${raygui_SOURCE_DIR}/src")
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# disabling enum flag due to some raygui enums
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-enum-compare -Wno-ignored-qualifiers -Wno-discarded-qualifiers -Wno-incompatible-pointer-types-discards-qualifiers -Wno-unused-command-line-argument -Wno-unknown-warning-option")

# raylib system dependencies
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
endif()

if(WIN32)
    target_link_options(${PROJECT_NAME} PRIVATE -static)
    target_link_libraries(${PROJECT_NAME} PRIVATE -lopengl32 -lgdi32 -lwinmm -static-libgcc -static-libstdc++ -pthread)
endif()
