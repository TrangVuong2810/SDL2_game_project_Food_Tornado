#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "Background.h"
#include "VectorMath.h"

const double SCREEN_WIDTH = 800;
const double HALF_SCREEN_WIDTH = 400;
const double SCREEN_HEIGHT = 600;
const double HALF_SCREEN_HEIGHT = 300;
const std::string WINDOW_TITLE = "Food Tornado";


const double leftBorder = 75;
const double rightBorder = 75;
const double topBorder = 75;
const double bottomBorder = 75;


const SDL_Rect grassBackground_rect = {0, 80, 96, 32};
const double grassBackgroundHeight = 32;
const double grassBackgroundRatio = 4.25;

const SDL_Rect tallTree_rect = {1, 0, 14, 29};
const double tallTreeHeight = 29;
const double tallTreeWidth = 14;
const double tallTreeRatio = 2.75;

const SDL_Rect boulder_rect = {128, 18, 16, 12};
const double boulderHeight = 12;
const double boulderWidth = 16;
const double boulderRatio = 4;

const double alignTree_boulder = (boulderWidth * boulderRatio / 2.0) - (tallTreeWidth * tallTreeRatio / 2.0);

const double dropAreaWidth = 300;
const double dropAreaHeight = SCREEN_HEIGHT - bottomBorder - boulderHeight * boulderRatio; //check the top border


const SDL_Rect pinkBud_rect = {99, 54, 9, 6};
const SDL_Rect yellowBud_rect = {99, 39, 9, 6};
const double budWidth = 9;
const double budHeight = 6;
const double budRatio = 4.25;

const SDL_Rect dirtBackground_rect = {0, 0, 48, 32};
const double dirtBackgroundHeight = 32;
const double dirtBackgroundRatio = 7.25; //dropAreaWidth / 48

const SDL_Rect dirtBackgroundBlend_rect = {26, 58, 28, 7};
const double dirtBackgroundBlendHeight = 7;
const double dirtBackgroundBlendRatio = 12.25;

const SDL_Rect grass_rect = {84, 23, 8, 5};
const double grassWidth = 8;
const double grassHeight = 5;
const double grassRatio = 5;



const double foodRatio = 3;
const double MAX_FOOD_WIDTH = 10;
const double MAX_FOOD_HEIGHT = 11;

const double leftDropBorder = leftBorder + boulderWidth * boulderRatio; //139
const double rightDropBorder = leftBorder + boulderWidth * boulderRatio + dropAreaWidth; //439
const double topDropBorder = topBorder + (dirtBackgroundBlendHeight / 2) * dirtBackgroundRatio;
const double bottomDropBorder = SCREEN_HEIGHT - bottomBorder - boulderHeight * boulderRatio; //477


class Food {
private:
    SDL_Rect food[5];
    std::vector<Entity> foodEntities;
    SDL_Texture* loadFood = nullptr;
    VectorMath pos;
    int foodNum = -1;
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
