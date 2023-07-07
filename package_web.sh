#!/bin/bash

# Read the version from CMakeLists.txt
NAME=$(grep 'PROJECT_NAME' cmake/init.cmake | sed -E 's/.*"([^"]+)".*/\1/')
VERSION=$(grep 'PROJECT_VERSION' cmake/init.cmake | tail -n 1 | sed -E 's/.*"([0-9]+\.[0-9]+\.[0-9]+)".*/\1/')
platform=$(uname -o)
# Create a timestamped archive file with the version number
ARCHIVE_NAME="${NAME}_${VERSION}_Web_$(date +%Y-%m-%d).zip"
mkdir -p dist/


# Create the archive
if [[ "$platform" == "Windows" || "$platform" == "Msys" ]]; then
    cd bin_web
    7z a ${ARCHIVE_NAME} *
    mv ${ARCHIVE_NAME} ../dist/
elif [[ "$platform" == "Darwin" ]]; then
    find bin_web -maxdepth 1 -type f | xargs zip -j "dist/${ARCHIVE_NAME}"
else
    find bin_web -maxdepth 1 -type f -printf "%f\n" | zip -@ "dist/${ARCHIVE_NAME}"
fi

# Print the archive filename
echo "Archive created: ${ARCHIVE_NAME}"
