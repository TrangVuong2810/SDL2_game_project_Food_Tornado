#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "VectorMath.h"
#include "Const_Vars.h"

class Buff {
private:
    SDL_Rect buff[2];
    std::vector<Entity> buffEntities;
    SDL_Texture* loadBuff = nullptr;
    VectorMath pos;
    int buffNum = -1;
    int buffFlip = 0;
    double buffRotate = 0;
public:
    ~Buff();

    int getBuffNum();
    void cleanUp();
    void clearVectors();
    VectorMath getBuffPos();
    void loadBuffTexture(RenderWindow &p_window);
    void buffRender(RenderWindow &p_window, const double &p_ratio);
    void randomBuffRender(RenderWindow &p_window, int &p_lives);
    void buffDrop (RenderWindow &p_window, int &p_lives, int &p_level);

};
