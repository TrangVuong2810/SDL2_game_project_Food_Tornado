#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

#include "VectorMath.h"
#include "RenderWindow.h"
#include "Entity.h"
#include "Background.h"
#include "Basket.h"
#include "Food.h"

void Basket::clearVectors() {
    basketEntities.clear();
}
VectorMath Basket::getBasketPos() {
    return pos;
}
void Basket::setBasketPos(double p_x, double p_y) {
    pos.x = p_x;
    pos.y = p_y;
}
void Basket::loadBasketTexture(RenderWindow &p_window) {
    loadBasket = p_window.loadTexture("Object.png"); //127 x 145 //32 x 96 //17 x14**//

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

    std::cout << "BASKET: " << pos.x << " " << pos.y << std:: endl;

}
void Basket::basketMove (RenderWindow &p_window, char &key) {
    if (pos.x >= leftDropBorder && pos.x <= rightDropBorder) {
        clearVectors();

        switch (key) {
        case 'L':
            pos.x -= 10;
            break;
        case 'R':
            pos.x += 10;
            break;
        }
        basketEntities.push_back(Entity(pos, basket_rect, loadBasket));

    }

}
