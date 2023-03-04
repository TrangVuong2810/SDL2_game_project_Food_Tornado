#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "VectorMath.h"
#include "RenderWindow.h"
#include "Background.h"
#include "Entity.h"
#include "Food.h"


void Food::clearVectors() {
    foodEntities.clear();
}

void Food::foodRender(RenderWindow &p_window, const double &p_ratio) {
    for (Entity& e : foodEntities) {
        p_window.render(e, p_ratio);
    }
}

void Food::loadFoodTexture(RenderWindow &p_window) {
    clearVectors();

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
    loadFoodTexture(p_window);

    pos.setVectorMath((double)(rand() % 271 + 139), 100.0); //x from 139 to 409

    foodEntities.push_back(Entity(pos, food[rand() % 4], loadFood));

    foodRender(p_window, foodRatio);
    std::cout << pos.x << " " << pos.y << std::endl;

    SDL_Delay(1000);
    cleanUp();
}



void Food::foodDrop (RenderWindow &p_window) {
    cleanUp();
}


void Food::cleanUp() {
    loadFood = nullptr;
    clearVectors();
}




















/*
 void Enemy::Update()
{
    Timer += Timer->GetTimeElapsed();
    int Random = (rand() % 4);
    if (Timer >= 2.0)
    {
        switch (Random)
        {
        case(0):
            m_xPos += 10.0 * Timer->tElapsed();
        case(1):
            m_xPos -= 10.0  * Timer->tElapsed();
        case(2):
            m_yPos -= 10.0  * Timer->tElapsed();
        case(3):
            m_yPos += 10.0  * Timer->tElapsed();
        }
    }
}




*/
