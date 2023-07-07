# Copy assets only for desktop builds
if(NOT ${PLATFORM} STREQUAL "Web")
    message("Copying assets")
    file(GLOB_RECURSE ASSET_FILES ${CMAKE_CURRENT_SOURCE_DIR}/assets/*)
    file(COPY ${ASSET_FILES} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/assets)
endif()
