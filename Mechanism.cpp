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
#include "Icon.h"

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
        if (p_event.type == SDL_QUIT || currentKeyStates[SDL_SCANCODE_ESCAPE]) {
            gameRunning = false;
            startGame = false;
            p_window.wait = false;
        }
        else if (currentKeyStates[ SDL_SCANCODE_LEFT ]) {
            key = 'L';
            basket.basketMove(p_window, key);
        }
        else if (currentKeyStates[ SDL_SCANCODE_RIGHT ]) {
            key = 'R';
            basket.basketMove(p_window, key);
        }
        else {//if (p_event.type == SDL_MOUSEMOTION || p_event.type == SDL_MOUSEBUTTONDOWN || p_event.type == SDL_MOUSEBUTTONUP) {
            handlePauseIcon (p_event, p_window);
        }
    }
    //else handlePauseIcon(p_event, p_window);
}


void Mechanism::startMenu(RenderWindow &p_window) {
    frameStart = SDL_GetTicks();

    Menu menu;

    while (startGame) {

        p_window._clear();

        background.renderGrassBackground(p_window);

        menu.renderDefaultMenu(p_window);


        if (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT || currentKeyStates[SDL_SCANCODE_ESCAPE]) {
                startGame = false;
                gameRunning = false;
                p_window.wait = false;
                cleanUp();
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

void Mechanism::handlePauseIcon (SDL_Event& p_event, RenderWindow& p_window) {
    if (pauseIcon.isInside(p_event)) {
        switch (p_event.type) {
        case SDL_MOUSEMOTION:
            if (paused) pauseIcon.currentSprite = ICON_MOUSE_CLICK;
            else pauseIcon.currentSprite = ICON_MOUSE_DEFAULT;
            break;
        case SDL_MOUSEBUTTONDOWN:
            pauseIcon.currentSprite = ICON_MOUSE_CLICK;

            Mix_PlayChannel(-1, p_window.getMix_Chunk(2), 0);
            if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
            else Mix_PauseMusic();

            break;
        case SDL_MOUSEBUTTONUP:
            paused = !paused;

            if (paused) pauseIcon.currentSprite = ICON_MOUSE_CLICK;
            else pauseIcon.currentSprite = ICON_MOUSE_DEFAULT;

            break;
        }
    }
    else  {
        if (paused) pauseIcon.currentSprite = ICON_MOUSE_CLICK;
        else pauseIcon.currentSprite = ICON_MOUSE_DEFAULT;
    }
}


void Mechanism::renderPauseIcon (RenderWindow& p_window) {
    cleanUp();

    pauseIcon.loadMedia(p_window, "pauseIcon.png");
    pauseIcon.setPosition(rootPos.x, rootPos.y);

    utilsEntities.push_back (pauseIcon.iconEntity());

    for (Entity& e : utilsEntities) {
        p_window.render(e, iconRatio);
    }

}


void Mechanism::playGame(RenderWindow& p_window) {
    frameStart = SDL_GetTicks();

    std::vector<Food> food(1);

    background.cleanBackground();

    Basket basket;

    bool add = true;

    std::clock_t start, now;
    start = std::clock();

    while (gameRunning) {
        p_window._clear();

        background.renderGrassBackground(p_window);
        background.renderDropAreaBackground(p_window);
        background.renderDropArea(p_window);

        renderPauseIcon (p_window);

        now = std::clock();

        double duration = double(now - start) / double(CLOCKS_PER_SEC);

        if (duration >= 15 && add) { //around 60s
            if (level == 2 && food[0].getFoodPos().y >= 300 && food[0].getFoodPos().y <= 350) {
                std::cout << "FOOD 0 POS Y: " << food[0].getFoodPos().y << std::endl;
                std::cout << "NOW: " << now << " DURATION: " << duration << std::endl;
                Food newFood;
                food.push_back(newFood);
                start = std::clock();
                add = false;
            }
        }

        handleEvent(event, p_window, basket);

        if (paused) {
            continue;
        }

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

    food.clear();

    renderLives(p_window);
    renderGameOver(p_window);
}

void Mechanism::damn(RenderWindow& p_window) {
    while (SDL_PollEvent(&event)) {
        if (currentKeyStates[ SDL_SCANCODE_SPACE ] || currentKeyStates[SDL_SCANCODE_ESCAPE]) {
            if (currentKeyStates[ SDL_SCANCODE_SPACE ]) {
                std::cout << "SPACE" << std::endl;
                lives = MAX_LIVES;
                score = 0;
                level = 1;
                gameRunning = true;
                startGame = true;
                p_window.playMusic();
                playGame(p_window);
                break;
            }
            else if (currentKeyStates[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT) {
                p_window.wait = false;
                break;
            }
        }
    }
}



void Mechanism::renderLives(RenderWindow& p_window) {
    cleanUp();

    loadMedia(p_window, livesFilePath.c_str());

    int currentLives = lives;
    for (int i = 0; i < MAX_LIVES; i++) {
        if (currentLives > 0) {
            utilsEntities.push_back(Entity(VectorMath(550 + i *  livesWitdth * livesRatio, SCREEN_HEIGHT / 2.15), livesRect, loadUtils));
            currentLives--;
        }
        else utilsEntities.push_back(Entity(VectorMath(550 + i *  livesWitdth * livesRatio, SCREEN_HEIGHT / 2.15), deadRect, loadUtils));
    }


    for (Entity& e : utilsEntities) {
        p_window.render(e, livesRatio);
    }

}


void Mechanism::updateGame(Basket &p_basket, Food &p_food, RenderWindow &p_window) {
    if (p_food.getFoodPos().y >= p_basket.getBasketPos().y) {
       if (p_food.getFoodPos().x >= p_basket.getBasketPos().x && p_food.getFoodPos().x + MAX_FOOD_WIDTH * foodRatio <= p_basket.getBasketPos().x + basketWidth *basketRatio
            && p_food.getFoodPos().y + MAX_FOOD_HEIGHT * foodRatio < bottomDropBorder) {
            Mix_PlayChannel(-1, p_window.getMix_Chunk(4), 0);
            updateScore();
            updateLevel();
            std::cout << "LEVEL: " << level << std::endl;
            p_food.foodDrop(p_window, FALSE, level);
        }
        else if (p_food.getFoodPos().y >= bottomDropBorder - MAX_FOOD_HEIGHT * foodRatio) {
            Mix_PlayChannel(-1, p_window.getMix_Chunk(5), 0);
            updateLives();
            std::cout << "LEVEL: " << level << std::endl;
            p_food.foodDrop(p_window, FALSE, level);
        }
    }


    if (lives == 0) {
        Mix_PlayChannel(-1, p_window.getMix_Chunk(3), 0);
        Mix_HaltMusic();
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
        utilsEntities.push_back(Entity(VectorMath(600 + (index * 50) - 5, 185), numRect, loadUtils));
        index++;
    }

    for (Entity& e : utilsEntities) {
        p_window.render(e, numRatio);
    }

    cleanUp();

    loadUtils = p_window.loadTexture(scoreFilePath.c_str());

    utilsEntities.push_back(Entity(VectorMath(460, 50), scoreRect, loadUtils));

    for (Entity& e : utilsEntities) {
        p_window.render(e, scoreRatio);
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

void Mechanism::renderGameOver(RenderWindow& p_window) {
    cleanUp();

    loadUtils = p_window.loadTexture(gameOverFilePath.c_str());

    utilsEntities.push_back(Entity(VectorMath(455, 325), gameOverRect, loadUtils));

    for (Entity& e : utilsEntities) {
        p_window.render(e, gameOverRatio);

    }

    cleanUp();

    loadMedia(p_window, "instruc_end.png");
    //loadUtils = p_window.loadTexture("instruc_end.png");

    utilsEntities.push_back(Entity(VectorMath(), fullScreenRect, loadUtils));

    for (Entity& e : utilsEntities) {
        p_window.render(e, fullScreenRatio);

    }
}


void Mechanism::updateLevel() {
    if (score % 10 == 0) {
        level += 1;
        std::cout << "LEVEL: " << level << std::endl;
    }

}

