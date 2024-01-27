// credits_scene.cpp
#include "credits_scene.h"
#include "../Utils/Utils.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"

CreditsScene::CreditsScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : BaseScene(renderer),
    musicPlayer(musicPlayer),
    soundPlayer(soundPlayer),
    backgroundTexture(loadTexture("Assets/Sprites/Main_menu.png", renderer)),
    returnToMenuButton(loadTexture("Assets\\Sprites\\Buttons\\Back_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Back_button_hover.png", renderer),
        400, 400, &soundPlayer) {

    // Текст для сцены кредитов
    creditsTextLines = {
        "Об авторе:",
        "КУРСОВАЯ РАБОТА",
        "на тему",
        "Игра «TankiGame»",
        "Выполнил студент группы А821С19",
        "Сапронов Д.Е.",
        "2024"
    };
}

void CreditsScene::handleEvents(const SDL_Event& event, GameState& gameState) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mousePoint = { x, y };

    returnToMenuButton.isHovered = SDL_PointInRect(&mousePoint, &returnToMenuButton.position);

    if (event.type == SDL_MOUSEBUTTONDOWN && returnToMenuButton.isHovered) {
        returnToMenuButton.isClicked = true;
    }
}

void CreditsScene::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    returnToMenuButton.render(renderer);

    // Рендеринг текста кредитов
    SDL_Color redColor = { 255, 0, 0, 255 }; // Красный цвет для текста
    SDL_Color textColor = { 0, 0, 0, 255 }; // Цвет текста

    int y = 75; // Начальная позиция Y
    int x = 250; // Начальная позиция X

    for (const auto& line : creditsTextLines) {
        if (line == "КУРСОВАЯ РАБОТА" ||
            line == "Игра «TankiGame»" ||
            line == "2024") {
            renderText(renderer, line, x - 15, y, 25, redColor); // Рендеринг красного текста
        }
        else {
            renderText(renderer, line, x, y, 25, textColor); // Рендеринг обычного текста
        }
        y += 45; // Смещение для следующей строки
    }


    SDL_RenderPresent(renderer);
}

GameState CreditsScene::updateState() {
    if (returnToMenuButton.isClicked) {
        returnToMenuButton.isClicked = false;
        return GameState::MainMenu;
    }
    return GameState::Credits;
}
