#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "VectorMath.h"
#include "RenderWindow.h"
#include "Background.h"
#include "Entity.h"

Background::~Background() {
    cleanBackground();
}

void Background::updateBackground(Entity p_entity) {
    backgroundEntities.push_back(p_entity);
}

void Background::renderBackground(RenderWindow& p_window, const double& p_ratio) {
    for (Entity& e : backgroundEntities) {
        p_window.render(e, p_ratio);
    }
}

void Background::cleanBackground() {
    SDL_DestroyTexture(loadBackground);
    loadBackground = nullptr;
    clearVector();
}


void Background::clearVector() {
    backgroundEntities.clear();
}

void Background::renderGrassBackground(RenderWindow& p_window) {
    cleanBackground();

    loadBackground = p_window.loadTexture("GrassHillTiles.png");

    clearVector();

    for (int i = 0; i * grassBackgroundHeight * grassBackgroundRatio < SCREEN_HEIGHT; i++) {
        updateBackground(Entity(VectorMath(0, i * grassBackgroundHeight * grassBackgroundRatio), grassBackground_rect, loadBackground));
        updateBackground(Entity(VectorMath(HALF_SCREEN_WIDTH, i * grassBackgroundHeight * grassBackgroundRatio), grassBackground_rect, loadBackground));
    }

    renderBackground(p_window, grassBackgroundRatio);
    cleanBackground();
}

void Background::renderDropArea(RenderWindow& p_window) {
    cleanBackground();

    loadBackground = p_window.loadTexture("TreesAndFruits.png");

    updateBackground(Entity(VectorMath(leftBorder, SCREEN_HEIGHT - bottomBorder - boulderHeight * boulderRatio), boulder_rect, loadBackground));
    updateBackground(Entity(VectorMath(leftBorder + boulderWidth * boulderRatio + dropAreaWidth, SCREEN_HEIGHT - bottomBorder - boulderHeight * boulderRatio), boulder_rect, loadBackground));

    renderBackground(p_window, boulderRatio);

    clearVector();

    for (int i = 0; SCREEN_HEIGHT - bottomBorder - boulderHeight * boulderRatio - tallTreeHeight * tallTreeRatio - (i * tallTreeHeight * tallTreeRatio) > 0; i++) {
        updateBackground(Entity(VectorMath(leftBorder + alignTree_boulder, SCREEN_HEIGHT - bottomBorder - boulderHeight * boulderRatio - tallTreeHeight * tallTreeRatio - (i * tallTreeHeight * tallTreeRatio)),tallTree_rect, loadBackground));
        updateBackground(Entity(VectorMath(leftBorder + boulderWidth * boulderRatio + dropAreaWidth + alignTree_boulder, SCREEN_HEIGHT - bottomBorder - boulderHeight * boulderRatio - tallTreeHeight * tallTreeRatio - (i * tallTreeHeight * tallTreeRatio)), tallTree_rect, loadBackground));
    }

    renderBackground(p_window, tallTreeRatio);

    clearVector();

    for (int i = 0; leftBorder + boulderWidth * boulderRatio + 2 * i * budWidth * budRatio < leftBorder + boulderWidth * boulderRatio + dropAreaWidth; i++) {
        updateBackground(Entity(VectorMath(leftBorder + boulderWidth * boulderRatio + 2 * i * budWidth * budRatio, SCREEN_HEIGHT - bottomBorder - budRatio * budHeight), pinkBud_rect, loadBackground));
        updateBackground(Entity(VectorMath(leftBorder + boulderWidth * boulderRatio + budWidth * budRatio + 2 * i * budWidth * budRatio, SCREEN_HEIGHT - bottomBorder - boulderHeight * boulderRatio), yellowBud_rect, loadBackground));

    }

    renderBackground(p_window, budRatio);
    cleanBackground();
}

void Background::renderDropAreaBackground(RenderWindow& p_window) {
    cleanBackground();

    loadBackground = p_window.loadTexture("DirtTiles.png");

    updateBackground(Entity(VectorMath(leftBorder + tallTreeWidth * tallTreeRatio, SCREEN_HEIGHT - bottomBorder - boulderHeight * boulderRatio - dirtBackgroundHeight * dirtBackgroundRatio), dirtBackground_rect, loadBackground));
    updateBackground(Entity(VectorMath(leftBorder + tallTreeWidth * tallTreeRatio, topBorder + dirtBackgroundBlendHeight * dirtBackgroundBlendRatio), dirtBackground_rect, loadBackground));


    renderBackground(p_window, dirtBackgroundRatio);

    clearVector();

    updateBackground(Entity(VectorMath(leftBorder + tallTreeWidth * tallTreeRatio, topBorder), dirtBackgroundBlend_rect, loadBackground));

    renderBackground(p_window, dirtBackgroundBlendRatio);

    cleanBackground();
}
