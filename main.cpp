#include "Headers/Game.h"
#include "Static/Theme.h"
#include <filesystem>

int main()
{
    if (!Theme::Font.loadFromFile(R"(..\Static\Fonts\FiraCode-Medium.ttf)"))
        return EXIT_FAILURE;

    Game game;
    while (game.running())
    {
        game.pollEvents();
        game.update();
        game.render();
    }

    return EXIT_SUCCESS;
}