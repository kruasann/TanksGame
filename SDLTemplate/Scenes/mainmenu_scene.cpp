// mainmenu_scene.cpp
#include "mainmenu_scene.h"
#include "../game_states.h"
#include "../Utils/Utils.h"
#include <iostream>

MainMenuScene::MainMenuScene(SDL_Renderer* ren, Button startBtn, Button settingsBtn, Button exitBtn, SDL_Texture* bgTexture)
    : renderer(ren), buttonStart(startBtn), buttonSettings(settingsBtn), buttonExit(exitBtn), backgroundTexture(bgTexture) {}

void MainMenuScene::handleEvents(const SDL_Event& event) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mousePoint = { x, y };

    buttonStart.isHovered = SDL_PointInRect(&mousePoint, &buttonStart.position);
    buttonSettings.isHovered = SDL_PointInRect(&mousePoint, &buttonSettings.position);
    buttonExit.isHovered = SDL_PointInRect(&mousePoint, &buttonExit.position);

    std::cout << "Start Button Hovered: " << buttonStart.isHovered << std::endl;
    std::cout << "Settings Button Hovered: " << buttonSettings.isHovered << std::endl;
    std::cout << "Exit Button Hovered: " << buttonExit.isHovered << std::endl;

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (buttonStart.isHovered) {
            buttonStart.isClicked = true;
        }
        else if (buttonSettings.isHovered) {
            buttonSettings.isClicked = true;
        }
        else if (buttonExit.isHovered) {
            buttonExit.isClicked = true;
        }
    }
}

void MainMenuScene::render() {
    std::cout << "Rendering Main Menu Scene" << std::endl;
    SDL_RenderClear(renderer);
    renderTexture(backgroundTexture, renderer, 0, 0);
    buttonStart.render(renderer);
    buttonSettings.render(renderer);
    buttonExit.render(renderer);
    SDL_RenderPresent(renderer);
}

GameState MainMenuScene::updateState() {
    if (buttonStart.isClicked) {
        buttonStart.isClicked = false;
        return GameState::Playing;
    }
    else if (buttonSettings.isClicked) {
        buttonSettings.isClicked = false;
        return GameState::Settings;
    }
    else if (buttonExit.isClicked) {
        buttonExit.isClicked = false;
        return GameState::Exit;
    }

    return GameState::MainMenu;
}

