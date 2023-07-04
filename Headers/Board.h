//
// Created by kawre on 22.05.2023.
//

#ifndef HEXXAGON_BOARD_H
#define HEXXAGON_BOARD_H

#include <SFML/Graphics.hpp>
#include <filesystem>
#include "HexagonShape.h"
#include "ChooseModeState.h"

class Board
{
 private:
    sf::RenderWindow* window;
    Team turn;
    Against against;
    StateStack& state;
    bool gameOver;
    std::pair<int, int> pawnCount;
    sf::String gameStatus;

    // Game objects
    std::unordered_map<std::string, HexagonShape> hexagons;
    HexagonShape hexagonShape;

    HexagonShape* focusedHexagon;

 public:
    Board(sf::RenderWindow*, Against, StateStack&);
    Board(sf::RenderWindow*, Against, StateStack&, const sf::String&);
    ~Board();

    void update();
    void drawTo(sf::RenderWindow*);
    void handleInput(sf::RenderWindow*, sf::Event);
    void init();

    /**
     * @brief wyznacza najlepszy możliwy ruch względem potencjalnej ilości przejęć pionków oraz odległości między source
     * @param source hexagon, dla którego chcemy znaleźć najlepszy ruch
     * @return adres hexagonu wraz z jego para ilości potencjalnych przejęć pionków i odległości między source
     */
    std::pair<HexagonShape*, std::pair<int, int>> findBestMove(HexagonShape* source);

    /**
     * @brief funkcja wykorzystuje findBestMove(), aby znaleźć najlepszy ruch, dla każdego z dostępnych pionków
     *        a następnie ponownie sortuje je według logiki z findBestMove()
     * @return para, która zawiera źródło i miejsce docelowe najlepszego dostępnego ruchu
     */
    std::pair<HexagonShape*, HexagonShape*> calculateBestComputerMove();

    void checkForGameOver();

    /**
     * @brief oznacza wszystkie hexagony, które nie posiadają pionka,
     *        jako aktywne(możliwość wykonania ruchu na to miejsce)
     * @param hexagon względem, którego chcemy zaznaczyć pobliskie hexagony
     */
    void focusNearby(HexagonShape* hexagon);
    void deFocus();

    /**
     * @brief dodaje hexagon do HashMapy(planszy)
     * @param position pozycja w układzie kartezjańskim
     * @param col,row pozycja na planszy
     */
    void append(sf::Vector2f position, int col, int row);

    /**
     * @brief określa w jaki sposób pionek ma sie poruszyć
     *        a następnie wykonuje określony ruch i wywołuje funkcje acquire
     * @param source hexagon z którego wykonujemy ruch
     * @param dest hexagon, do którego chcemy, żeby trafił pionek
     */
    void movePawn(HexagonShape* source, HexagonShape* dest);

    /**
     * @brief przejmuje wszystkie sąsiadujące pionki na korzyść drużyny przekazanego pionka
     * @param hexagon względem, którego chcemy przejąć sąsiadujące pionki
     */
    void acquire(HexagonShape* hexagon);

    std::pair<int, int> getPawnCount() const;
    sf::String getGameStatus() const;
    bool isGameOver() const;
};

#endif //HEXXAGON_BOARD_H
