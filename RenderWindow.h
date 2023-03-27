#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Entity.h"
#include "VectorMath.h"

//using namespace std;

class RenderWindow {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;


    Mix_Music* music = nullptr;

    Mix_Chunk* menu_click = nullptr; //1
    Mix_Chunk* menu_back = nullptr; //2

    Mix_Chunk* dead = nullptr; //3
    Mix_Chunk* scored = nullptr; //4
    Mix_Chunk* missed = nullptr; //5

public:

    ~RenderWindow();
    RenderWindow(const char* WINDOW_TITLE, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    SDL_Texture* loadTexture(const char* _filePath);

    void loadMusic();
    Mix_Chunk* getMix_Chunk(int soundIndex);

    void cleanUp();
    void _clear();
    void render(Entity& p_entity, const double& p_ratio);
    void display();

};

