# Proto-Kit the Raylib game starter kit

This is a starter project for  game development using the raylib library. It is meant to be used as a template for your own projects.  

### Features:
- Windows, MacOS and Web builds
- Reacting to web window resize
- Included beach bounce minigame
- Customized web templates for debug and release
- Cmake presets for easy configuration


This project is setup to work mainly with cmake and relies on CMakePresets.
Cmake pulls and builds raylib and raygui from source, so you don't have to worry about that.

Setup is tested on MacOS and Windows. Building for web from those platforms is also tested.

Cmake configure also copies all assets from assets/ directory to bin directory. When you add new assets you will need to re run configure.

## Dependencies

- GCC or Clang compiler is required for desktop builds.
- Emscripten is required for web builds.
- Cmake 3.20 or newer is required.

[Raylib - 4.5.0](https://github.com/raysan5/raylib/releases/tag/4.5.0)  
[Raygui - 3.5](https://github.com/raysan5/raygui/releases/tag/3.5)

## Recommended vscode extensions
[CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)  
[C++ Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)  
[CodeLLDB](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb)

## Helpful scripts
I am using mainly vscode with cmake extension to make my life configuring and building easier, but I've also included some scripts to help you out.

`configure.sh` - Configures cmake using presets from CmakePresets.json, you can also pass options to it.

### Options
By default script assumes that you are using gcc compiler and building for desktop in debug mode.
- -release - Configures for release mod
- -clang - Configures for clang compiler (desktop only)
- -gcc - Configures for gcc compiler (desktop only)
- -web - Configures using emscripten compiler, make sure you have emscripten installed and configured and EMSDK evnironment variable set
- -clean - Cleans build and thirdpary directory, this is usefull when changing presets.

Script also detects if you are on windows, in which case it tries to use gcc from mingw and cmake generates mingw makefiles. This is both for desktop and web builds.

`build.sh` - Builds using cmake and presets, has same options as configure.sh

`package_web.sh` - Packages web build into zip file and outputs it to dist/
`package_desktop.sh` - Packages desktop build into zip file and outputs it to dist/

<br/><br/>

----------

<br/><br/>

# Troubleshooting
## When debugging on windows, breakpoints don't work
- Try changing cmake.debugConfig.MIMode from ``lldb`` to ``gdb`` in settings.json or laucnh debug session using the Debug configuration instead of Debug LLDB
