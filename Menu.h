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
#include "Icon.h"
#include "Const_Vars.h"

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

    Icon musicIcon;

public:
    bool play = false;


    ~Menu();
    void clearVector();
    void cleanMenu();
    void render(RenderWindow& p_window, const double& p_ratio);

    void handleMusicIcon (RenderWindow& p_window, SDL_Event& p_event);


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
