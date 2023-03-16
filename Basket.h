#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "Background.h"
#include "VectorMath.h"
#include "Food.h"
#include "Mechanism.h"
#include "Text.h"

const SDL_Rect basket_rect = {16, 82, 16, 14};
const double basketWidth = 16;
const double basketHeight = 14;
const double basketRatio = 5;

class Basket {
private:
    std::vector<Entity> basketEntities;
    SDL_Texture* loadBasket = nullptr;
    VectorMath pos;
public:
    ~Basket();
    void clearVectors();
    void cleanUp();
    VectorMath getBasketPos();
    void setBasketPos(double p_x, double p_y);
    void loadBasketTexture(RenderWindow &p_window);
    void basketRender(RenderWindow &p_window);
    void basketMove (RenderWindow &p_window, char &key);
};

