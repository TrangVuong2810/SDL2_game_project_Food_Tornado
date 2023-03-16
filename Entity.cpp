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
}

SDL_Texture* Entity::getTex() {
    return tex;
}

SDL_Rect Entity::getCurrentFrame() {
    return currentFrame;
}
