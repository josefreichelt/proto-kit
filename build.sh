#!/usr/bin/env bash
# This script is used to build using cmake for different platforms and compilers


release=false
gcc=true
clang=false
web=false
platform=$(uname -o)
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
        *)
            echo "Unknown option: $key"
            exit 1
        ;;
    esac
done

# Build web
if $web; then
    if [[ "$platform" == "Windows" || "$platform" == "Msys" ]]; then
        if $release; then
            cmake --build --preset build_web_release_win
        else
            cmake --build --preset build_web_debug_win
        fi
    else
        if $release; then
            cmake --build --preset build_web_release
        else
            cmake --build --preset build_web_debug
        fi
    fi
    exit 0
fi


if ! $web; then
    # GCC on windows is preferable
    if [[ "$platform" == "Windows" || "$platform" == "Msys" ]]; then
        gcc=true
    fi
    # Build for gcc
    if $gcc; then
        if $release; then
            if [[ "$platform" == "Windows" || "$platform" == "Msys" ]]; then
                cmake --build --preset build_gcc_release_win
            else
                cmake --build --preset build_gcc_release
            fi
        else
            if [[ "$platform" == "Windows" || "$platform" == "Msys" ]]; then
                cmake --build --preset build_gcc_debug_win
            else
                cmake --build --preset build_gcc_debug .
            fi
        fi
        exit 0
    fi
    # Configure cmake for clang
    if $clang; then
        if $release; then
            cmake --build --preset build_clang_release
        else
            cmake --build --preset build_clang_debug
        fi
        exit 0
    fi
fi
