//
// Created by kawre on 28.05.2023.
//

#include "../Headers/BestScoresState.h"
#include "../Static/Theme.h"
#include <fstream>
#include <sstream>

BestScoresState::BestScoresState(sf::RenderWindow* window, StateStack& state)
    : window(window), state(state)
{
    score.setSize({ window->getSize().x - 80.f, 75 });
    loadScores();
    initQuitButton();
}

void BestScoresState::handleEvents(sf::Event& e)
{
    quitButton.handleInput(window, e);
}

void BestScoresState::update()
{
}

void BestScoresState::render()
{
    window->clear(Theme::Background);

    quitButton.drawTo(window);
    for (int i = 0; i < std::min(5, static_cast<int>(scores.size())); ++i)
    {
        scores.at(i).setPosition({ 40, 150 + (i * 100.f) });
        scores.at(i).drawTo(window);
    }

    window->display();
}

void BestScoresState::initQuitButton()
{
    auto winSize = window->getSize();

    quitButton.setFont(Theme::Font);
    quitButton.setTextSize(24);
    quitButton.setText("QUIT");

    float padding = 15;
    quitButton.setPadding({ padding, padding * 0.75f });

    auto qbtnRect = quitButton.getGlobalBounds();
    float margin = Theme::Hexagon::Radius;
    quitButton.setPosition({ qbtnRect.width / 2.f + margin, winSize.y - qbtnRect.height / 2.f - margin });

    quitButton.addCallback(sf::Event::MouseButtonPressed, sf::Mouse::Left,
        [&]() {
            state.menuState();
        });
}

void BestScoresState::loadScores()
{
    std::fstream file(R"(../scores.txt)");
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        float team;
        iss >> team;

        float yourCount;
        iss >> yourCount;

        float enemyCount;
        iss >> enemyCount;

        std::string time;
        iss >> time;

        score.setTeam(static_cast<Team>(team));
        score.setMovesCount(sf::Vector2i(yourCount, enemyCount));
        score.setTime(time);

        scores.push_back(score);
    }

    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return a.getMovesCount().x < b.getMovesCount().x;
    });
}
