# Web Configurations
if(${PLATFORM} STREQUAL "Web")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -Wno-unused-command-line-argument --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets@assets")

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS " --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/web/template.debug.html")
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS " --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/web/template.release.html -O3")
    endif()

    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index")
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_WEB)
    target_include_directories(${PROJECT_NAME} PRIVATE $ENV{EMSDK}/upstream/emscripten/cache/sysroot/include)

    # Copy web related assets to output directory
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/web/style.css DESTINATION ${EXECUTABLE_OUTPUT_PATH}/)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/web/module.js DESTINATION ${EXECUTABLE_OUTPUT_PATH}/)
endif()
