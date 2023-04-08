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

    double degrees;

    SDL_RendererFlip flipType;
public:
    Entity(VectorMath p_pos, SDL_Rect p_rect, SDL_Texture*  p_tex);
    Entity(VectorMath p_pos, SDL_Rect p_rect, SDL_Texture*  p_tex, double p_degrees, int flipNum);
    void handleFlipNum (int p_flipNum);

    bool rotationCheck();

    VectorMath getPos() {return pos;}
    double getDeg() {return degrees;}
    SDL_RendererFlip getFLip() {return flipType;}
    SDL_Texture* getTex();
    SDL_Rect getCurrentFrame();
};


