// leaderboard_scene.cpp
#include "leaderboard_scene.h"
#include "../Utils/Utils.h"

LeaderboardScene::LeaderboardScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(renderer),
    musicPlayer(musicPlayer),
    soundPlayer(soundPlayer),
    backgroundTexture(loadTexture("Assets/Sprites/Main_menu.png", renderer)),
    returnToMenuButton(loadTexture("Assets\\Sprites\\Buttons\\Back_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Back_button_hover.png", renderer),
        400, 400, &soundPlayer) {
}

void LeaderboardScene::handleEvents(const SDL_Event& event) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mousePoint = { x, y };

    returnToMenuButton.isHovered = SDL_PointInRect(&mousePoint, &returnToMenuButton.position);

    if (event.type == SDL_MOUSEBUTTONDOWN && returnToMenuButton.isHovered) {
        returnToMenuButton.isClicked = true;
    }
}

void LeaderboardScene::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    returnToMenuButton.render(renderer);

    SDL_RenderPresent(renderer);
}

GameState LeaderboardScene::updateState() {
    if (returnToMenuButton.isClicked) {
        returnToMenuButton.isClicked = false;
        return GameState::MainMenu;
    }
    return GameState::Leaderboard;
}
