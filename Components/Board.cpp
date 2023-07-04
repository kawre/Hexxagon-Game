//
// Created by kawre on 22.05.2023.
//

#include <iostream>

#include "../Headers/Board.h"
#include "../Static/Theme.h"
#include "../Headers/Util.h"
#include <algorithm>
#include <fstream>
using std::pair, std::vector, std::unordered_map, std::string;

Board::Board(sf::RenderWindow* window, Against against, StateStack& state)
    : window(window), focusedHexagon(nullptr), turn(Team::Red), against(against), state(state), gameOver(false)
{
    this->init();
}

Board::Board(sf::RenderWindow* window, Against against, StateStack& state, const sf::String& path)
    : window(window), focusedHexagon(nullptr), turn(Team::Red), against(against), state(state), gameOver(false)
{
    std::fstream file(path);
    std::string line;

    while (std::getline(file, line))
    {
        int i = 0;

        std::istringstream iss(line);
        sf::Vector2f gridPos;
        sf::Vector2f pos;
        Team team;

        float n;
        while (iss >> n)
        {
            if (i == 0)
                gridPos.x = n;
            else if (i == 1)
                gridPos.y = n;
            else if (i == 2)
                pos.x = n;
            else if (i == 3)
                pos.y = n;
            else
                team = static_cast<Team>(n);

            i++;
        }

        hexagonShape.setGridPosition(gridPos.x, gridPos.y);
        hexagonShape.setPosition(pos);
        hexagonShape.setPawnTeam(team);
        hexagons[hexagonShape.getGridPositionStr()] = hexagonShape;
    }
    file.close();
}

Board::~Board()
{
    delete this->focusedHexagon;
}

void Board::drawTo(sf::RenderWindow* window)
{
    for (auto& [pos, hex] : this->hexagons)
        hex.drawTo(window);
}

void Board::append(sf::Vector2f pos, int col, int row)
{
    this->hexagonShape.setGridPosition(col, row);
    this->hexagonShape.setPosition(pos);
    this->hexagonShape.setPawnTeam(PawnShape::getTeam(col, row));

    hexagons[hexagonShape.getGridPositionStr()] = hexagonShape;
}

void Board::init()
{
    float gap = Theme::Hexagon::Gap;
    float r = Theme::Hexagon::Radius + gap;
    float h = Theme::Hexagon::Height + gap;
    int bh = Theme::BoardHeight;

    auto winSize = window->getSize();
    auto center = sf::Vector2f(winSize.x / 2.f, winSize.y / 2.f);
    float yTop = center.y - ((bh / 2) * h * 2);

    for (int col = 0; col <= bh / 2; col++)
    {
        float yStart = yTop + (h * col);
        float xDiff = col * r * 1.5;

        for (int row = 0; row < bh - col; row++)
        {
            bool isDisabled = !col && row == bh / 2 - 1 || col == 1 && row == bh / 2;
            if (isDisabled) continue;

            float yPos = yStart + (row * h * 2);
            this->append({ center.x + xDiff, yPos }, col, row);
            if (col != 0) this->append({ center.x - xDiff, yPos }, -col, row);
        }
    }
}

void Board::focusNearby(HexagonShape* hex)
{
    auto nearby = hex->findNearby(5, hexagons);
    nearby.push_back(focusedHexagon);

    for (auto h : nearby)
        if (!h->containsPawn() || focusedHexagon == h)
        {
            h->border.setColorByDist(Util::distance(hex, h));
            h->setFocused(true);
        }
}

void Board::deFocus()
{
    for (auto& [grid, hex] : this->hexagons)
        hex.setFocused(false);
}

void Board::movePawn(HexagonShape* source, HexagonShape* dest)
{
    double dist = Util::distance(source, dest);
    if (dist > Theme::Hexagon::Height * 5)
        throw ("Invalid data input");

    dest->setPawnTeam(source->getPawnTeam());

    if (dist >= Theme::Hexagon::Height * 3)
        source->setPawnTeam(None);

    this->turn = turn == Team::Red ? Team::White : Team::Red;
    acquire(dest);
}

void Board::acquire(HexagonShape* hex)
{
    for (const auto& h : hex->findNearby(3, hexagons))
        if (h->containsPawn() && hex->pawn.getTeam() != h->pawn.getTeam())
            h->pawn.setTeam(hex->pawn.getTeam());
}

void Board::handleInput(sf::RenderWindow* window, sf::Event e)
{
    if (gameOver) return;

    if (e.type == sf::Event::MouseButtonPressed)
        if (e.mouseButton.button == sf::Mouse::Left)
        {
            auto pos = sf::Mouse::getPosition(*window);

            for (auto& [grid, hex] : hexagons)
                if (hex.getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y)))
                {
                    if (focusedHexagon == &hex)
                    {
                        focusedHexagon = nullptr;
//                        deFocus();
                        break;
                    }

                    if (hex.containsPawn() && hex.pawn.getTeam() != turn) break;

                    if (focusedHexagon != nullptr)
                    {
                        if (hex.containsPawn())
                        {
                            deFocus();
                            focusedHexagon = &hex;
                        }
                        else if (!hex.isFocused())
                            focusedHexagon = nullptr;
                        else if (hex.isFocused())
                        {
                            movePawn(focusedHexagon, &hex);
                            focusedHexagon = nullptr;
                        }
                    }
                    else if (hex.containsPawn())
                        focusedHexagon = &hex;
                    break;
                }
        }

}

pair<HexagonShape*, pair<int, int>> Board::findBestMove(HexagonShape* source)
{
    vector<pair<HexagonShape*, pair<int, int>>> vector;

    for (auto hex : source->findNearby(5, hexagons))
    {
        if (hex->containsPawn()) continue;

        int count = 0;
        for (auto hexDeep : hex->findNearby(3, hexagons))
            if (hexDeep->containsPawn() && hexDeep->getPawnTeam() != source->getPawnTeam())
                count++;

        vector.push_back({ hex, { count, Util::distance(source, hex) }});
    }

    sort(vector.begin(), vector.end(), [](auto a, auto b) {
        if (a.second.first == b.second.first)
            return a.second.second < b.second.second;
        return a.second.first > b.second.first;
    });

    return !vector.empty() ? vector.front() : std::make_pair(nullptr, std::make_pair(0, 0));
}

pair<HexagonShape*, HexagonShape*> Board::calculateBestComputerMove()
{
    vector<pair<HexagonShape*, pair<HexagonShape*, pair<int, int>>>> bestMoves;

    for (auto& [pair, hex] : hexagons)
        if (hex.getPawnTeam() == Team::White)
        {
            auto bestMove = findBestMove(&hex);
            if (bestMove.first == nullptr) continue;
            bestMoves.emplace_back(&hex, findBestMove(&hex));
        }

    if (bestMoves.empty())
    {
        state.menuState();
        return { nullptr, nullptr };
    }
    else
    {
        auto comparator = [](auto a, auto b) {
            if (a.second.second.first == b.second.second.first)
                return a.second.second.second < b.second.second.second;
            return a.second.second.first > b.second.second.first;
        };

        sort(bestMoves.begin(), bestMoves.end(), comparator);
        auto best = bestMoves.front();
        return { best.first, best.second.first };
    }
}

void Board::update()
{
    checkForGameOver();

    if (focusedHexagon != nullptr) focusNearby(focusedHexagon);
    else deFocus();

    if (!gameOver && against == Against::COMPUTER && turn == Team::White)
    {
        auto bestMove = calculateBestComputerMove();
        movePawn(bestMove.first, bestMove.second);
    }

    if (gameOver)
        gameStatus = "GAME OVER";
    else
        switch (turn)
        {
        case Red:
            gameStatus = "RED TURN";
            break;
        case White:
            gameStatus = "WHITE TURN";
            break;
        }
}

void Board::checkForGameOver()
{
    int count[3] = { 0, 0, 0 };
    bool isMoveAvailable = false;

    for (auto& [grid, hex] : hexagons)
    {
        if (hex.getPawnTeam() == turn)
            isMoveAvailable |= findBestMove(&hex).first != nullptr;

        switch (hex.getPawnTeam())
        {
        case None:
            count[0]++;
            break;
        case Red:
            count[1]++;
            break;
        case White:
            count[2]++;
            break;
        }
    }

    pawnCount.first = count[1];
    pawnCount.second = count[2];

    if (!isMoveAvailable
        || count[0] == 0
        || count[1] == 0 || count[2] == 0
        || count[1] + count[2] == 58)
    {
        gameOver = true;
    }
}

pair<int, int> Board::getPawnCount() const
{
    return pawnCount;
}

sf::String Board::getGameStatus() const
{
    return gameStatus;
}

bool Board::isGameOver() const
{
    return gameOver;
}
