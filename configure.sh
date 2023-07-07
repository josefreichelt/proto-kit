#!/usr/bin/env bash
# This script is used to configure cmake for different platforms and compilers
# By default, it configures cmake for gcc in debug mode


release=false
gcc=true
clang=false
web=false
platform=$(uname -o)
clean=false
# Parse command line arguments
while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
        -release)
            release=true
            shift
        ;;
        -clang)
            clang=true
            shift
        ;;
        -gcc)
            gcc=true
            shift
        ;;
        -web)
            web=true
            shift
        ;;
        -clean)
            clean=true
            shift
        ;;
        *)
            echo "Unknown option: $key"
            exit 1
        ;;
    esac
done

# Clean existing build and third party directories
if $clean; then
    rm -rf build
    rm -rf build_web
    cd thirdparty
    find . -type d -name "*-subbuild*" -exec rm -r {} +
    cd ..
fi



# Prepare build directory for cmake
if $web; then
    mkdir -p build_web
    cd build_web
else
    mkdir -p build
    cd build
fi


# Configure cmake for web
if $web; then
    if [[ "$platform" == "Windows" || "$platform" == "Msys" ]]; then
        if $release; then
            cmake .. --preset web_release_win
        else
            cmake .. --preset web_debug_win
        fi
    else
        if $release; then
            cmake .. --preset web_release
        else
            cmake .. --preset web_debug
        fi
    fi
    exit 0
fi


if ! $web; then
    # GCC on windows is preferable
    if [[ "$platform" == "Windows" || "$platform" == "Msys" ]]; then
        gcc=true
    fi
    # Configure cmake for gcc
    if $gcc; then
        if $release; then
            if [[ "$platform" == "Windows" || "$platform" == "Msys" ]]; then
                cmake .. --preset gcc_release_win
            else
                cmake .. --preset gcc_release
            fi
        else
            if [[ "$platform" == "Windows" || "$platform" == "Msys" ]]; then
                cmake .. --preset gcc_debug_win
            else
                cmake .. --preset gcc_debug
            fi
        fi
        exit 0
    fi
    # Configure cmake for clang
    if $clang; then
        if $release; then
            cmake .. --preset clang_release
        else
            cmake .. --preset clang_debug
        fi
        exit 0
    fi
fi
