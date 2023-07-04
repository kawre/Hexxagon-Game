cmake_minimum_required(VERSION 3.25)

project(Hexxagon)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cpp States/Game.cpp Headers/Game.h Shapes/HexagonShape.cpp Headers/HexagonShape.h Shapes/PawnShape.cpp Headers/PawnShape.h Headers/Team.h Shapes/BorderShape.cpp Headers/BorderShape.h Static/Theme.h Static/Util.cpp Headers/Util.h Components/Board.cpp Headers/Board.h Headers/State.h States/MenuState.cpp Headers/MenuState.h States/GamePlayState.cpp Headers/GamePlayState.h Components/TextBox.cpp Headers/TextBox.h Components/Button.cpp Headers/Button.h States/ChooseModeState.cpp Headers/ChooseModeState.h States/StateStack.cpp Headers/StateStack.h Components/RadioButton.cpp Headers/RadioButton.h States/BestScoresState.cpp Headers/BestScoresState.h Headers/Score.h Components/Score.cpp States/LoadGameState.cpp Headers/LoadGameState.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics network REQUIRED)
include_directories(C:/SFML/include)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)