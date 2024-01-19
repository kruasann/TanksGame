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
    buttonCredits(loadTexture("Assets\\Sprites\\Buttons\\Credits_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Credits_button_hover.png", renderer),
        780, 930, &soundPlayer),
    buttonLeaderboard(loadTexture("Assets\\Sprites\\Buttons\\Leaderboard_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Leaderboard_button_hover.png", renderer),
        400, 300, &soundPlayer),
    buttonHelp(loadTexture("Assets\\Sprites\\Buttons\\Help_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Help_button_hover.png", renderer),
        900, 100, &soundPlayer),
    buttonExit(loadTexture("Assets\\Sprites\\Buttons\\Exit_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Exit_button_hover.png", renderer),
        400, 400, &soundPlayer)
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
    buttonCredits.isHovered = SDL_PointInRect(&mousePoint, &buttonCredits.position);
    buttonLeaderboard.isHovered = SDL_PointInRect(&mousePoint, &buttonLeaderboard.position);
    buttonHelp.isHovered = SDL_PointInRect(&mousePoint, &buttonHelp.position);
    buttonExit.isHovered = SDL_PointInRect(&mousePoint, &buttonExit.position);

    // Обработка нажатия кнопок мыши.
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (buttonStart.isHovered) {
            buttonStart.isClicked = true;
        }
        else if (buttonSettings.isHovered) {
            buttonSettings.isClicked = true;
        }
        else if (buttonCredits.isHovered) {
            buttonCredits.isClicked = true;
        }
        else if (buttonHelp.isHovered) {
            buttonHelp.isClicked = true;
        }
        else if (buttonLeaderboard.isHovered) {
            buttonLeaderboard.isClicked = true;
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
    buttonCredits.render(renderer);
    buttonLeaderboard.render(renderer);
    buttonHelp.render(renderer);
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
    else if (buttonCredits.isClicked) {
        buttonCredits.isClicked = false;
        return GameState::Credits;
    }
    else if (buttonLeaderboard.isClicked) {
        buttonLeaderboard.isClicked = false;
        return GameState::Leaderboard;
    }
    else if (buttonHelp.isClicked) {
        buttonHelp.isClicked = false;
        return GameState::Help;
    }
    else if (buttonExit.isClicked) {
        buttonExit.isClicked = false;
        return GameState::Exit;
    }

    return GameState::MainMenu;
}