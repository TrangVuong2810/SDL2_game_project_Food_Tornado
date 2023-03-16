#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "VectorMath.h"
#include "RenderWindow.h"
//using namespace std;

class Entity {
private:
    VectorMath pos;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
public:
    Entity(VectorMath p_pos, SDL_Rect p_rect, SDL_Texture*  p_tex);
    VectorMath getPos() {return pos;}
    SDL_Texture* getTex();
    SDL_Rect getCurrentFrame();
};


