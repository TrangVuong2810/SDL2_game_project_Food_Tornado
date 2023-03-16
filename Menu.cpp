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
#include "Menu.h"

Menu::~Menu() {
    cleanMenu();
}

void Menu::clearVector() {
    menuEntities.clear();
}

void Menu::cleanMenu() {
    //SDL_DestroyTexture(loadMenu);
    //loadMenu = nullptr;
    clearVector();
}

void Menu::render(RenderWindow& p_window, const double& p_ratio) {
    for (Entity& e : menuEntities) {
        p_window.render(e, p_ratio);
    }
}

void Menu::renderMenu(RenderWindow& p_window, SDL_Event& p_event) {
    clearVector();

    loadButtons(p_window);
    /*

    for (int i = 0; i < 4; i++) {
        if (button[i].isInside(p_event)) {

            switch (p_event.type) {
            case SDL_MOUSEMOTION:
                button[i].currentSprite = BUTTON_MOUSE_OVER;
                break;
            case SDL_MOUSEBUTTONDOWN:
                button[i].currentSprite = BUTTON_MOUSE_OVER;

                bool doneHover = false;
                while (!doneHover) {
                    if (p_event.type == SDL_QUIT) {
                        doneHover = true;
                        cleanMenu();
                    }
                    else {
                        while (SDL_PollEvent(&p_event)) {
                            if (button[i].isInside(p_event)) {
                                switch (p_event.type) {
                                case SDL_MOUSEMOTION:
                                    button[i].currentSprite = BUTTON_MOUSE_OVER;
                                    break;
                                case SDL_MOUSEBUTTONDOWN:
                                    button[i].currentSprite = BUTTON_MOUSE_OVER;
                                    //add sound here
                                    doneHover = true;
                                    break;
                                }
                            }
                            else {
                                button[i].currentSprite = BUTTON_MOUSE_OUT;
                            }
                            //
                        }
                    }
                }
                break;
            }
        }
        else {
            button[i].currentSprite = BUTTON_MOUSE_OUT;
        }

    }
    */
    for (int i = 0; i < BUTTON_TOTAL; i++) {
        if (button[i].isInside(p_event)) {
            switch (p_event.type) {
            case SDL_MOUSEMOTION:
                button[i].currentSprite = BUTTON_MOUSE_OVER;
                break;
            case SDL_MOUSEBUTTONDOWN:
                button[i].currentSprite = BUTTON_MOUSE_OVER;
                //sound

                break;
            }
        }
        else button[i].currentSprite = BUTTON_MOUSE_OUT;
    }


    for (int i = 0; i < BUTTON_TOTAL; i++) {
        if (button[i].currentSprite == BUTTON_MOUSE_OUT) {
            menuEntities.push_back(button[i].buttonEntity(menuButtons, p_window));
        }
        else if (button[i].currentSprite == BUTTON_MOUSE_OVER) {
            menuEntities.push_back(button[i].buttonEntity(menuButtonsHover, p_window));
        }
    }


    render(p_window, buttonRatio);
}

void Menu::handleTrivialButtons(RenderWindow& p_window, SDL_Event& p_event) {

}

void Menu::handlePlayButton(RenderWindow& p_window, SDL_Event& p_event) {

}




void Menu::loadButtons(RenderWindow& p_window) {
    cleanMenu();

    for (int i = 0; i < BUTTON_TOTAL; i++) {
        button[i].loadMedia(p_window, menuButtonsFilePath[i].c_str());
        button[i].setPosition(menuTrivialButtonsPos[i].x, menuTrivialButtonsPos[i].y);
    }

}
