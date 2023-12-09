find_package(Catch2 3 REQUIRED)

include(CTest)
include(Catch)

add_executable(
    TestSimpleGUI++

    src/eng/math/Vector2.hpp
    src/eng/math/Vector2format.hpp
    src/eng/math/Angle.hpp
    src/eng/math/Angle.cpp
    src/eng/System.cpp
    src/eng/gfx/Graphics.cpp
    src/eng/gfx/texture/Texture.cpp
    src/eng/gfx/texture/TextureStorage.cpp
    src/eng/gfx/texture/TextureLoader.cpp
    src/eng/gfx/Window.cpp
    src/eng/gfx/Renderer.cpp
    src/eng/gfx/Camera.cpp
    src/eng/gfx/Color.cpp
    src/eng/util/Utils.cpp

    test/eng/math/TestAngle.cpp
    test/eng/math/TestVector.cpp
    test/eng/math/TestVectorFormat.cpp
    test/eng/gfx/TestGraphics.cpp
)

target_link_libraries(
    TestSimpleGUI++
    ${SDL2_LIBRARIES}
    -lSDL2_image
    -lm
    Catch2::Catch2WithMain
)

catch_discover_tests(TestSimpleGUI++)
