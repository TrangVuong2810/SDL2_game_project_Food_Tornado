#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "Background.h"
#include "VectorMath.h"
#include "Food.h"
#include "Basket.h"
#include "Mechanism.h"
#include "Button.h"
#include "Menu.h"

Mechanism::Mechanism() {
    score = 0;
    lives = 3;
    level = 1;


    startGame = true;
    gameRunning = true;
}

void Mechanism::handleEvent(SDL_Event &p_event, RenderWindow& p_window, Basket& basket) {
    while (SDL_PollEvent(&p_event)) {
        if (p_event.type == SDL_QUIT) {
            gameRunning = false;
            startGame = false;
            //p_window.cleanUp();
        }
        else if (currentKeyStates[ SDL_SCANCODE_LEFT ]) {
            key = 'L';
            basket.basketMove(p_window, key);
            //std::cout << "LEFT" << std::endl;

        }
        else if (currentKeyStates[ SDL_SCANCODE_RIGHT ]) {
            key = 'R';
            basket.basketMove(p_window, key);
            //std::cout << "RIGHT" << std::endl;

        }
        else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            std::cout << "DOWN" << std::endl;
            startGame = false;
            gameRunning = false;
        }
        else if (currentKeyStates[SDL_SCANCODE_UP]) {
            std::cout << "UP ~ START" << std::endl;
            playGame(p_window);
        }
    }
}

void Mechanism::handleEventMenu(SDL_Event& p_event, RenderWindow& p_window, Menu& p_menu) {

    //p_menu.renderMenu(p_window, p_event);

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || currentKeyStates[SDL_SCANCODE_UP]) {
            std::cout << "STOP MENU" << std::endl;
            startGame = false;

        }
        else {
            p_menu.renderMenu(p_window, p_event);
        }
    }


}

void Mechanism::startMenu(RenderWindow &p_window) {

    frameStart = SDL_GetTicks();

    Background backgroundTemp;


    Menu menu;

    while (startGame) {

        p_window._clear();

        backgroundTemp.renderGrassBackground(p_window);

        menu.renderMenu(p_window, event);


        //if (!(SDL_PollEvent(&event) != 0))  menu.renderMenu(p_window, event);
        //else {
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT || currentKeyStates[SDL_SCANCODE_UP]) {
                    std::cout << "STOP MENU" << std::endl;
                    startGame = false;
                }
                else {
                    p_window._clear();
                    backgroundTemp.renderGrassBackground(p_window);

                    menu.renderMenu(p_window, event);
                }
            }
        //}

        //else



        //handleEventMenu(event, p_window, menu);

        p_window.display();



        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

}




void Mechanism::playGame(RenderWindow& p_window) {
    frameStart = SDL_GetTicks();

    Background background;

    std::vector<Food> food(1);

    Basket basket;

    while (gameRunning) {

        p_window._clear();


        background.renderGrassBackground(p_window);
        background.renderDropAreaBackground(p_window);
        background.renderDropArea(p_window);


        handleEvent(event, p_window, basket);

        basket.basketRender(p_window);



        for (Food &f : food) {
            f.foodDrop(p_window, TRUE, level);
        }

        for (Food &f : food) {
            updateGame(basket, f, p_window);
        }

        p_window.display();


        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    food.clear();
}


void Mechanism::updateGame(Basket &p_basket, Food &p_food, RenderWindow &p_window) {
    if (p_food.getFoodPos().y >= p_basket.getBasketPos().y) {
       if (p_food.getFoodPos().x >= p_basket.getBasketPos().x && p_food.getFoodPos().x + MAX_FOOD_WIDTH * foodRatio <= p_basket.getBasketPos().x + basketWidth *basketRatio
            && p_food.getFoodPos().y + MAX_FOOD_HEIGHT * foodRatio < bottomDropBorder) {
            updateScore();
            updateLevel();
            std::cout << "SCORE: " << score << std::endl << "LEVEL: " << level << std::endl;
            p_food.foodDrop(p_window, FALSE, level);
        }
        else if (p_food.getFoodPos().y >= bottomDropBorder - MAX_FOOD_HEIGHT * foodRatio) {
            updateLives();
            std::cout << "LIVES: " << lives << std::endl << "LEVEL: " << level << std::endl;
            p_food.foodDrop(p_window, FALSE, level);
        }
    }


    if (lives == 0) {
        std::cout << "GAME OVER" << std::endl;
        gameRunning = false;
    }
}

int Mechanism::getScore() {
    return score;
}
int Mechanism::getLevel() {
    return level;
}
int Mechanism::getLives() {
    return lives;
}
void Mechanism::updateScore() {
    score += 1;
}
void Mechanism::updateLives() {
    lives -= 1;
}

void Mechanism::updateStartMenu(const bool& newValue) {
    startGame = newValue;
}

void Mechanism::updateGameRunning(const bool& newValue) {
    gameRunning = newValue;
}


void Mechanism::updateLevel() {
    if (score == 10) {
        level += 1; //2
        std::cout << "LEVEL: " << level << std::endl;
    }
    else if (score == 20) {
        level += 1; //3
        std::cout << "LEVEL: " << level << std::endl;
    }
}

