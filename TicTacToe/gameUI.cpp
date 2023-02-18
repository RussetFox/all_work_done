#include "gameUI.h"
#include "gameHandling.h"


GameUI:: GameUI() {
    appWindow.create(VideoMode(883, 621), "Tic Tac Toe");
    appWindow.setFramerateLimit(60);
    appWindow.setKeyRepeatEnabled(false);
    appWindow.setVerticalSyncEnabled(true);

    //__________________LOAD ASSETS__________________
    playbutton.loadFromFile("playbutton.png");
    xmark.loadFromFile("xmark.png");
    omark.loadFromFile("omark.png");
    title.loadFromFile("Napis.png");
    gamescreen3.loadFromFile("board.png");
    winscreeno.loadFromFile("owin.png");
    winscreenx.loadFromFile("xwin.png");
    tiescreen.loadFromFile("tie.png");
    diffscreen.loadFromFile("difficulty.png");

    //__________________SPRITE ASSETS__________________
    gametitle.setTexture(title);
    button.setTexture(playbutton);
    board3.setTexture(gamescreen3);
    x.setTexture(xmark);
    o.setTexture(omark);
    xwin.setTexture(winscreenx);
    owin.setTexture(winscreeno);
    tie.setTexture(tiescreen);
    diffs.setTexture(diffscreen);

    //__________________SPRITE SIZES__________________
    gametitle.setTextureRect(IntRect(0, 0, 684, 185));
    button.setTextureRect(IntRect(0,0,142,138));
    board3.setTextureRect(IntRect(0,0,883,621));
    x.setTextureRect(IntRect(0,0,200,200));
    o.setTextureRect(IntRect(0,0,200,200));
    xwin.setTextureRect(IntRect(0,0,883,621));
    owin.setTextureRect(IntRect(0,0,883,621));
    tie.setTextureRect(IntRect(0,0,883,621));
    diffs.setTextureRect(IntRect(0,0,883,621));
    //__________________SPRITE POSITIONS__________________
    gametitle.setPosition(100, 10);
    button.setPosition(350, 300);
    board3.setPosition(0, 0);
    xwin.setPosition(0,0);
    owin.setPosition(0,0);
    tie.setPosition(0,0);

    //_________________Initial Values__________________
    playscreen = 1;
    clickx = 0;
    clicky = 0;
}


void GameUI::mouseClickEvent() {
        switch (playscreen) {
            case 1: {
                if (clickx > 340 && clickx < 500 && clicky > 290 && clicky < 450) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    playscreen = 6;
                }
                break;
            }
            case 2: {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (clickx > 294 * j && clickx < 294 + j * 294 && clicky > 207 * i && clicky < 207 + i * 207 &&
                            !getTurn() && getGameboard(i, j) == 0) {
                            setGameboard(i, j, 3);
                            setTurn();
                        }
                    }
                    }
                break;
            }
            case 3: {
                if (clickx > 123 && clickx < 663 && clicky > 335 && clicky < 473) {
                    playscreen = 1;
                    resetStats();
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                }
                break;
            }
            case 4:{
                if (clickx > 123 && clickx < 663 && clicky > 335 && clicky < 473) {
                    playscreen = 1;
                    resetStats();
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                }
                break;
            }
            case 5:{
                if (clickx > 123 && clickx < 663 && clicky > 335 && clicky < 473) {
                    playscreen = 1;
                    resetStats();
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                }
                break;
            }
            case 6:{
                if (clickx > 86 && clickx < 346 && clicky > 336 && clicky < 433) {
                    setDifficulty(1);
                    playscreen = 2;
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                }
                else if (clickx > 430 && clickx < 686 && clicky > 336 && clicky < 433) {
                    setDifficulty(2);
                    playscreen = 2;
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                }
                break;
            }
        }
    }
void GameUI:: showScreen() {
    switch (playscreen) {
        case 1: {
            appWindow.draw(gametitle);
            appWindow.draw(button);
            break;
        }
        case 2: {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (getGameboard(i, j) == 2) {
                        x.setPosition(294 * j, 207 * i);
                        appWindow.draw(x);
                    } if (getGameboard(i, j) == 3) {
                        o.setPosition(294 * j, 207 * i);
                        appWindow.draw(o);
                    }
                }
            }
            appWindow.draw(board3);
            break;
        }
        case 3:{
            appWindow.draw(xwin);
            break;
        }
        case 4:{
            appWindow.draw(owin);
            break;
        }
        case 5:{
            appWindow.draw(tie);
            break;
        }
        case 6: {
            appWindow.draw(diffs);
            break;
        }
    }
    appWindow.display();
}


void GameUI::runGame() {
    int helpb[3][3];
    while (appWindow.isOpen()) {
        appWindow.clear(Color::Blue);
        while (appWindow.pollEvent(appEvent)) {
            if (appEvent.type == Event::Closed)
                appWindow.close();
        }
        if (appEvent.type == Event::MouseMoved) {
            clickx = appEvent.mouseMove.x;
            clicky = appEvent.mouseMove.y;
        }
        if(appEvent.type == Event:: MouseButtonReleased) {
            mouseClickEvent();
        }
        if (playscreen == 2 && getTurn() && getResult() != 1 && getResult() != 2 && getResult() != 3) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    helpb[i][j] = getGameboard(i, j);
                }
                }
               Move bestMove = findBestMove(helpb);
                setGameboard(bestMove.row, bestMove.col, 2);
                setTurn();
            }
        showScreen();
        switch (getResult()) {
            case 1: {
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                playscreen = 3;
                break;
            }
            case 2: {
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                playscreen = 4;
                break;
            }
            case 3: {
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                playscreen = 5;
                break;
            }
        }
    }
}

GameUI:: ~GameUI() = default;