// leaderboard_scene.cpp
#include "leaderboard_scene.h"
#include "../Utils/Utils.h"
#include <iostream>


LeaderboardScene::LeaderboardScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(renderer),
    musicPlayer(musicPlayer),
    soundPlayer(soundPlayer),
    backgroundTexture(loadTexture("Assets/Sprites/Main_menu.png", renderer)),
    returnToMenuButton(loadTexture("Assets\\Sprites\\Buttons\\Back_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Back_button_hover.png", renderer),
        400, 400, &soundPlayer) {
    leaderboardEntries = readLeaderboard();
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

    // Отображение данных таблицы лидеров
    SDL_Color textColor = { 0, 0, 0, 255 };
    int x = 200; // Начальная координата X для текста
    int y = 100; // Начальная координата Y для текста

    for (const auto& entry : leaderboardEntries) {
        std::string text = entry.date + " " + entry.time + " Time: " + entry.gameDuration + " Score: " + std::to_string(entry.score);
        renderText(renderer, text, x, y, 32, textColor);
        y += 30; // Увеличиваем координату Y
    }

    SDL_RenderPresent(renderer);
}

GameState LeaderboardScene::updateState() {
    if (returnToMenuButton.isClicked) {
        returnToMenuButton.isClicked = false;
        return GameState::MainMenu;
    }
    return GameState::Leaderboard;
}
