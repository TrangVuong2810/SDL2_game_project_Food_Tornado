#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "VectorMath.h"
#include "Food.h"
#include "Button.h"
#include "Cow.h"
#include "Bear.h"

const std::string menuPlayButtonFilePath = {"playButton.png"}; //play
const std::string menuGameButtonFilePath = {"gameButton.png"}; //story
const std::string menuInforButtonFilePath = {"informationButton.png"}; //how to play
const std::string menuAboutButtonFilePath = {"aboutButton.png"}; //credit
const std::string backButtonFilePath = {"backButton.png"};

const std::string menuBackground = {"menuBackground.png"};
const std::string storyBackground = {"story.png"}; //game
const std::string instructionBackground = {"instruction.png"}; //infor
const std::string creditBackground = {"credit.png"}; //about

const VectorMath menuPlayButtonPos = {100, 100};
const VectorMath menuGameButtonPos = {100, 200};
const VectorMath menuInforButtonPos = {100, 300};
const VectorMath menuAboutButtonPos = {100, 400};
const VectorMath rootPos = {0, 0};

const SDL_Rect fullScreenRect = {0, 0, 800, 600};

const double fullScreenRatio = 1;
const double buttonRatio = 1.5;
const double backButtonRatio = 1;

class Menu {
private:
    std::vector<Entity> menuEntities;
    SDL_Texture* loadMenuBackground = nullptr;

    Cow cow;
    Bear bear;

    Button playButton;
    Button gameButton;
    Button inforButton;
    Button aboutButton;
    Button backButton;

public:
    bool play = false;


    ~Menu();
    void clearVector();
    void cleanMenu();
    void render(RenderWindow& p_window, const double& p_ratio);


    void setButtonSprite(Button& p_button);


    void handleGameButton (RenderWindow& p_window, SDL_Event& p_event);
    void handleInforButton (RenderWindow& p_window, SDL_Event& p_event);
    void handleAboutButton (RenderWindow& p_window, SDL_Event& p_event);
    void handlePlayButton (RenderWindow& p_window, SDL_Event& p_event);

    void renderDefaultMenu(RenderWindow& p_window);
    void renderMenu (RenderWindow& p_window, SDL_Event& p_event);
    void renderCow();
    void renderBear();

    void loadButtons(RenderWindow& p_window);
};
