#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "Background.h"
#include "VectorMath.h"
#include "Food.h"
#include "Basket.h"
#include "Mechanism.h"

Mechanism::Mechanism() {
    score = 0;
    lives = 3;
    level = 1;
}

void Mechanism::handleEvent(SDL_Event &p_event, RenderWindow& p_window, Basket& basket) {
    while (SDL_PollEvent(&p_event)) {
        if (p_event.type == SDL_QUIT) {
            gameRunning = false;
        }
        else if (currentKeyStates[ SDL_SCANCODE_LEFT ]) {
            key = 'L';
            basket.basketMove(p_window, key);
            std::cout << "LEFT" << std::endl;

        }
        else if (currentKeyStates[ SDL_SCANCODE_RIGHT ]) {
            key = 'R';
            basket.basketMove(p_window, key);
            std::cout << "RIGHT" << std::endl;

        }
        else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            std::cout << "DOWN" << std::endl;
            gameRunning = false;
        }
    }
}

void Mechanism::playGame(RenderWindow& p_window) {

    frameStart = SDL_GetTicks();

    SDL_Event event;

    Background background;

    Food food;

    Basket basket;



    while (gameRunning) {

        p_window._clear();

        background.renderGrassBackground(p_window);
        background.renderDropAreaBackground(p_window);
        background.renderDropArea(p_window);

        handleEvent(event, p_window, basket);

        basket.basketRender(p_window);

        //food.randomFoodRender(p_window);

        p_window.display();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}


