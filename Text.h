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
#include "Mechanism.h"

struct Text {
    SDL_Texture* texture;

    TTF_Font* font = nullptr;

    //Image dimensions
    int width = 0;
    int height = 0;

    Text();
    ~Text();

    SDL_Texture* getTexture();

    void close();

    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer );

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );
};





