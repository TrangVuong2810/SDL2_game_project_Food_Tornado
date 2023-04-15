#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "VectorMath.h"
#include "Const_Vars.h"
#include "Buff.h"

Buff::~Buff() {
    cleanUp();
}

int Buff::getBuffNum() {
    return buffNum;
}

void Buff::cleanUp() {
    SDL_DestroyTexture(loadBuff);
    loadBuff = nullptr;
    clearVectors();
}

void Buff::clearVectors() {
    buffEntities.clear();
}


VectorMath Buff::getBuffPos() {
    return pos;
}


void Buff::loadBuffTexture(RenderWindow &p_window) {
    cleanUp();

    loadBuff = p_window.loadTexture("Utils.png");

    if (loadBuff == nullptr) {
        std::cout << "Unable to load buff. Error: " << SDL_GetError() << std::endl;
    }
    else {
        buff[0] = livesRect; //lives
        buff[1] = shieldRect; //shield
    }
}


void Buff::buffRender(RenderWindow &p_window, const double &p_ratio) {
    for (Entity& e : buffEntities) {
        p_window.render(e, p_ratio);
    }
}


void Buff::randomBuffRender(RenderWindow &p_window, int &p_lives) {
    cleanUp();

    if (loadBuff == nullptr) loadBuffTexture(p_window);

    clearVectors();

    pos.setVectorMath((double)(rand() % 271 + 139), topDropBorder); //x from 139 to 409

    if (p_lives < 3) buffNum = rand() % 2;
    else buffNum = 1;
    buffFlip = rand() % 3;
    buffRotate = rand() % 360;

    buffEntities.push_back(Entity(pos, buff[buffNum], loadBuff, buffRotate, buffFlip));

    std::cout << "NEW BUFF: " << pos.x << " " << pos.y << " ROTATION: " << buffRotate << " " << buffFlip << std::endl;

    buffRender(p_window, buffRatio);
}


void Buff::buffDrop (RenderWindow &p_window, int &p_lives, int &p_level) {
    cleanUp();
    if (loadBuff == nullptr) loadBuffTexture(p_window);

    if (buffNum == -1) randomBuffRender(p_window, p_lives);
    if (p_level == 1) pos.y += 1;
    else if (p_level == 2) pos.y += 1.5;
    else pos.y += 2;
    buffEntities.push_back(Entity(pos, buff[buffNum], loadBuff, buffRotate, buffFlip));
    buffRender(p_window, buffRatio);

}
