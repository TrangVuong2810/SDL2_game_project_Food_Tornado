#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "Background.h"
#include "VectorMath.h"
#include "Food.h"
#include "Basket.h"
#include "Button.h"
#include "Menu.h"
#include "Icon.h"

Menu::~Menu() {
    cleanMenu();
}

void Menu::clearVector() {
    menuEntities.clear();
}

void Menu::cleanMenu() {
    SDL_DestroyTexture(loadMenuBackground);
    loadMenuBackground = nullptr;
    clearVector();
}

void Menu::render(RenderWindow& p_window, const double& p_ratio) {
    for (Entity& e : menuEntities) {
        p_window.render(e, p_ratio);
    }
}

void Menu::setButtonSprite(Button& p_button) {
    //clearVector();
    menuEntities.push_back(p_button.buttonEntity());

}

void Menu::renderDefaultMenu(RenderWindow& p_window) {
    cleanMenu();

    loadButtons(p_window);

    menuEntities.push_back(Entity(rootPos, fullScreenRect, loadMenuBackground));

    render(p_window, fullScreenRatio);

    clearVector();

    cow.loadMedia(p_window, cowFilePath.c_str());
    renderCow();

    render(p_window, cowRatio);

    clearVector();

    bear.loadMedia(p_window, bearFilePath.c_str());
    renderBear();

    render(p_window, bearRatio);

    clearVector();

    setButtonSprite(playButton);

    setButtonSprite(gameButton);

    setButtonSprite(inforButton);

    setButtonSprite(aboutButton);

    render(p_window, buttonRatio);

    clearVector();

    menuEntities.push_back(musicIcon.iconEntity());

    render(p_window, iconRatio);

}

void Menu::renderMenu(RenderWindow& p_window, SDL_Event& p_event) {
    cleanMenu();

    loadButtons(p_window);

    menuEntities.push_back(Entity(rootPos, fullScreenRect, loadMenuBackground));

    render(p_window, fullScreenRatio);

    clearVector();

    cow.loadMedia(p_window, cowFilePath.c_str());
    renderCow();

    render(p_window, cowRatio);

    clearVector();

    bear.loadMedia(p_window, bearFilePath.c_str());
    renderBear();

    render(p_window, bearRatio);

    clearVector();

    handlePlayButton(p_window, p_event);
    setButtonSprite(playButton);

    handleGameButton(p_window, p_event);
    setButtonSprite(gameButton);

    handleInforButton(p_window, p_event);
    setButtonSprite(inforButton);

    handleAboutButton(p_window, p_event);
    setButtonSprite(aboutButton);

    render(p_window, buttonRatio);

    clearVector();

    handleMusicIcon(p_window, p_event);
    menuEntities.push_back(musicIcon.iconEntity());

    render(p_window, iconRatio);

}

void Menu::handleMusicIcon (RenderWindow& p_window, SDL_Event& p_event) {
        if (musicIcon.isInside(p_event)) {
        switch (p_event.type) {
        case SDL_MOUSEMOTION:
            if (Mix_PausedMusic() == 1) musicIcon.currentSprite = ICON_MOUSE_CLICK;
            else musicIcon.currentSprite = ICON_MOUSE_DEFAULT;
            break;
        case SDL_MOUSEBUTTONDOWN:
            Mix_PlayChannel(-1, p_window.getMix_Chunk(2), 0);
            if (Mix_PausedMusic() == 1) {
                    Mix_ResumeMusic();
                    p_window.playingMusic = true;
            }

            else {
                    Mix_PauseMusic();
                    p_window.playingMusic = false;
            }

            if (Mix_PausedMusic() == 1) musicIcon.currentSprite = ICON_MOUSE_CLICK;
            else musicIcon.currentSprite = ICON_MOUSE_DEFAULT;
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        }
    }
    else  {
        if (Mix_PausedMusic() == 1) musicIcon.currentSprite = ICON_MOUSE_CLICK;
        else musicIcon.currentSprite = ICON_MOUSE_DEFAULT;
    }
}

void Menu::handleGameButton(RenderWindow& p_window, SDL_Event& p_event) {
    //cleanMenu();

    if (gameButton.isInside(p_event)) {
        switch (p_event.type) {
        case SDL_MOUSEMOTION:
            gameButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            gameButton.currentSprite = BUTTON_MOUSE_OVER;

            Mix_PlayChannel(-1, p_window.getMix_Chunk(1), 0);

            bool readingDone = false;

            while (!readingDone) {
                if (SDL_PollEvent(&p_event) != 0 ) {
                    if (p_event.type == SDL_QUIT) {
                        readingDone = true;
                        cleanMenu();
                    }
                    else if (backButton.isInside(p_event)) {
                        switch (p_event.type) {
                        case SDL_MOUSEMOTION:
                            backButton.currentSprite = BUTTON_MOUSE_OVER;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            backButton.currentSprite = BUTTON_MOUSE_OVER;
                            Mix_PlayChannel(-1, p_window.getMix_Chunk(2), 0);
                            readingDone = true;


                            break;
                        }
                    }
                    else {
                        backButton.currentSprite = BUTTON_MOUSE_OUT;
                    }
                    do {
                        //render story
                        p_window._clear();
                        cleanMenu();

                        loadMenuBackground = p_window.loadTexture(storyBackground.c_str());
                        menuEntities.push_back(Entity(rootPos, fullScreenRect, loadMenuBackground));

                        render(p_window, fullScreenRatio);


                    } while (SDL_PollEvent(&p_event) != 0);

                //loadButtons(p_window);
                menuEntities.push_back(backButton.buttonEntity());

                render(p_window, backButtonRatio);

                p_window.display();


                }
            }
            break;
        }
    }
    else {
        gameButton.currentSprite = BUTTON_MOUSE_OUT;
    }

}

void Menu::handleInforButton(RenderWindow& p_window, SDL_Event& p_event) {
    //cleanMenu();

        if (inforButton.isInside(p_event)) {
        switch (p_event.type) {
        case SDL_MOUSEMOTION:
            inforButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            inforButton.currentSprite = BUTTON_MOUSE_OVER;
            Mix_PlayChannel(-1, p_window.getMix_Chunk(1), 0);

            bool readingDone = false;
            SDL_Delay(500);

            while (!readingDone) {
                if (SDL_PollEvent(&p_event) != 0) { // && (p_event.type == SDL_MOUSEBUTTONDOWN || p_event.type == SDL_MOUSEMOTION)) {
                    if (p_event.type == SDL_QUIT) {
                        readingDone = true;
                        cleanMenu();
                    }
                    else if (backButton.isInside(p_event)) {
                        switch (p_event.type) {
                        case SDL_MOUSEMOTION:
                            backButton.currentSprite = BUTTON_MOUSE_OVER;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            backButton.currentSprite = BUTTON_MOUSE_OVER;
                            Mix_PlayChannel(-1, p_window.getMix_Chunk(2), 0);
                            readingDone = true;

                            break;
                        }
                    }
                    else {
                        backButton.currentSprite = BUTTON_MOUSE_OUT;
                    }
                    do {

                        //render instrction
                        p_window._clear();
                        cleanMenu();

                        loadMenuBackground = p_window.loadTexture(instructionBackground.c_str());
                        menuEntities.push_back(Entity(rootPos, fullScreenRect, loadMenuBackground));

                        render(p_window, fullScreenRatio);


                    } while (SDL_PollEvent(&p_event) != 0); // && (p_event.type == SDL_MOUSEBUTTONDOWN || p_event.type == SDL_MOUSEMOTION));

                //loadButtons(p_window);
                menuEntities.push_back(backButton.buttonEntity());

                render(p_window, backButtonRatio);

                p_window.display();


                }
            }
            break;
        }
    }
    else {
        inforButton.currentSprite = BUTTON_MOUSE_OUT;
    }

}

void Menu::handleAboutButton(RenderWindow& p_window, SDL_Event& p_event) {
    //cleanMenu();

        if (aboutButton.isInside(p_event)) {
        switch (p_event.type) {
        case SDL_MOUSEMOTION:
            aboutButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            aboutButton.currentSprite = BUTTON_MOUSE_OVER;
            Mix_PlayChannel(-1, p_window.getMix_Chunk(1), 0);

            bool readingDone = false;

            SDL_Delay(500);

            while (!readingDone) {
                if (SDL_PollEvent(&p_event) != 0 ) {// && (p_event.type == SDL_MOUSEBUTTONDOWN || p_event.type == SDL_MOUSEMOTION)) {
                    if (p_event.type == SDL_QUIT) {
                        readingDone = true;
                        cleanMenu();
                    }
                    else if (backButton.isInside(p_event)) {
                        switch (p_event.type) {
                        case SDL_MOUSEMOTION:
                            backButton.currentSprite = BUTTON_MOUSE_OVER;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            backButton.currentSprite = BUTTON_MOUSE_OVER;
                            Mix_PlayChannel(-1, p_window.getMix_Chunk(2), 0);
                            readingDone = true;

                            break;
                        }
                    }
                    else {
                        backButton.currentSprite = BUTTON_MOUSE_OUT;
                    }
                    do {

                        //render credit
                        p_window._clear();
                        cleanMenu();

                        loadMenuBackground = p_window.loadTexture(creditBackground.c_str());
                        menuEntities.push_back(Entity(rootPos, fullScreenRect, loadMenuBackground));

                        render(p_window, fullScreenRatio);


                    } while (SDL_PollEvent(&p_event) != 0);

                //loadButtons(p_window);
                menuEntities.push_back(backButton.buttonEntity());

                render(p_window, backButtonRatio);

                p_window.display();


                }
            }
            break;
        }
    }
    else {
        aboutButton.currentSprite = BUTTON_MOUSE_OUT;
    }


}



void Menu::handlePlayButton(RenderWindow& p_window, SDL_Event& p_event) {
    //cleanMenu();

        if (playButton.isInside(p_event)) {
        switch (p_event.type) {
        case SDL_MOUSEMOTION:
            playButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            playButton.currentSprite = BUTTON_MOUSE_OVER;

            play = true;
            Mix_PlayChannel(-1, p_window.getMix_Chunk(1), 0);
            break;
        }
    }
    else {
        playButton.currentSprite = BUTTON_MOUSE_OUT;
    }


}

void Menu::renderBear() {

    menuEntities.push_back(bear.bearEntity());
}




void Menu::renderCow() {

    menuEntities.push_back(cow.cowEntity());

 }

void Menu::loadButtons(RenderWindow& p_window) {
    cleanMenu();

    loadMenuBackground = p_window.loadTexture(menuBackground.c_str());

    playButton.loadMedia(p_window, menuPlayButtonFilePath.c_str());
    playButton.setPosition(menuPlayButtonPos.x, menuPlayButtonPos.y);

    gameButton.loadMedia(p_window, menuGameButtonFilePath.c_str());
    gameButton.setPosition(menuGameButtonPos.x, menuGameButtonPos.y);

    inforButton.loadMedia(p_window, menuInforButtonFilePath.c_str());
    inforButton.setPosition(menuInforButtonPos.x, menuInforButtonPos.y);

    aboutButton.loadMedia(p_window, menuAboutButtonFilePath.c_str());
    aboutButton.setPosition(menuAboutButtonPos.x, menuAboutButtonPos.y);

    backButton.loadMedia(p_window, backButtonFilePath.c_str());
    backButton.setPosition(rootPos.x, rootPos.y);

    musicIcon.loadMedia (p_window, musicIconFilePath.c_str());
    musicIcon.setPosition(musicIconPos.x, musicIconPos.y);
}
