// help_scene.cpp
#include "help_scene.h"
#include "../Utils/Utils.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"

HelpScene::HelpScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(renderer),
    musicPlayer(musicPlayer),
    soundPlayer(soundPlayer),
    backgroundTexture(loadTexture("Assets/Sprites/Main_menu.png", renderer)),
    returnToMenuButton(loadTexture("Assets\\Sprites\\Buttons\\Back_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Back_button_hover.png", renderer),
        400, 450, &soundPlayer) {

    helpTextLines = {
        "Добро пожаловать в мир танковых баталий!",
        "Вы – командир танка, великолепной машины, созданной для разрушения и победы.",
        "Каждая пораженная мишень приближает вас к званию лучшего танкиста.",
        "Но будьте осторожны, время – ваш главный враг.", 
        "Сможете ли вы стать легендой?",
        "Инструкции по управлению:",
        "W и S: Движение вперед и назад. Эти клавиши помогут вам маневрировать по полю боя.",
        "A и D: Вращение башни танка. Используйте эти клавиши для цели и огня.",
        "Пробел: Выстрел. Нажмите, чтобы атаковать мишени.",
        "Цель игры:",
        "Ваша миссия – поразить все мишени на уровне как можно быстрее.",
        "Быстрое выполнение задачи увеличит ваш счет и престиж.",
        "Удачи"
    };
}

void HelpScene::handleEvents(const SDL_Event& event) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mousePoint = { x, y };

    returnToMenuButton.isHovered = SDL_PointInRect(&mousePoint, &returnToMenuButton.position);

    if (event.type == SDL_MOUSEBUTTONDOWN && returnToMenuButton.isHovered) {
        returnToMenuButton.isClicked = true;
    }
}

void HelpScene::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    returnToMenuButton.render(renderer);

    // Рендеринг текста помощи
    SDL_Color redColor = { 255, 0, 0, 255 }; // Красный цвет для текста

    int y = 25; // Начальная позиция Y
    int x = 250; // Начальная позиция X

    for (const auto& line : helpTextLines) {

        if (line == "Добро пожаловать в мир танковых баталий!" ||
            line == "Инструкции по управлению:" ||
            line == "Цель игры:" ||
            line == "Удачи") {
            renderText(renderer, line, x-15, y, 16, redColor); // Рендеринг красного текста
        }
        else {
            renderText(renderer, line, x, y, 16, { 0, 0, 0, 255 }); // Рендеринг обычного текста
        }

        y += 30; // Смещение для следующей строки
    }

    SDL_RenderPresent(renderer);
}

GameState HelpScene::updateState() {
    if (returnToMenuButton.isClicked) {
        returnToMenuButton.isClicked = false;
        return GameState::MainMenu;
    }
    return GameState::Help;
}
