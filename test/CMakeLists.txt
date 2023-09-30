find_package(Catch2 3 REQUIRED)

include(CTest)
include(Catch)

add_executable(
    TestSimpleGUI++
    test/eng/math/TestAngle.cpp
)

target_link_libraries(
    TestSimpleGUI++
    ${SDL2_LIBRARIES}
    -lSDL2_image
    -lm
    Catch2::Catch2WithMain
)

catch_discover_tests(TestSimpleGUI++)
