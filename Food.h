#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "Background.h"
#include "VectorMath.h"
#include "Const_Vars.h"

class Food {
private:
    SDL_Rect food[5];
    std::vector<Entity> foodEntities;
    SDL_Texture* loadFood = nullptr;
    VectorMath pos;
    int foodNum = -1;
    int foodFlip = 0;
    double foodRotate = 0;
public:
    ~Food();

    void cleanUp();
    void clearVectors();
    VectorMath getFoodPos();
    void loadFoodTexture(RenderWindow &p_window);
    void foodRender(RenderWindow &p_window, const double &p_ratio);
    void randomFoodRender(RenderWindow &p_window);
    void foodDrop (RenderWindow &p_window, const bool &p_check, int &p_level);
};
