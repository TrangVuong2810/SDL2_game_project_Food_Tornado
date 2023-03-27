#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "VectorMath.h"
#include "Basket.h"

Basket::~Basket() {
    cleanUp();
}

void Basket::clearVectors() {
    basketEntities.clear();
}

void Basket::cleanUp() {
    SDL_DestroyTexture(loadBasket);
    loadBasket = nullptr;
    clearVectors();
}

VectorMath Basket::getBasketPos() {
    return pos;
}
void Basket::setBasketPos(double p_x, double p_y) {
    pos.x = p_x;
    pos.y = p_y;
}
void Basket::loadBasketTexture(RenderWindow &p_window) {
    cleanUp();

    loadBasket = p_window.loadTexture("Object.png");

    if (loadBasket == nullptr) {
        std::cout << "Unable to load basket. Error: " << SDL_GetError() << std::endl;
    }
    else {
        pos.setVectorMath(leftDropBorder, bottomDropBorder - basketHeight * basketRatio);

        basketEntities.push_back(Entity(pos, basket_rect, loadBasket));
    }

}
void Basket::basketRender(RenderWindow &p_window) {

    if (loadBasket == nullptr) loadBasketTexture(p_window);

    for (Entity& e : basketEntities) {
        p_window.render(e, basketRatio);
    }


    //std::cout << "BASKET: " << pos.x << " " << pos.y << std:: endl;

}
void Basket::basketMove (RenderWindow &p_window, char &key) {

    if (pos.x >= leftDropBorder && pos.x + basketWidth * basketRatio <= rightDropBorder) {
        clearVectors();

        switch (key) {
        case 'L':
            if (pos.x >= leftDropBorder + 10) pos.x -= 10;
            break;
        case 'R':
            if (pos.x + basketWidth * basketRatio <= rightDropBorder - 10) pos.x += 10;
            break;
        }
        basketEntities.push_back(Entity(pos, basket_rect, loadBasket));

    }

}
