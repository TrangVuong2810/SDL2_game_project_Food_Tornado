#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "VectorMath.h"
#include "Icon.h"

class Background {
private:
    std::vector<Entity> backgroundEntities;
    SDL_Texture* loadBackground = nullptr;
public:
    ~Background();
    void clearVector();
    void cleanBackground();
    void updateBackground(Entity p_entity);
    void renderBackground(RenderWindow& p_window, const double& p_ratio);
    void renderGrassBackground(RenderWindow& p_window);
    void renderDropArea(RenderWindow& p_window);
    void renderDropAreaBackground(RenderWindow& p_window);
};

