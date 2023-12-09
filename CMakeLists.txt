cmake_minimum_required(VERSION 3.22.1)

project(SimpleGUI++ VERSION 0.1.0 LANGUAGES CXX)

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/StaticAnalyzers.cmake)

add_library(
    ${PROJECT_NAME}

    # Engine
    src/eng/Engine.cpp
    src/eng/System.cpp
    src/eng/math/Angle.cpp
    src/eng/math/Random.cpp

    src/eng/event/EventHandler.cpp

    src/eng/util/Utils.cpp

    src/eng/time/TimeStep.cpp

    src/eng/gfx/Color.cpp
    src/eng/gfx/Graphics.cpp
    src/eng/gfx/Camera.cpp
    src/eng/gfx/Window.cpp
    src/eng/gfx/Renderer.cpp
    src/eng/gfx/texture/Texture.cpp
    src/eng/gfx/texture/TextureLoader.cpp
    src/eng/gfx/texture/TextureStorage.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    SYSTEM
    PRIVATE
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    -lSDL2_image
    -lm
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -Werror
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -pedantic
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wmisleading-indentation
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2
    -Wimplicit-fallthrough
)

include(test/CMakeLists.txt)
