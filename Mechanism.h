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
#include "Icon.h"

const bool TRUE = true;
const bool FALSE = false;

const std::string livesFilePath = {"Utils.png"};
const std::string numbersFilePath = {"Numbers.png"};
const std::string scoreFilePath = {"Score.png"};
const std::string gameOverFilePath = {"GameOver.png"};

const SDL_Rect livesRect = {0, 34, 16, 13};
const double livesWitdth = 16;
const double livesRatio = 3.5;
const SDL_Rect deadRect = {32, 34, 16, 13};
const SDL_Rect scoreRect = {0, 0, 240, 120};
const SDL_Rect gameOverRect = {0, 0, 240, 120};

const double numRatio = 1.75;
const double scoreRatio = 1.5;
const double gameOverRatio = 1.5;

const double alignLives_screen = (SCREEN_WIDTH - rightDropBorder - boulderWidth * boulderRatio) / 3; // ?

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
    bool paused;

    SDL_Event event;

    Icon pauseIcon;

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
public:
    Mechanism();
    ~Mechanism();
    void cleanUp();
    void clearVector();
    bool loadMedia(RenderWindow& p_window, const char* p_filePath);

    void handleEvent (SDL_Event &p_event, RenderWindow& p_window, Basket& basket);
    void handleEventMenu (SDL_Event &p_event, RenderWindow& p_window, Menu& p_menu);
    void handlePauseIcon (SDL_Event &p_event, RenderWindow& p_window);

    void startMenu (RenderWindow &p_window);
    void playGame(RenderWindow &p_window);
    void renderLives(RenderWindow& p_window);
    void renderScores(RenderWindow& p_window);

    void renderPauseIcon(RenderWindow& p_window);

    void renderGameOver(RenderWindow& p_window);

    int getScore();
    int getLevel();
    int getLives();

    void damn(RenderWindow& p_window);

    void updateScore();
    void updateLives();
    void updateLevel();
    void updateStartMenu(const bool &newValue);
    void updateGameRunning (const bool &newValue);
    void updateGame(Basket &p_basket, Food &p_food, RenderWindow &p_window);
};

