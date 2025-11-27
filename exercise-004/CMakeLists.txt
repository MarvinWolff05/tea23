cmake_minimum_required (VERSION 3.10.2)

project (exercise-004 VERSION 0.0.1 LANGUAGES CXX)
string(TIMESTAMP BUILD_DATE "%Y-%m-%dT%H:%M:%S")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Dependencies
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_package(Catch2 3 REQUIRED)

# NEU: OpenCV
find_package(OpenCV REQUIRED core imgcodecs imgproc)

# config.h generieren
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/config.h"
    @ONLY
)

# Include-Pfade: generierte Header + OpenCV
include_directories(
    "${CMAKE_CURRENT_BINARY_DIR}/include"
    ${OpenCV_INCLUDE_DIRS}
)

# Bildpfade
set(INPUT_IMAGE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets/image.jpg")
set(GENERATED_HEADER_PATH "${CMAKE_CURRENT_BINARY_DIR}/include/image.h")

# Python-Script ausführen
add_custom_command(
    OUTPUT ${GENERATED_HEADER_PATH}
    COMMAND ${CMAKE_COMMAND} -E env python3
            ${CMAKE_CURRENT_SOURCE_DIR}/jpg_to_header.py
            ${INPUT_IMAGE_PATH}
            ${GENERATED_HEADER_PATH}
    DEPENDS
        ${INPUT_IMAGE_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}/jpg_to_header.py
    COMMENT "Generating header file from image..."
)

add_custom_target(generate_image_header ALL DEPENDS ${GENERATED_HEADER_PATH})

# Executable
add_executable(${PROJECT_NAME}
    main.cpp
    ${GENERATED_HEADER_PATH}
)

add_dependencies(${PROJECT_NAME} generate_image_header)

# Linker-Libs
target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt::fmt
    CLI11::CLI11
    ${OpenCV_LIBS}          # <-- das ist wichtig
)