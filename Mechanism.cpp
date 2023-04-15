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
#include "Button.h"
#include "Menu.h"
#include "Icon.h"
#include "Buff.h"
#include "Debuff.h"

Mechanism::Mechanism() {
    score = 0;
    lives = MAX_LIVES;
    level = 1;

    shield = false;

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
        else if (currentKeyStates[ SDL_SCANCODE_DOWN]) {
            gameRunning = false;
            startGame = false;
            Mix_HaltMusic();
        }
        else {//if (p_event.type == SDL_MOUSEMOTION || p_event.type == SDL_MOUSEBUTTONDOWN || p_event.type == SDL_MOUSEBUTTONUP) {
            handleIcon (p_event, p_window);

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
                if (menu.quit) {
                    startGame = false;
                    gameRunning = false;
                    p_window.wait = false;
                    cleanUp();
                    break;
                }

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

void Mechanism::handleIcon (SDL_Event& p_event, RenderWindow& p_window) {
    if (pauseIcon.isInside(p_event)) {
        switch (p_event.type) {
        case SDL_MOUSEMOTION:
            if (paused) pauseIcon.currentSprite = ICON_MOUSE_CLICK;
            else pauseIcon.currentSprite = ICON_MOUSE_DEFAULT;
            break;
        case SDL_MOUSEBUTTONDOWN:
            pauseIcon.currentSprite = ICON_MOUSE_CLICK;

            Mix_PlayChannel(-1, p_window.getMix_Chunk(2), 0);
            if (p_window.playingMusic) {
               if (Mix_PausedMusic() == 1) {
                    Mix_ResumeMusic();
                }
                else {
                    Mix_PauseMusic();
                }
            }

            break;
        case SDL_MOUSEBUTTONUP:

            paused = !paused;

            if (paused) pauseIcon.currentSprite = ICON_MOUSE_CLICK;
            else pauseIcon.currentSprite = ICON_MOUSE_DEFAULT;

            break;
        }
    }
    else if (musicIcon.isInside(p_event) && paused == false) {
        switch (p_event.type) {
        case SDL_MOUSEMOTION:
            if (Mix_PausedMusic() == 1) musicIcon.currentSprite = ICON_MOUSE_CLICK;
            else musicIcon.currentSprite = ICON_MOUSE_DEFAULT;
            break;
        case SDL_MOUSEBUTTONDOWN:
            Mix_PlayChannel(-1, p_window.getMix_Chunk(2), 0);
            if (Mix_PausedMusic() == 1) {
                    Mix_ResumeMusic();
                    p_window.playingMusic = true;
            }

            else {
                    Mix_PauseMusic();
                    p_window.playingMusic = false;
            }

            if (Mix_PausedMusic() == 1) musicIcon.currentSprite = ICON_MOUSE_CLICK;
            else musicIcon.currentSprite = ICON_MOUSE_DEFAULT;
            break;
        case SDL_MOUSEBUTTONUP:

            break;
        }
    }
    else  {
        if (paused) pauseIcon.currentSprite = ICON_MOUSE_CLICK;
        else pauseIcon.currentSprite = ICON_MOUSE_DEFAULT;

        if (Mix_PausedMusic() == 1) musicIcon.currentSprite = ICON_MOUSE_CLICK;
        else musicIcon.currentSprite = ICON_MOUSE_DEFAULT;
    }

}


void Mechanism::renderIcon (RenderWindow& p_window) {
    cleanUp();

    pauseIcon.loadMedia(p_window, "pauseIcon.png");
    pauseIcon.setPosition(rootPos.x, rootPos.y);

    utilsEntities.push_back (pauseIcon.iconEntity());

    musicIcon.loadMedia(p_window, musicIconFilePath.c_str());
    musicIcon.setPosition(musicIconPos.x, musicIconPos.y);

    utilsEntities.push_back(musicIcon.iconEntity());

    for (Entity& e : utilsEntities) {
        p_window.render(e, iconRatio);
    }
}


void Mechanism::playGame(RenderWindow& p_window) {
    frameStart = SDL_GetTicks();

    std::vector<Food> food(1);
    std::vector<Debuff> debuff(0);
    std::vector<Buff> buff(0);

    background.cleanBackground();

    Basket basket;

    std::clock_t start, now, de_buffStart, de_buffNow;
    start = std::clock();
    de_buffStart = std::clock();

    double de_buffTime = (double)(rand() % 30);

    while (gameRunning) {
        p_window._clear();

        background.renderGrassBackground(p_window);
        background.renderDropAreaBackground(p_window);
        background.renderDropArea(p_window);

        renderIcon (p_window);

        now = std::clock();
        de_buffNow = std::clock();

        double duration = double(now - start) / double(CLOCKS_PER_SEC);
        double de_buffDuration = double(de_buffNow - de_buffStart) / double(CLOCKS_PER_SEC);

        if (duration >= 60 && food.size() < 3) {
            handleFoodAdd(food, start, now);
        }
        if (de_buffDuration >= de_buffTime) {
            if (lives == 3 && shield) {
                debuff.clear();
                Debuff newDebuff;
                debuff.push_back(newDebuff);
            }
            else {
                int de_buff = rand() % 2;
                if (de_buff == 0) {
                    buff.clear();
                    Buff newBuff;
                    buff.push_back(newBuff);
                }
                else {
                    debuff.clear();
                    Debuff newDebuff;
                    debuff.push_back(newDebuff);
                }
            }

            de_buffTime = (double)(rand() % 30);
            de_buffStart = std::clock();
            de_buffNow = std::clock();
        }

        handleEvent(event, p_window, basket);

        if (paused) {
            continue;
        }

        basket.basketRender(p_window);

        renderLives(p_window);
        renderScores(p_window);
        renderShield(p_window);

        for (Food &f : food) {
            f.foodDrop(p_window, TRUE, level);
        }

        if (buff.size() > 0) {
            for (Buff &b : buff) {
                b.buffDrop(p_window, lives, level);
            }
        }
        if (debuff.size() > 0) {
            for (Debuff &d : debuff) {
                d.debuffDrop(p_window, level);
            }
        }


        for (Food &f : food) {
            updateGame(basket, f, p_window);
        }
        handleBuff(basket, buff, p_window);
        handleDebuff(basket, debuff, p_window);

        p_window.display();


        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    food.clear();
    buff.clear();
    debuff.clear();

    renderLives(p_window);
    renderGameOver(p_window);
}

void Mechanism::handleFoodAdd(std::vector<Food>& food, std::clock_t &start, std::clock_t &now) {
    if (level == 2 && food[0].getFoodPos().y >= 300 && food[0].getFoodPos().y <= 350 && lives >= 2) {
        std::cout << "FOOD 0 POS Y: " << food[0].getFoodPos().y << std::endl;
        Food newFood;
        food.push_back(newFood);
        start = std::clock();
        now = std::clock();
    }
    else if (level >= 3) {
        if (food.size() == 1 && food[0].getFoodPos().y >= 300 && food[0].getFoodPos().y <= 350) {
            std::cout << "FOOD 0 POS Y: " << food[0].getFoodPos().y << std::endl;
            Food newFood;
            food.push_back(newFood);
            start = std::clock();
            now = std::clock();
        }
        else if (food.size() == 2 && food[1].getFoodPos().y >= 200 && food[1].getFoodPos().y <= 250) {
            std::cout << "FOOD 1 POS Y: " << food[1].getFoodPos().y << std::endl;
            Food newFood;
            food.push_back(newFood);
            start = std::clock();
            now = std::clock();
        }
    }
}

void Mechanism::playAgain(RenderWindow& p_window) {
    while (SDL_PollEvent(&event)) {
        if (currentKeyStates[ SDL_SCANCODE_SPACE ] || currentKeyStates[SDL_SCANCODE_ESCAPE]) {
            if (currentKeyStates[ SDL_SCANCODE_SPACE ]) {
                lives = MAX_LIVES;
                score = 0;
                level = 1;
                gameRunning = true;
                startGame = true;
                shield = false;
                p_window.loadMusic();
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

void Mechanism::renderShield(RenderWindow& p_window) {
    cleanUp();

    loadMedia(p_window, utilsFilePath.c_str());

    if (shield) {
        utilsEntities.push_back(Entity(VectorMath(rightDropBorder + boulderWidth * boulderRatio, bottomDropBorder - MAX_BUFF_HEIGHT * buffRatio), shieldRect, loadUtils));
        p_window.render(utilsEntities[0], buffRatio);
    }
}


void Mechanism::renderLives(RenderWindow& p_window) {
    cleanUp();

    loadMedia(p_window, utilsFilePath.c_str());

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
            p_food.foodDrop(p_window, FALSE, level);
        }
        else if (p_food.getFoodPos().y >= bottomDropBorder - MAX_FOOD_HEIGHT * foodRatio) {
            Mix_PlayChannel(-1, p_window.getMix_Chunk(5), 0);
            if (shield) shield = false;
            else updateLives();
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

void Mechanism::handleBuff(Basket &p_basket, std::vector<Buff> &p_buff, RenderWindow &p_window) {
    if (p_buff.size() > 0) {
        int buffLen = p_buff.size();
        for (int b = 0; b < buffLen; b++) {
            std::vector<Buff>::iterator buffIt = p_buff.begin() + b;
            if (p_buff[b].getBuffPos().y >= p_basket.getBasketPos().y) {
                if (p_buff[b].getBuffPos().x >= p_basket.getBasketPos().x && p_buff[b].getBuffPos().x + MAX_BUFF_WIDTH * buffRatio <= p_basket.getBasketPos().x + basketWidth * basketRatio
                        && p_buff[b].getBuffPos().y + MAX_BUFF_HEIGHT * buffRatio < bottomDropBorder) {
                    Mix_PlayChannel(-1, p_window.getMix_Chunk(4), 0);
                    std::cout << "GOT BUFF" << std::endl;
                    if (p_buff[b].getBuffNum() == 1) shield = true;
                    else lives += 1;
                    p_buff.erase(buffIt);
                }
                else if (p_buff[b].getBuffPos().y >= bottomDropBorder - MAX_DEBUFF_HEIGHT * buffRatio) {
                    Mix_PlayChannel(-1, p_window.getMix_Chunk(5), 0);
                    std::cout << "MISS BUFF" << std::endl;
                    p_buff.erase(buffIt);
                }
            }

        }
    }
}


void Mechanism::handleDebuff(Basket &p_basket, std::vector<Debuff> &p_debuff, RenderWindow &p_window) {
    if (p_debuff.size() > 0) {
        int debuffLen = p_debuff.size();
        for (int d = 0; d < debuffLen; d++) {
            std::vector<Debuff>::iterator debuffIt = p_debuff.begin() + d;

            if (p_debuff[d].getDebuffPos().y >= p_basket.getBasketPos().y) {
                if (p_debuff[d].getDebuffPos().x >= p_basket.getBasketPos().x && p_debuff[d].getDebuffPos().x + MAX_DEBUFF_WIDTH * debuffRatio <= p_basket.getBasketPos().x + basketWidth * basketRatio
                        && p_debuff[d].getDebuffPos().y + MAX_DEBUFF_HEIGHT * debuffRatio < bottomDropBorder) {
                    Mix_PlayChannel(-1, p_window.getMix_Chunk(5), 0);
                    if (shield) shield = false;
                    else updateLives();
                    std::cout << "X_X" << std::endl;
                    p_debuff.erase(debuffIt);
                }
                else if (p_debuff[d].getDebuffPos().y >= bottomDropBorder - MAX_DEBUFF_HEIGHT * foodRatio) {
                    Mix_PlayChannel(-1, p_window.getMix_Chunk(4), 0);
                    std::cout << "SAFE" << std::endl;
                    p_debuff.erase(debuffIt);
                }
            }
        }
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


