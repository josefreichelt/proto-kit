#!/bin/bash

# Read the version from CMakeLists.txt
NAME=$(grep 'PROJECT_NAME' cmake/init.cmake | sed -E 's/.*"([^"]+)".*/\1/')
VERSION=$(grep 'PROJECT_VERSION' cmake/init.cmake | tail -n 1 | sed -E 's/.*"([0-9]+\.[0-9]+\.[0-9]+)".*/\1/')
platform=$(uname -o)
# Create a timestamped archive file with the version number
ARCHIVE_NAME="${NAME}_${VERSION}_Desktop_$(date +%Y-%m-%d).zip"
mkdir -p dist/


# Create the archive
if [[ "$platform" == "Windows" || "$platform" == "Msys" ]]; then
    cd bin
    7z a ${ARCHIVE_NAME} *
    mv ${ARCHIVE_NAME} ../dist/
else
    cd bin
    zip -r "../dist/${ARCHIVE_NAME}" .
fi

# Print the archive filename
echo "Archive created: ${ARCHIVE_NAME}"
