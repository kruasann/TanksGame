#include "WinScene.h"
#include "../Utils/Utils.h"
#include <iostream>

// Конструктор класса WinScene.
WinScene::WinScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(renderer),
    returnToMenuButton(loadTexture("Assets/Sprites/Buttons/Menu_button.png", renderer),
        loadTexture("Assets/Sprites/Buttons/Menu_button_hover.png", renderer),
        400, 600, &soundPlayer),
    backgroundTexture(loadTexture("Assets/Sprites/Win_Menu.png", renderer)) {
}

// Деструктор класса WinScene.
WinScene::~WinScene() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture); // Освобождение ресурсов фоновой текстуры
    }
}

// Обработка событий в сцене победы.
void WinScene::handleEvents(const SDL_Event& event, GameState& gameState) {
    int x, y;
    SDL_GetMouseState(&x, &y); // Получение состояния мыши
    SDL_Point mousePoint = { x, y }; // Точка положения курсора

    // Проверка, находится ли курсор на кнопке "Вернуться в меню".
    returnToMenuButton.isHovered = SDL_PointInRect(&mousePoint, &returnToMenuButton.position);

    // Обработка клика мыши
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (returnToMenuButton.isHovered) {
            returnToMenuButton.isClicked = true; // Установка флага клика по кнопке
        }
    }
}

// Рендеринг сцены победы.
void WinScene::render() {
    renderTexture(backgroundTexture, renderer, 0, 0); // Отрисовка фона
    returnToMenuButton.render(renderer); // Отрисовка кнопки "Вернуться в меню"
    SDL_RenderPresent(renderer); // Обновление экрана
}

// Обновление состояния сцены победы.
GameState WinScene::updateState() {
    if (returnToMenuButton.isClicked) {
        returnToMenuButton.isClicked = false;
        return GameState::MainMenu; // Переход в главное меню
    }
    return GameState::Win; // Оставаться в сцене победы
}
