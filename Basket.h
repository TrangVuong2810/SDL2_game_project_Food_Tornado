#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "VectorMath.h"
#include "Const_Vars.h"


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

