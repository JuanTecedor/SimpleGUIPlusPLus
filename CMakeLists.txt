cmake_minimum_required(VERSION 3.22.1)

project(SimpleGUI++ VERSION 0.1.0 LANGUAGES CXX)

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/StaticAnalyzers.cmake)

add_executable(
    ${PROJECT_NAME}
    src/Main.cpp

    # Engine
    src/eng/EngineConfig.hpp
    src/eng/Engine.hpp
    src/eng/Engine.cpp
    src/eng/System.hpp
    src/eng/System.cpp

    src/eng/math/Vector2.hpp
    src/eng/math/Angle.hpp
    src/eng/math/Angle.cpp

    src/eng/event/Event.hpp
    src/eng/event/EventHandler.hpp
    src/eng/event/EventHandler.cpp

    src/eng/util/Utils.hpp
    src/eng/util/Utils.cpp

    src/eng/time/TimeStep.hpp
    src/eng/time/TimeStep.cpp

    src/eng/gfx/Camera.hpp
    src/eng/gfx/Color.hpp
    src/eng/gfx/Color.cpp
    src/eng/gfx/Graphics.hpp
    src/eng/gfx/Graphics.cpp
    src/eng/gfx/Window.hpp
    src/eng/gfx/Window.cpp
    src/eng/gfx/Renderer.hpp
    src/eng/gfx/Renderer.cpp
    src/eng/gfx/GraphicsPrimitives.hpp
    src/eng/gfx/texture/Texture.hpp
    src/eng/gfx/texture/Texture.cpp
    src/eng/gfx/texture/TextureLoader.hpp
    src/eng/gfx/texture/TextureLoader.cpp
    src/eng/gfx/texture/TextureStorage.hpp
    src/eng/gfx/texture/TextureStorage.cpp

    src/eng/component/Position.hpp
    src/eng/component/PositionF.hpp
    src/eng/component/Direction.hpp

    # Game
    src/game/Game.hpp
    src/game/Game.cpp
    src/game/World.hpp
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
