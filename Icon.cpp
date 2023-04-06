#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "VectorMath.h"
#include "Icon.h"


Icon::Icon()
{
	position.setVectorMath(0, 0);

	//currentSprite = ICON_MOUSE_DEFAULT;
}


void Icon::cleanUp() {
    SDL_DestroyTexture(loadIcon);
    loadIcon = nullptr;
}

Icon::~Icon() {
    cleanUp();
}

void Icon::setPosition(double x, double y)
{
	position.setVectorMath(x, y);
}

Entity Icon::iconEntity() {
    if (currentSprite == ICON_MOUSE_CLICK) {
        return Entity(position, iconClickedRect, loadIcon);
    }
    else return Entity(position, iconDefaultRect, loadIcon);

}

bool Icon::isInside(SDL_Event &e)
{
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        int x, y;
        double icon_width, icon_height;

        icon_width = 128;
        icon_height = 128;

        SDL_GetMouseState(&x, &y);

        bool inside = true;
        if (x < position.x) {
            inside = false;
        }
        else if (x > position.x + icon_width) {
            inside = false;
        }
        else if (y < position.y) {
            inside = false;
        }
        else if (y > position.y + icon_height) {
            inside = false;
        }
        return inside;
    }
	return false;
}

void Icon::loadMedia(RenderWindow& p_window, const char* p_filePath) {

    cleanUp();

    if (loadIcon == nullptr) loadIcon = p_window.loadTexture(p_filePath);
    if (loadIcon == nullptr) {
        std::cout << "Unable to load Icon texture. Error: " << SDL_GetError() << std::endl;
    }

}
