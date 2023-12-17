// mainmenu_scene.cpp
#include "mainmenu_scene.h"
#include "../game_states.h"
#include "../Utils/Utils.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"
#include "../Objects/button.h"
#include <iostream>

// Конструктор главного меню.
MainMenuScene::MainMenuScene(SDL_Renderer* ren, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(ren),
    musicPlayer(musicPlayer),
    soundPlayer(soundPlayer),
    initializedSuccessfully(true),
    backgroundTexture(loadTexture("Assets/Sprites/Main_menu.png", renderer)),
    // Инициализация кнопок меню.
    buttonStart(loadTexture("Assets\\Sprites\\Buttons\\Play_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Play_button_hover.png", renderer),
        400, 100, &soundPlayer),
    buttonSettings(loadTexture("Assets\\Sprites\\Buttons\\Settings_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Settings_button_hover.png", renderer),
        400, 200, &soundPlayer),
    buttonExit(loadTexture("Assets\\Sprites\\Buttons\\Exit_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Exit_button_hover.png", renderer),
        400, 300, &soundPlayer)
{
    // Загрузка и воспроизведение музыки в главном меню.
    if (!musicPlayer.loadMusic("Assets\\Sounds\\MainMenu_music.mp3")) {
        std::cerr << "Failed to load main menu music" << std::endl;
        initializedSuccessfully = false;
    }
    musicPlayer.playMusic();
    musicPlayer.setVolume(75); // Начальная громкость.

    // Загрузка звуковых эффектов.
    if (!soundPlayer.loadSound("Assets\\Sounds\\chooseButton_sound.mp3")) {
        std::cerr << "Failed to load hover sound effect" << std::endl;
    }
}

// Деструктор главного меню.
MainMenuScene::~MainMenuScene() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
    }
}

// Функция проверки успешной инициализации.
bool MainMenuScene::isInitializedSuccessfully() const {
    return initializedSuccessfully;
}

// Обработка событий в главном меню.
void MainMenuScene::handleEvents(const SDL_Event& event) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mousePoint = { x, y };

    // Определение, находится ли курсор на кнопках.
    buttonStart.isHovered = SDL_PointInRect(&mousePoint, &buttonStart.position);
    buttonSettings.isHovered = SDL_PointInRect(&mousePoint, &buttonSettings.position);
    buttonExit.isHovered = SDL_PointInRect(&mousePoint, &buttonExit.position);

    // Обработка нажатия кнопок мыши.
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

// Отрисовка главного меню.
void MainMenuScene::render() {
    SDL_RenderClear(renderer);
    renderTexture(backgroundTexture, renderer, 0, 0);
    buttonStart.render(renderer);
    buttonSettings.render(renderer);
    buttonExit.render(renderer);
    SDL_RenderPresent(renderer);
}

// Обновление состояния главного меню.
GameState MainMenuScene::updateState() {
    // Переход к различным состояниям игры в зависимости от выбора пользователя.
    if (buttonStart.isClicked) {
        buttonStart.isClicked = false;
        return GameState::Level1;
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