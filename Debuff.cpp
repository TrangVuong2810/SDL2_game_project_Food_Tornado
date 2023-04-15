#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "VectorMath.h"
#include "Const_Vars.h"
#include "Debuff.h"

Debuff::~Debuff() {
    cleanUp();
}

int Debuff::getDebuffNum() {
    return debuffNum;
}

void Debuff::cleanUp() {
    SDL_DestroyTexture(loadDebuff);
    loadDebuff = nullptr;
    clearVectors();
}

void Debuff::clearVectors() {
    debuffEntities.clear();
}


VectorMath Debuff::getDebuffPos() {
    return pos;
}


void Debuff::loadDebuffTexture(RenderWindow &p_window) {
    cleanUp();

    loadDebuff = p_window.loadTexture("TreesAndFruits.png");

    if (loadDebuff == nullptr) {
        std::cout << "Unable to load debuff Error: " << SDL_GetError() << std::endl;
    }
    else {
        debuff[0] = {80, 35, 16, 10}; //wood log
        debuff[1] = {114, 18, 10, 8}; // rock
    }
}


void Debuff::debuffRender(RenderWindow &p_window, const double &p_ratio) {
    for (Entity& e : debuffEntities) {
        p_window.render(e, p_ratio);
    }
}


void Debuff::randomDebuffRender(RenderWindow &p_window) {
    cleanUp();

    if (loadDebuff == nullptr) loadDebuffTexture(p_window);

    clearVectors();

    pos.setVectorMath((double)(rand() % 271 + 139), topDropBorder); //x from 139 to 409

    debuffNum = rand() % 2;
    debuffFlip = rand() % 3;
    debuffRotate = rand() % 360;

    debuffEntities.push_back(Entity(pos, debuff[debuffNum], loadDebuff, debuffRotate, debuffFlip));

    std::cout << "NEW DEBUFF: " << pos.x << " " << pos.y << " ROTATION: " << debuffRotate << " " << debuffFlip << std::endl;

    debuffRender(p_window, debuffRatio);
}


void Debuff::debuffDrop (RenderWindow &p_window, int &p_level) {
    cleanUp();
    if (loadDebuff == nullptr) loadDebuffTexture(p_window);

    if (debuffNum == -1) randomDebuffRender(p_window);
    if (p_level == 1) pos.y += 1;
    else if (p_level == 2) pos.y += 1.5;
    else pos.y += 2;
    debuffEntities.push_back(Entity(pos, debuff[debuffNum], loadDebuff, debuffRotate, debuffFlip));
    debuffRender(p_window, debuffRatio);

}

