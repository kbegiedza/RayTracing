cmake_minimum_required (VERSION 3.9)

project(RayTracing)

set(CMAKE_CXX_STANDARD 11)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src/")

include_directories("${INCLUDE_DIR}")
include_directories("${SRC_DIR}")

file(GLOB ALL_SRC
    "${INCLUDE_DIR}*.hpp"
    "${SRC_DIR}*.cpp"
    )

add_executable(RayTracing "${ALL_SRC}")
