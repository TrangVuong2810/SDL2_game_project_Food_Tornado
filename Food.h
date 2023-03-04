#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

#include "VectorMath.h"
#include "RenderWindow.h"
#include "Entity.h"
#include "Background.h"


const double foodRatio = 3;

const double leftDropBorder = leftBorder + boulderWidth * boulderRatio; //139
const double rightDropBorder = leftBorder + boulderWidth * boulderRatio + dropAreaWidth - 10 * foodRatio; //409 //10 is the width of the widest food
const double topDropBorder = topBorder + (dirtBackgroundBlendHeight / 2) * dirtBackgroundRatio;
const double bottomDropBorder = SCREEN_HEIGHT - bottomBorder - boulderHeight * boulderRatio;


class Food {
private:
    SDL_Rect food[5];
    std::vector<Entity> foodEntities;
    SDL_Texture* loadFood = nullptr;
    VectorMath pos;
public:
    void cleanUp();
    void clearVectors();
    void loadFoodTexture(RenderWindow &p_window);
    void foodRender(RenderWindow &p_window, const double &p_ratio);
    void randomFoodRender(RenderWindow &p_window);
    void foodDrop (RenderWindow &p_window);
};
