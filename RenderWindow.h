#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Entity.h"
//#include "Background.h"
#include "VectorMath.h"
#include "Text.h"
#include "Food.h"

//using namespace std;

class RenderWindow {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    //Text text;
public:
    ~RenderWindow();
    RenderWindow(const char* WINDOW_TITLE, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    SDL_Texture* loadTexture(const char* _filePath);

    //bool loadMedia();
    //Text getText();
    //SDL_Renderer* getRenderer();
    //void renderText (double x, double y, Entity &p_entity);

    //if the VSYNC doesnt work:
    //int getRefreshRate();
    void cleanUp();
    void _clear();
    void render(Entity& p_entity, const double& p_ratio);
    void display();

};

