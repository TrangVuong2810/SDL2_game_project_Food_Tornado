#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "VectorMath.h"
#include "RenderWindow.h"
#include "Bear.h"
#include "Const_Vars.h"


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
