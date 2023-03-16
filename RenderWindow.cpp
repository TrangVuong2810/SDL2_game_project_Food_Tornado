#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"

//using namespace std;

RenderWindow::~RenderWindow() {
    cleanUp();
}

RenderWindow::RenderWindow (const char* WINDOW_TITLE, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // cho may ao:
    //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) {
        std::cout << "Could not create window. Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //add ...accelerated | SDL_RENDERER_PRESENTVSYNC)
    //Khi chay o may ao
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
}

SDL_Texture* RenderWindow::loadTexture (const char* _filePath) {
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(renderer, _filePath);

    if (texture == nullptr) {
        std::cout << "Could not load texture. Error: " << SDL_GetError() << std::endl;
    }
    return texture;
}

//int RenderWindow::getRefreshRate() {
//  int displayIndex = SDL_GetWindowDisplayIndex(window);
//  SDL_DisplayMode mode;
//  SDL_GetDisplayMode(displayIndex, 0, &mode);
//  return mode.refresh_rate;
//}


void RenderWindow::cleanUp() {
    //text.close();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void RenderWindow::_clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::render (Entity& p_entity, const double& p_ratio) {
    SDL_Rect src;
    src.x = p_entity.getCurrentFrame().x;
    src.y = p_entity.getCurrentFrame().y;
    src.w = p_entity.getCurrentFrame().w;
    src.h = p_entity.getCurrentFrame().h;

    SDL_Rect dst;
    dst.x = p_entity.getPos().x;
    dst.y = p_entity.getPos().y;
    dst.w = p_entity.getCurrentFrame().w * p_ratio;
    dst.h = p_entity.getCurrentFrame().h * p_ratio;

    //SDL_RenderCopy(renderer, _texture, NULL, NULL);
    SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}
/*
Text RenderWindow::getText() {
    return text;
}
*/
/*
SDL_Renderer* RenderWindow::getRenderer() {
    return renderer;
}
*/

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}
/*
void RenderWindow::renderText(double x, double y, Entity &p_entity)
{

    if (!loadMedia()) {
        std::cout << "Failed to load media - text" << std::endl;
    }

	const double temp = 1;
	render(p_entity, temp);

	//Render to screen
    //display();
}

bool RenderWindow::loadMedia()
{
	//Loading success flag
	bool success = true;

	text.font = TTF_OpenFont( "Kaph-Regular.ttf", 28 );
	if( text.font == NULL )
	{
		std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
		success = false;
	}
	else
	{
		SDL_Color textColor = {130, 69, 19};
		if( !text.loadFromRenderedText( "The quick brown fox jumps over the lazy dog", textColor, renderer ) )
		{
			std::cout << "Failed to render text texture!" << std::endl;
			success = false;
		}
	}

	return success;
}

*/
