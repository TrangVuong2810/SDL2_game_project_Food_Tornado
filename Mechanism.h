#pragma once

#include <bits/stdc++.h>
#include <chrono>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "Background.h"
#include "VectorMath.h"
#include "Food.h"
#include "Basket.h"
#include "Menu.h"
#include "Button.h"

const bool TRUE = true;
const bool FALSE = false;

const std::string livesFilePath = {"Utils.png"};
const std::string numbersFilePath = {"Numbers.png"};

const SDL_Rect livesRect = {0, 34, 16, 13};
const double livesWitdth = 16;
const double livesRatio = 3.5;
const SDL_Rect deadRect = {32, 34, 16, 13};

const double numRatio = 1;

const double alignLives_screen = (SCREEN_WIDTH - rightDropBorder - boulderWidth * boulderRatio) / 3;

const int MAX_LIVES = 3;

class Mechanism {
private:
    int lives;
    int score;
    int level;

    Background background;

    std::vector<Entity> utilsEntities;
    SDL_Texture* loadUtils = nullptr;

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
    ~Mechanism();
    void cleanUp();
    void clearVector();
    bool loadMedia(RenderWindow& p_window, const char* p_filePath);
    void handleEvent (SDL_Event &p_event, RenderWindow& p_window, Basket& basket);
    void handleEventMenu (SDL_Event &p_event, RenderWindow& p_window, Menu& p_menu);
    void startMenu (RenderWindow &p_window);
    void playGame(RenderWindow &p_window);
    void renderLives(RenderWindow& p_window);
    void renderScores(RenderWindow& p_window);

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

