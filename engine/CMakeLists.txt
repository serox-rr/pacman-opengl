cmake_minimum_required(VERSION 3.28)
project(engine VERSION 0.0.1)

file(GLOB_RECURSE MDLS *.cppm)
file(GLOB_RECURSE SRCS *.cpp)

add_library(engine STATIC)

target_sources(engine PUBLIC ${SRCS})
target_sources(engine PUBLIC FILE_SET CXX_MODULES FILES ${MDLS})

set_property(TARGET engine PROPERTY CXX_STANDARD 23)


include(FetchContent)

FetchContent_Declare(
    fastnoise
    GIT_REPOSITORY https://github.com/Auburn/FastNoise2.git
    GIT_TAG        v0.10.0-alpha
)

FetchContent_MakeAvailable(fastnoise)
set(FASTNOISE2_NOISETOOL OFF CACHE BOOL "Build Noise Tool" FORCE)

find_package(Freetype REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(assimp CONFIG REQUIRED)
target_link_libraries(engine PUBLIC glfw glad::glad glm::glm FastNoise Freetype::Freetype assimp::assimp)
target_include_directories(engine PUBLIC ${Stb_INCLUDE_DIR})
