#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


struct VectorMath {
    double x, y;
    VectorMath() {
        x = 0;
        y = 0;
    }
    VectorMath(double p_x, double p_y) {
        x = p_x;
        y = p_y;
    }
    void setVectorMath (double p_x, double p_y) {
        x = p_x;
        y = p_y;
    }
};


