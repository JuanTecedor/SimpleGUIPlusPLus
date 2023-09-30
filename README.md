# SimpleGUIPlusPLus

This is a simple C++ engine built on top of SDL2. It also features useful mathematical operations as the ones supplied by Vector2.

## Features:
- C++20, using a lot of modern C++ features for safety: std::filesystem, <=>, inline variables, nodiscard, constexpr, structured bindings, std::variant, auto, using, etc.
- SDL2
- Catch2 testing with separate executable.
- CMake with prevention of building in source, clang-tidy, cppcheck and Catch2 integration.
- Integration with GitHub's actions.
- Separate debug/release application and test executables.

## Structure:
- Drawing module:
    - Textures:
        - Loading textures from a file, including PNG
        - Fill screen with texture, custom size texture, rotating textures
        - Transparency
        - Automatic RAII of textures, no resources are leaked! Flyweight pattern, texture storage owns the textures.
        - Default error texture.
    - Primitives:
        - Point
        - Line
        - Rectangle
        - Filled Rectangle
        - Circle
        - Color
    - Transformations:
        - Screen to world
        - World to screen
        - Camera panning
- Math module:
    - Angle: Allows for the conversion between radians and degrees as well as adding angles.
    - Vector2 (templated): Mathematical 2D vector, supports many operations: Add, subtract, scale, length, dot product, angles, projections, etc.
- Component module: Some of these components build on top of Vector2
    - Direction
    - Position
    - PositionF
- Time module:
    - TimeStep: Makes the engine run at predictable and reproducible speeds (FPS lock). Offers delta time variable for physics calculations.
- Event module:
    - Event: Based on a type-safe std::variant. Each event has its own data: ExitEvent has none while MoveCameraEvent has a Direction member.
    - EventHandler: Handles the SDL_Events and returns a std::vector with the list of events.
