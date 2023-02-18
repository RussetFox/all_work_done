#ifndef TICTACTOE_GAMEUI_H
#define TICTACTOE_GAMEUI_H

#include "gameHandling.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

using namespace sf;

class GameUI : public gameHandling {
    RenderWindow appWindow;
    Event appEvent;
    Texture playbutton, gamescreen3, table, xmark, omark, title, winscreenx, winscreeno, tiescreen, diffscreen;
    Sprite gametitle, button, board3, x, o, xwin, owin, tie, diffs;
    int playscreen, clickx, clicky;
public:
    GameUI();
    ~GameUI();
    void runGame();
    void showScreen();
    void mouseClickEvent();
};

#endif //TICTACTOE_GAMEUI_H
