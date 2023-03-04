#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Entity.h"
//#include "Background.h"
#include "VectorMath.h"

//using namespace std;

const double SCREEN_WIDTH = 800;
const double HALF_SCREEN_WIDTH = 400;
const double SCREEN_HEIGHT = 600;
const std::string WINDOW_TITLE = "Food Tornado";

class RenderWindow {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    RenderWindow(const char* WINDOW_TITLE, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    SDL_Texture* loadTexture(const char* _filePath);
    //if the VSYNC doesnt work:
    //int getRefreshRate();
    void cleanUp();
    void _clear();
    void render(Entity& p_entity, const double& p_ratio);
    void display();

};

