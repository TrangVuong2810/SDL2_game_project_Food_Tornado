#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "VectorMath.h"
#include "RenderWindow.h"

const SDL_Rect cowRect1 = {1, 0, 31, 31};
const SDL_Rect cowRect2 = {33, 0, 31, 31};
const SDL_Rect cowRect3 = {65, 0, 31, 31};

const std::string cowFilePath = {"cow.png"};

const double cowRatio = 7;

enum CowSprite
{
	COW_DEFAULT = 0,
	COW_CLOSED_EYES = 1,
	COW_WAVING_TAIL = 2
};

class Cow {
private:
    VectorMath position;

	SDL_Texture* loadCow = nullptr;
public:
    CowSprite currentSprite;

    int cntSprite;

    void setCowSprite();

	~Cow();

	Cow();

	void loadMedia(RenderWindow& p_window, const char* p_filePath);

	void setPosition(double x, double y);

	void cleanUp();

	Entity cowEntity();

};
