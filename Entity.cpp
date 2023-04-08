#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "VectorMath.h"
#include "RenderWindow.h"
#include "Entity.h"

Entity::Entity(VectorMath p_pos, SDL_Rect p_rect, SDL_Texture* p_tex) {
    pos = p_pos;
    tex = p_tex;

    currentFrame.x = p_rect.x;
    currentFrame.y = p_rect.y;
    currentFrame.w = p_rect.w ;
    currentFrame.h = p_rect.h ;

    degrees = 0;
    flipType = SDL_FLIP_NONE;
}

Entity::Entity(VectorMath p_pos, SDL_Rect p_rect, SDL_Texture* p_tex, double p_degrees, int flipNum) {
    pos = p_pos;
    tex = p_tex;

    currentFrame.x = p_rect.x;
    currentFrame.y = p_rect.y;
    currentFrame.w = p_rect.w ;
    currentFrame.h = p_rect.h ;

    degrees = p_degrees;
    handleFlipNum(flipNum);
}

bool Entity::rotationCheck() {
    if (degrees == 0 && flipType == SDL_FLIP_NONE) {
        return false;
    }
    return true;
}

void Entity::handleFlipNum(int p_flipNum) {
    switch (p_flipNum) {
    case 0:
        flipType = SDL_FLIP_HORIZONTAL;
        break;
    case 1:
        flipType = SDL_FLIP_NONE;
        break;
    case 2:
        flipType = SDL_FLIP_VERTICAL;
        break;
    }
}

SDL_Texture* Entity::getTex() {
    return tex;
}

SDL_Rect Entity::getCurrentFrame() {
    return currentFrame;
}
