#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

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
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}


int main (int argc, char* argv[]) {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init failed. Error: " << SDL_GetError() << std::endl;
    }

    RenderWindow window(WINDOW_TITLE.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT);

    Mechanism mechanism;


    window.display();

    mechanism.playGame(window);

    waitUntilKeyPressed();

    window._clear();
    window.cleanUp();
    SDL_Quit();

    return 0;
}

