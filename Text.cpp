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
#include "Mechanism.h"
#include "Text.h"

void Text::free()
{
    SDL_DestroyTexture( texture );
    texture = NULL;
    width = 0;
    height = 0;
}

Text::Text() {
	texture = NULL;
	width = 0;
	height = 0;
}

Text::~Text()
{
	free();
}


bool Text::loadFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Renderer* renderer) {

	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
	if(textSurface == nullptr)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	else
	{
        texture = SDL_CreateTextureFromSurface(renderer, textSurface );
		if(texture == nullptr)
		{
			std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			width = textSurface->w;
			height = textSurface->h;
		}

		SDL_FreeSurface( textSurface );
	}

	return texture != nullptr;
}



void Text::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( texture, red, green, blue );
}

void Text::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( texture, blending );
}

void Text::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( texture, alpha );
}


void Text::close()
{
	free();

	TTF_CloseFont( font );
	font = nullptr;
}

SDL_Texture* Text::getTexture() {
    return texture;
}
