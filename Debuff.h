#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "VectorMath.h"
#include "Const_Vars.h"

class Debuff {
private:
    SDL_Rect debuff[2];
    std::vector<Entity> debuffEntities;
    SDL_Texture* loadDebuff = nullptr;
    VectorMath pos;
    int debuffNum = -1;
    int debuffFlip = 0;
    double debuffRotate = 0;
public:
    ~Debuff();

    int getDebuffNum();
    void cleanUp();
    void clearVectors();
    VectorMath getDebuffPos();
    void loadDebuffTexture(RenderWindow &p_window);
    void debuffRender(RenderWindow &p_window, const double &p_ratio);
    void randomDebuffRender(RenderWindow &p_window);
    void debuffDrop (RenderWindow &p_window, int &p_level);

};
