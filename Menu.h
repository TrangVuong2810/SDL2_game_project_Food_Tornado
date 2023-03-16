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
#include "Text.h"
#include "Button.h"

const SDL_Rect menuButtons = {0, 0, 144, 72};
const SDL_Rect menuButtonsHover = {0, 72, 144, 72};
const std::string menuButtonsFilePath[4] = {"playButton.png", //play
                                        "gameButton.png",  //story
                                        "informationButton.png", //How to play
                                        "aboutButton.png"}; //credit

const VectorMath menuTrivialButtonsPos[4] = { {100, 100},
                                        {100, 200},
                                        {100, 300},
                                        {100, 400}};
const VectorMath menuPlayButtonPos = {100, 100};

const VectorMath backButtonPos = {0, 0};
const int BUTTON_TOTAL = 4;
const double buttonRatio = 1.5;
const double backButtonRatio = 1;

class Menu {
private:
    std::vector<Entity> menuEntities;
    //SDL_Texture* loadMenu = nullptr;
    Button button[BUTTON_TOTAL];
public:
    ~Menu();
    void clearVector();
    void cleanMenu();
    void render(RenderWindow& p_window, const double& p_ratio);
    void handleTrivialButtons(RenderWindow& p_window, SDL_Event& p_event);
    void handlePlayButton (RenderWindow& p_window, SDL_Event& p_event);
    void renderMenu(RenderWindow& p_window, SDL_Event& p_event);
    void loadButtons(RenderWindow& p_window);
};
