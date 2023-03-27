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
    lives = MAX_LIVES;
    level = 1;


    startGame = true;
    gameRunning = true;
}

Mechanism::~Mechanism() {
    cleanUp();
}

void Mechanism::clearVector() {
    utilsEntities.clear();
}

void Mechanism::cleanUp() {
    SDL_DestroyTexture(loadUtils);
    loadUtils = nullptr;
    clearVector();
}

bool Mechanism::loadMedia(RenderWindow &p_window, const char* p_filePath) {
    if (loadUtils == nullptr) {
        loadUtils = p_window.loadTexture(p_filePath);
    }
    if (loadUtils == nullptr) {
        std::cout << "Unable to load Utils IMG. Error: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;

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
    }
}


void Mechanism::startMenu(RenderWindow &p_window) {

    frameStart = SDL_GetTicks();

    Menu menu;

    while (startGame) {

        p_window._clear();

        background.renderGrassBackground(p_window);

        menu.renderDefaultMenu(p_window);


        if (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT || currentKeyStates[SDL_SCANCODE_UP]) {
                    std::cout << "STOP MENU" << std::endl;
                    startGame = false;
                }
                else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {

                    p_window._clear();
                    background.renderGrassBackground(p_window);

                    menu.renderMenu(p_window, event);

                    if (menu.play) {
                        playGame(p_window);
                    }

                }

        }


        p_window.display();



        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

}




void Mechanism::playGame(RenderWindow& p_window) {
    frameStart = SDL_GetTicks();

    std::vector<Food> food(1);

    background.cleanBackground();

    Basket basket;

    int more = 2;

    std::clock_t start, now;
    start = std::clock();

    while (gameRunning) {
        p_window._clear();

        background.renderGrassBackground(p_window);
        background.renderDropAreaBackground(p_window);
        background.renderDropArea(p_window);

        now = std::clock();

        double duration = double(now - start) / double(CLOCKS_PER_SEC);

        //std::cout << "NOW: " << now << " DURATION: " << duration << std::endl;

        if (duration >= 15 && more > 0) {
            if (level == 1 && food[0].getFoodPos().y >= 300 && food[0].getFoodPos().y <= 350) {
                std::cout << "FOOD 0 POS Y: " << food[0].getFoodPos().y << std::endl;
                std::cout << "NOW: " << now << " DURATION: " << duration << std::endl;
                Food newFood;
                food.push_back(newFood);
                start = std::clock();
                more--;
            }
            else if ( level == 3 && food[1].getFoodPos().y >= 200 && food[1].getFoodPos().y <= 300) {
                std::cout << "FOOD 1 POS Y: " << food[1].getFoodPos().y << std::endl;
                std::cout << "NOW: " << now << " DURATION: " << duration << std::endl;
                Food newFood;
                food.push_back(newFood);
                start = std::clock();
                more--;
            }
        }


        handleEvent(event, p_window, basket);

        basket.basketRender(p_window);

        renderLives(p_window);
        renderScores(p_window);

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

    renderLives(p_window);

    food.clear();
}

void Mechanism::renderLives(RenderWindow& p_window) {
    cleanUp();

    loadMedia(p_window, livesFilePath.c_str());

    int currentLives = lives;
    for (int i = 0; i < MAX_LIVES; i++) {
        if (currentLives > 0) {
            utilsEntities.push_back(Entity(VectorMath(rightDropBorder + alignLives_screen + i *  livesWitdth * livesRatio, SCREEN_HEIGHT / 2), livesRect, loadUtils));
            currentLives--;
        }
        else utilsEntities.push_back(Entity(VectorMath(rightDropBorder + alignLives_screen + i *  livesWitdth * livesRatio, SCREEN_HEIGHT / 2), deadRect, loadUtils));
    }


    for (Entity& e : utilsEntities) {
        p_window.render(e, livesRatio);
    }

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
        startGame = false;
    }
}

void Mechanism::renderScores(RenderWindow& p_window) {
    std::vector<int> seperatedScores;
    int currentScores = score;
    if (currentScores == 0) seperatedScores.push_back(0);
    else while (currentScores) {
        seperatedScores.push_back(currentScores % 10);
        currentScores /= 10;
    }
    std::reverse(seperatedScores.begin(), seperatedScores.end());

    cleanUp();

    loadUtils = p_window.loadTexture(numbersFilePath.c_str());

    int index = 0;
    for (int& i : seperatedScores) {
        SDL_Rect numRect = {i * 40, 0, 40, 40};
        utilsEntities.push_back(Entity(VectorMath(500 + index * 40, 100), numRect, loadUtils));
        index++;
    }

    for (Entity& e : utilsEntities) {
        p_window.render(e, numRatio);
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

