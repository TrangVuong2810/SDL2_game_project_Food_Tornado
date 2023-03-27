#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "VectorMath.h"
#include "RenderWindow.h"
#include "Cow.h"

Cow::Cow() {
    position.setVectorMath(350, 300);

    cntSprite = 0;

    currentSprite = COW_WAVING_TAIL;
}

Cow::~Cow() {
    cleanUp();
}

void Cow::cleanUp() {
    SDL_DestroyTexture(loadCow);
    loadCow = nullptr;
}

void Cow::setPosition(double x, double y) {
    position.setVectorMath(x, y);
}

void Cow::setCowSprite() {
    if (currentSprite == COW_DEFAULT && cntSprite == MAX_SPRITES) {
        currentSprite = COW_CLOSED_EYES;
        cntSprite = 0;
    }
    else if (currentSprite == COW_CLOSED_EYES && cntSprite == MAX_SPRITES) {
        currentSprite = COW_WAVING_TAIL;
        cntSprite = 0;
    }
    else if (currentSprite == COW_WAVING_TAIL && cntSprite == MAX_SPRITES) {
        currentSprite = COW_DEFAULT;
        cntSprite = 0;
    }
    else cntSprite++;

}

Entity Cow::cowEntity() {
    //if (loadCow == nullptr) loadCow =
    setCowSprite();

    if (currentSprite == COW_DEFAULT) {
        return Entity(position, cowRect1, loadCow);
    }
    else if (currentSprite == COW_CLOSED_EYES) {
        return Entity(position, cowRect2, loadCow);
    }
    else return Entity(position, cowRect3, loadCow);
}

void Cow::loadMedia(RenderWindow& p_window, const char* p_filePath) {
    cleanUp();

    if (loadCow == nullptr) loadCow = p_window.loadTexture(p_filePath);

    if (loadCow == nullptr) {
        std::cout << "Unable to load Cow texture. Error: " << SDL_GetError() << std::endl;
    }

}
