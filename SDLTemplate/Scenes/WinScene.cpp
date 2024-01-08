// WinScene.cpp
#include "WinScene.h"
#include "../Utils/Utils.h"
#include <iostream>

WinScene::WinScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(renderer),
    returnToMenuButton(loadTexture("Assets/Sprites/Buttons/Menu_button.png", renderer),
        loadTexture("Assets/Sprites/Buttons/Menu_button_hover.png", renderer),
        400, 600, &soundPlayer),
    backgroundTexture(loadTexture("Assets/Sprites/Win_Menu.png", renderer)) {
    // Другие настройки
}


// Деструктор сцены паузы.
WinScene::~WinScene() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
    }
}

void WinScene::handleEvents(const SDL_Event& event, GameState& gameState) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mousePoint = { x, y };

    // Определение, находится ли курсор на кнопках.
    returnToMenuButton.isHovered = SDL_PointInRect(&mousePoint, &returnToMenuButton.position);

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        std::cout << "Mouse Button Down at: " << x << ", " << y << std::endl;
        if (returnToMenuButton.isHovered) {
            std::cout << "Button Clicked" << std::endl;
            returnToMenuButton.isClicked = true;
        }
    }
}

void WinScene::render() {
    renderTexture(backgroundTexture, renderer, 0, 0);

    returnToMenuButton.render(renderer);
    SDL_RenderPresent(renderer);
}

GameState WinScene::updateState() {
    if (returnToMenuButton.isClicked) {
        std::cout << "Returning to main menu from win scene" << std::endl;
        returnToMenuButton.isClicked = false;
        return GameState::MainMenu;
    }
    return GameState::Win;
}
