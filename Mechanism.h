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
#include "Const_Vars.h"

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
    Icon musicIcon;

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
public:
    Mechanism();
    ~Mechanism();
    void cleanUp();
    void clearVector();
    bool loadMedia(RenderWindow& p_window, const char* p_filePath);

    void handleEvent (SDL_Event &p_event, RenderWindow& p_window, Basket& basket);
    void handleEventMenu (SDL_Event &p_event, RenderWindow& p_window, Menu& p_menu);
    void handleIcon (SDL_Event &p_event, RenderWindow& p_window);

    void startMenu (RenderWindow &p_window);
    void playGame(RenderWindow &p_window);
    void renderLives(RenderWindow& p_window);
    void renderScores(RenderWindow& p_window);

    void renderIcon(RenderWindow& p_window);

    void renderGameOver(RenderWindow& p_window);

    int getScore();
    int getLevel();
    int getLives();

    void playAgain(RenderWindow& p_window);

    void updateScore();
    void updateLives();
    void updateLevel();
    void updateStartMenu(const bool &newValue);
    void updateGameRunning (const bool &newValue);
    void updateGame(Basket &p_basket, Food &p_food, RenderWindow &p_window);
};

