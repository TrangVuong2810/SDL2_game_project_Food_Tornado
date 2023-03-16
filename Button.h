#pragma once

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
#include "Menu.h"

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2

/*
const double COMMON_BUTTON_WIDTH = 144;
const double COMMON_BUTTON_HEIGHT = 72;
const double SMALL_BUTTON_WIDTH = 144;
const double SMALL_BUTTON_HEIGHT = 72;

const int PLAY_BUTTON_POSX = 250;
const int PLAY_BUTTON_POSY= 425;
const int HELP_BUTTON_POSX = 750;
const int HELP_BUTTON_POSY = 150;
const int EXIT_BUTTON_POSX = 750;
const int EXIT_BUTTON_POSY = 400;
const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;
const int PAUSE_BUTTON_POSX = 31;
const int PAUSE_BUTTON_POSY = 29;
const int CONTINUE_BUTTON_POSX = 31;
const int CONTINUE_BUTTON_POSY = 29;


*/


enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1
};

class Button
{
public:
	ButtonSprite currentSprite;

	~Button();

	Button();

	void loadMedia(RenderWindow& p_window, const char* p_filePath);

	void setPosition(double x, double y);

	void cleanUp();

	bool isInside(SDL_Event& p_event);

	Entity buttonEntity(const SDL_Rect& currentClip, RenderWindow& p_window);

private:
	VectorMath position;

	SDL_Texture* loadButton = nullptr;
};

