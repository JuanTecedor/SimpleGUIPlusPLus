#include "game/Game.hpp"

#include <filesystem>

int main()
{
    TextureStorage::TexturePaths texture_paths = {
        { "red", "red.png" }
    };
    std::filesystem::path base_path = "res";
    EngineConfig engine_config = {
        .app_name="SimpleGUI++",
        .texture_config={
            .base_path=base_path,
            .texture_paths=texture_paths
        }
    };
    Game game{engine_config};
    game.run();
}
