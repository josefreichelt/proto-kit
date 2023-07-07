#include "web.hpp"
#ifdef PLATFORM_WEB

void RegisterEmscriptenCallbacks()
{
    emscripten_set_interval(HandleEmscriptenCanvasResize, 250, 0);
}

void HandleEmscriptenCanvasResize(void* userData)
{
    double cssWidth, cssHeight;
    int canvasWidth, canvasHeight;
    emscripten_get_canvas_element_size("#canvas", &canvasWidth, &canvasHeight);
    emscripten_get_element_css_size("#canvas", &cssWidth, &cssHeight);
    EmscriptenFullscreenChangeEvent fullscreenStatus;
    emscripten_get_fullscreen_status(&fullscreenStatus);

    if (fullscreenStatus.fullscreenEnabled && fullscreenStatus.isFullscreen) {
        if ((static_cast<int>(fullscreenStatus.screenWidth) != GameSettings::screenWidth || static_cast<int>(fullscreenStatus.screenHeight) != GameSettings::screenHeight)) {

            auto dpi = emscripten_get_device_pixel_ratio();
            GameSettings::screenWidth = static_cast<int>(fullscreenStatus.screenWidth);
            GameSettings::screenHeight = static_cast<int>(fullscreenStatus.screenHeight);
// Deprecated by emscripten, but due to different functionality from emscripten_set_canvas_element_size still needed
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
            emscripten_set_canvas_size(GameSettings::screenWidth, GameSettings::screenHeight);
#pragma GCC diagnostic pop
        }
    }
    if (!fullscreenStatus.isFullscreen) {
        if ((static_cast<int>(cssWidth) != GameSettings::screenWidth || static_cast<int>(cssHeight) != GameSettings::screenHeight)) {
            GameSettings::screenWidth = cssWidth;
            GameSettings::screenHeight = cssHeight;
            SetWindowSize(cssWidth, cssHeight);
        }
    }
}

#endif
