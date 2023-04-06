#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "VectorMath.h"
#include "RenderWindow.h"

const int MAX_SPRITES = 30;

const SDL_Rect bearRect1 = {1, 210, 37, 25};
const SDL_Rect bearRect2 = {49, 210, 42, 25};
const SDL_Rect bearRect3 = {98, 210, 37, 25};

const std::string bearFilePath = {"bear.png"};

const double bearRatio = 5;

enum BearSprite
{
	BEAR_DEFAULT = 0,
	BEAR_MOVE_1 = 1,
	BEAR_MOVE_2 = 2
};

class Bear {
private:
    VectorMath position;

	SDL_Texture* loadBear = nullptr;
public:
    BearSprite currentSprite;

    int cntSprite;

    void setBearSprite();

	~Bear();

	Bear();

	void loadMedia(RenderWindow& p_window, const char* p_filePath);

	void setPosition(double x, double y);

	void cleanUp();

	Entity bearEntity();

};

