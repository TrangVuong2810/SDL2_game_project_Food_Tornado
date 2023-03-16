#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "Background.h"
#include "VectorMath.h"
#include "Food.h"
#include "Basket.h"
#include "Text.h"
#include "Button.h"

Button::Button()
{
	position.setVectorMath(0, 0);

	currentSprite = BUTTON_MOUSE_OUT;
}


void Button::cleanUp() {
    SDL_DestroyTexture(loadButton);
    loadButton = nullptr;
}

Button::~Button() {
    cleanUp();
}

void Button::setPosition(double x, double y)
{
	position.setVectorMath(x, y);
}

//bool Button::IsInside(SDL_Event &e, int size)
bool Button::isInside(SDL_Event &e)
{
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		double button_width, button_height;

        button_width = 144;
        button_height = 72;

		SDL_GetMouseState(&x, &y);

		bool inside = true;
		if (x < position.x)
		{
			inside = false;
		}
		else if (x > position.x + button_width)
		{
			inside = false;
		}
		else if (y < position.y)
		{
			inside = false;
		}
		else if (y > position.y + button_height)
		{
			inside = false;
		}
		return inside;
	}
	return false;
}

Entity Button::buttonEntity(const SDL_Rect& currentClip, RenderWindow& p_window)
{
	 return Entity(position, currentClip, loadButton);
}

void Button::loadMedia(RenderWindow& p_window, const char* p_filePath) {

    cleanUp();

    loadButton = p_window.loadTexture(p_filePath);

    if (loadButton == nullptr) {
        std::cout << "Unable to load Button texture. Error: " << SDL_GetError() << std::endl;
    }

}
