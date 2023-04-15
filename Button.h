#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "VectorMath.h"
#include "Const_Vars.h"



enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_MOUSE_CLICK = 2
};

class Button
{

private:
	VectorMath position;

	SDL_Texture* loadButton = nullptr;

public:
	ButtonSprite currentSprite;

	~Button();

	Button();

	void loadMedia(RenderWindow& p_window, const char* p_filePath);

	void setPosition(double x, double y);

	void cleanUp();

	bool isInside(SDL_Event& p_event);

	Entity buttonEntity();

};

