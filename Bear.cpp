#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "VectorMath.h"
#include "RenderWindow.h"
#include "Bear.h"

Bear::Bear() {
    position.setVectorMath(575, 390);

    cntSprite = 0;

    currentSprite = BEAR_DEFAULT;
}

Bear::~Bear() {
    cleanUp();
}

void Bear::cleanUp() {
    SDL_DestroyTexture(loadBear);
    loadBear = nullptr;
}

void Bear::setPosition(double x, double y) {
    position.setVectorMath(x, y);
}

void Bear::setBearSprite() {
    if (currentSprite == BEAR_DEFAULT && cntSprite == MAX_SPRITES) {
        currentSprite = BEAR_MOVE_1;
        cntSprite = 0;
    }
    else if (currentSprite == BEAR_MOVE_1 && cntSprite == MAX_SPRITES) {
        currentSprite = BEAR_MOVE_2;
        cntSprite = 0;
    }
    else if (currentSprite == BEAR_MOVE_2 && cntSprite == MAX_SPRITES) {
        currentSprite = BEAR_DEFAULT;
        cntSprite = 0;
    }
    else cntSprite++;
}

Entity Bear::bearEntity() {
    setBearSprite();

    if (currentSprite == BEAR_DEFAULT) {
        return Entity(position, bearRect1, loadBear);
    }
    else if (currentSprite == BEAR_MOVE_1) {
        return Entity(position, bearRect2, loadBear);
    }
    else return Entity(position, bearRect3, loadBear);
}

void Bear::loadMedia(RenderWindow& p_window, const char* p_filePath) {
    cleanUp();

    if (loadBear == nullptr) loadBear = p_window.loadTexture(p_filePath);

    if (loadBear == nullptr) {
        std::cout << "Unable to load Bear texture. Error: " << SDL_GetError() << std::endl;
    }

}

