// settings_scene.cpp
#include "settings_scene.h"
#include "../Objects/button.h"
#include "../Utils/Utils.h"

SettingsScene::SettingsScene(SDL_Renderer* ren, Button backBtn, SDL_Texture* bgTexture)
    : renderer(ren), backButton(backBtn), backgroundTexture(bgTexture) {}

void SettingsScene::handleEvents(const SDL_Event& event) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mousePoint = { x, y };

    backButton.isHovered = SDL_PointInRect(&mousePoint, &backButton.position);

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (backButton.isHovered) {
            backButton.isClicked = true;
        }
    }
}

void SettingsScene::render() {
    SDL_RenderClear(renderer);
    renderTexture(backgroundTexture, renderer, 0, 0);
    backButton.render(renderer);
    // Отрисовка ползунка громкости и кнопки громкости
    SDL_RenderPresent(renderer);
}

GameState SettingsScene::updateState()
{
    if (backButton.isClicked) {
        backButton.isClicked = false;
        return GameState::MainMenu;
    }
    return GameState::Settings;
}
