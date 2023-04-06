#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "VectorMath.h"


const SDL_Rect iconDefaultRect = {0, 0, 128, 128};
const SDL_Rect iconClickedRect = {0, 128, 128, 128};

const double iconRatio = 0.5;

enum iconSprite
{
	ICON_MOUSE_DEFAULT = 0,
	ICON_MOUSE_CLICK = 1
};
class Icon
{

private:
	VectorMath position;

	SDL_Texture* loadIcon = nullptr;

public:
	iconSprite currentSprite;

	~Icon();

	Icon();

	void loadMedia(RenderWindow& p_window, const char* p_filePath);

	void setPosition(double x, double y);

	void cleanUp();

	bool isInside(SDL_Event& p_event);

	Entity iconEntity();

};


