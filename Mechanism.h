#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "Background.h"
#include "VectorMath.h"
#include "Food.h"
#include "Basket.h"


class Mechanism {
private:
    int lives;
    int score;
    int level;

    char key;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    bool gameRunning = true;

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
public:
    Mechanism();
    void handleEvent (SDL_Event &p_event, RenderWindow& p_window, Basket& basket);
    void playGame(RenderWindow &p_window);




};
