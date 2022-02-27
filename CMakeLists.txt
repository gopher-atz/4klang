cmake_minimum_required(VERSION 3.15)

project(4klang LANGUAGES CXX RC)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Cache option defaults
set(DOWNLOAD_YASM OFF CACHE BOOL "Download yasm if not present.")
set(YASM_PATH "${PROJECT_BINARY_DIR}/downloads/" CACHE PATH "Search path for yasm.")

# Download yasm if configured in cache and not present.
find_program(YASM NAMES yasm-1.3.0-win32.exe HINTS "${YASM_PATH}/")
if(${YASM} MATCHES YASM-NOTFOUND AND DOWNLOAD_YASM)
    set(YASM_URL "http://www.tortall.net/projects/yasm/releases/yasm-1.3.0-win32.exe")
    message(STATUS "Downloading YASM from ${YASM_URL}...")
    file(DOWNLOAD ${YASM_URL} "${YASM_PATH}/yasm-1.3.0-win32.exe" SHOW_PROGRESS)
    find_program(YASM NAMES yasm-1.3.0-win32.exe HINTS "${YASM_PATH}")
endif()
message(STATUS "Found YASM: ${YASM}")

# Build-type-dependent configuration
add_compile_definitions(WIN32 _WINDOWS WINDOWS=1)
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_compile_definitions(_DEBUG _CRT_SECURE_NO_DEPRECATE)
    add_compile_options(/MTd)
elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
    add_compile_definitions(NDEBUG)
    add_compile_options(/MT)
endif()

set(YASM_OPTIONS ${YASM_OPTIONS} -Xvc -fwin32)

add_subdirectory(4klang_source/Go4kVSTi)
