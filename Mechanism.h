#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//#include "RenderWindow.h"
#include "Entity.h"
#include "Background.h"
#include "VectorMath.h"
//#include "Food.h"
//#include "Basket.h"
#include "Text.h"
#include "Menu.h"
#include "Button.h"

const bool TRUE = true;
const bool FALSE = false;

class Food;
class Basket;
class RenderWindow;
//class Background;
class Mechanism {
private:
    int lives;
    int score;
    int level;

    //Background backgroun1;

    char key;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    bool startGame;
    bool gameRunning;

    SDL_Event event;

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
public:
    Mechanism();
    void handleEvent (SDL_Event &p_event, RenderWindow& p_window, Basket& basket);
    void handleEventMenu (SDL_Event &p_event, RenderWindow& p_window, Menu& p_menu);
    void startMenu (RenderWindow &p_window);
    void playGame(RenderWindow &p_window);
    //void cleanUp();
    int getScore();
    int getLevel();
    int getLives();
    void updateScore();
    void updateLives();
    void updateLevel();
    void updateStartMenu(const bool &newValue);
    void updateGameRunning (const bool &newValue);
    void updateGame(Basket &p_basket, Food &p_food, RenderWindow &p_window);
};
