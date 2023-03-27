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

void RenderWindow::cleanUp() {

    Mix_FreeChunk(menu_click);
    Mix_FreeChunk(menu_back);
    Mix_FreeChunk(dead);
    Mix_FreeChunk(scored);
    Mix_FreeChunk(missed);

    menu_click = nullptr;
    menu_back = nullptr;
    dead = nullptr;
    scored = nullptr;
    missed = nullptr;

    Mix_FreeMusic(music);
    music = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
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

void RenderWindow::loadMusic() {
	//Load music
	music = Mix_LoadMUS( "Music.wav" );
	if( music == nullptr ) {
		std::cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl ;
	}

	//Load sound effects
	menu_click = Mix_LoadWAV( "Menu_Click.wav" );
	if( menu_click == nullptr ) {
		std::cout << "Failed to load menu_click sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl ;
	}

	menu_back = Mix_LoadWAV( "Menu_back.wav" );
	if( menu_back == nullptr ) {
		std::cout << "Failed to load menu_back sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

	dead = Mix_LoadWAV( "Dead.wav" );
	if( dead == nullptr ) {
		std::cout << "Failed to load dead sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

	scored = Mix_LoadWAV( "Scored.wav" );
	if( scored == nullptr ) {
		std::cout << "Failed to load scored sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

	missed = Mix_LoadWAV( "Missed.wav" );
	if( missed == nullptr ) {
		std::cout << "Failed to load missed sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;

	}
}

Mix_Chunk* RenderWindow::getMix_Chunk(int soundIndex) {
    switch (soundIndex) {
    case 1:
        std::cout << "OK" <<std::endl;
        return menu_click;
        break;
    case 2:
        return menu_back;
        break;
    case 3:
        return dead;
        break;
    case 4:
        return scored;
        break;
    case 5:
        return missed;
        break;
    }
    std::cout << "UHO" <<std::endl;
    return nullptr;
}

void RenderWindow::playMusic() {
    loadMusic();

    Mix_PlayMusic(music, -1);
}

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}

