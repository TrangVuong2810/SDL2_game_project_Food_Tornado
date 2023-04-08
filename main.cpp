#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "Background.h"
#include "VectorMath.h"
#include "Food.h"
#include "Basket.h"
#include "Mechanism.h"

//using namespace std;

void waitUntilKeyPressed() {
    SDL_Event e;
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (keyboardState[SDL_SCANCODE_ESCAPE] || e.type == SDL_QUIT) )
            return;
        //SDL_Delay(100);
    }
}

int main (int argc, char* argv[]) {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init failed. Error: " << SDL_GetError() << std::endl;
    }
    if( TTF_Init() == -1 ) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

    RenderWindow window(WINDOW_TITLE.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT);

    window.playMusic();

    Mechanism mechanism;

    window.display();

    mechanism.startMenu(window);

    while (window.wait) {
        mechanism.playAgain(window);
        window.display();
    }

    window._clear();
    window.cleanUp();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();

    return 0;
}

