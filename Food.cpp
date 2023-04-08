#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "VectorMath.h"
#include "RenderWindow.h"
#include "Background.h"
#include "Entity.h"
#include "Food.h"

Food::~Food() {
    cleanUp();
}

void Food::clearVectors() {
    foodEntities.clear();
}

void Food::foodRender(RenderWindow &p_window, const double &p_ratio) {
    for (Entity& e : foodEntities) {
        p_window.render(e, p_ratio);
    }
}

void Food::loadFoodTexture(RenderWindow &p_window) {
    cleanUp();

    loadFood = p_window.loadTexture("TreesAndFruits.png");

    if (loadFood == nullptr) {
        std::cout << "Unable to load food. Error: " << SDL_GetError() << std::endl;
    }
    else {
        food[0] = {20, 36, 7, 8}; //apple
        food[1] = {53, 54, 6, 6}; //strawberry?
        food[2] = {100, 4, 10, 11}; //red mushroom
        food[3] = {115, 3, 7, 8}; //purple mushroom
    }
}

void Food::randomFoodRender(RenderWindow &p_window) {
    cleanUp();

    if (loadFood == nullptr) loadFoodTexture(p_window);

    clearVectors();

    pos.setVectorMath((double)(rand() % 271 + 139), topDropBorder); //x from 139 to 409

    foodNum = rand() % 4;
    foodFlip = rand() % 3;
    foodRotate = rand() % 360;

    foodEntities.push_back(Entity(pos, food[foodNum], loadFood, foodRotate, foodFlip));

    std::cout << "NEW FOOD: " << pos.x << " " << pos.y << " ROTATION: " << foodRotate << " " << foodFlip << std::endl;

    foodRender(p_window, foodRatio);
}

VectorMath Food::getFoodPos() {
    return pos;
}

void Food::foodDrop (RenderWindow &p_window, const bool &p_check, int &p_level) {
    cleanUp();
    if (loadFood == nullptr) loadFoodTexture(p_window);

    if (foodNum == -1) randomFoodRender(p_window);
    if (p_check) {
        if (p_level == 1) pos.y += 1;
        else if (p_level == 2) pos.y += 2;
        else pos.y += 3;
        foodEntities.push_back(Entity(pos, food[foodNum], loadFood, foodRotate, foodFlip));
        foodRender(p_window, foodRatio);
    }
    else {
        randomFoodRender(p_window);
    }

}


void Food::cleanUp() {
    SDL_DestroyTexture(loadFood);
    loadFood = nullptr;
    clearVectors();
}

