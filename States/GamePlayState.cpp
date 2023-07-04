//
// Created by kawre on 23.05.2023.
//

#include <fstream>
#include "../Headers/GamePlayState.h"
#include "../Static/Theme.h"

GamePlayState::GamePlayState(sf::RenderWindow* window, StateStack& state, Against against)
    : window(window), board(window, against, state), state(state), redCount("3", Theme::Font, 24), gameOver(false),
      whiteCount("3", Theme::Font, 24), gameStatus("RED TURN", Theme::Font, 24), time("0:00", Theme::Font, 24)
{
    initQuitButton();
    initCountTexts();
    initStatusText();
    initTimeText();
}

GamePlayState::GamePlayState(sf::RenderWindow* window, StateStack& state,
    Against against, const sf::String& path)

    : window(window), board(window, against, state, path), state(state), redCount("3", Theme::Font, 24), gameOver(false),
      whiteCount("3", Theme::Font, 24), gameStatus("RED TURN", Theme::Font, 24), time("0:00", Theme::Font, 24)
{
    initQuitButton();
    initCountTexts();
    initStatusText();
    initTimeText();
}

void GamePlayState::handleEvents(sf::Event& e)
{
    board.handleInput(window, e);
    quitButton.handleInput(window, e);
}

void GamePlayState::update()
{
    board.update();

    auto count = board.getPawnCount();
    redCount.setString(std::to_string(count.first));
    whiteCount.setString(std::to_string(count.second));

    gameStatus.setString(board.getGameStatus());
    auto fillColor =
        board.getGameStatus() == "GAME OVER" ? sf::Color::White :
        board.getGameStatus() == "RED TURN" ? Theme::RedPawn : Theme::WhitePawn;
    gameStatus.setFillColor(fillColor);

    auto winSize = window->getSize();
    float margin = Theme::Hexagon::Radius;

    auto statusRect = gameStatus.getGlobalBounds();
    auto statusLocal = gameStatus.getLocalBounds();
    gameStatus.setPosition({ winSize.x - statusRect.width - statusLocal.left - margin,
                             winSize.y - statusRect.height - statusLocal.top - margin });

    if (board.isGameOver() && !gameOver)
    {
        saveToScores();
        gameOver = true;
    }

    if (!board.isGameOver())
    {
        sf::Time elapsed = clock.getElapsedTime();
        int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
        int seconds = static_cast<int>(elapsed.asSeconds()) % 60;
        std::stringstream ss;
        ss << minutes << ":" << std::setfill('0') << std::setw(2) << seconds;
        time.setString(ss.str());
    }
}

void GamePlayState::render()
{
    // Change background
    window->clear(Theme::Background);

    // Draw board
    board.drawTo(window);
    quitButton.drawTo(window);

    window->draw(whiteCount);
    window->draw(redCount);
    window->draw(gameStatus);
    window->draw(time);

    // Display
    window->display();
}

void GamePlayState::initQuitButton()
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

void GamePlayState::initCountTexts()
{
    float margin = Theme::Hexagon::Radius;

    redCount.setFillColor(Theme::RedPawn);
    redCount.setPosition({ margin, margin });

    whiteCount.setFillColor(Theme::WhitePawn);
    whiteCount.setPosition({ margin, margin + Theme::Hexagon::Radius });
}

void GamePlayState::initStatusText()
{
    time.setPosition({ (window->getSize().x - 90) / 1.f,
                       Theme::Hexagon::Radius - 4 });
}

void GamePlayState::initTimeText()
{
    time.setFillColor(sf::Color::White);
}

void GamePlayState::saveToScores()
{
    std::fstream file;
    file.open(R"(../scores.txt)", std::ios_base::app | std::ios_base::in);

    int winner = board.getPawnCount().first >= board.getPawnCount().second ? 1 : 2;
    file << winner << " "
         << board.getPawnCount().first << " " << board.getPawnCount().second << " "
         << time.getString().toAnsiString() << "\n";

    file.close();
}
