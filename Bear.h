#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "VectorMath.h"
#include "RenderWindow.h"
#include "Const_Vars.h"

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

