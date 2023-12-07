#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "game_states.h"
#include "Scenes/mainmenu_scene.h"
#include "Scenes/settings_scene.h"
#include "Objects/button.h"
#include "Objects/slider.h"

// Функция для загрузки текстуры из файла
SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* ren) {
    SDL_Texture* texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr) {
        std::cout << "LoadTexture error: " << SDL_GetError() << std::endl;
    }
    return texture;
}

int main(int, char**) {
    // Инициализация SDL и создание окна и рендерера
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Game Menu", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 1024, 1024, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Создание объектов для различных сцен..

    SDL_Texture* background = loadTexture("Assets\\Sprites\\Main_menu.png", renderer);

    SDL_Texture* buttonStartNormal = loadTexture("Assets\\Sprites\\Buttons\\Play_button.png", renderer);
    SDL_Texture* buttonStartHover = loadTexture("Assets\\Sprites\\Buttons\\Play_button_hover.png", renderer);
    Button buttonStart(buttonStartNormal, buttonStartHover, 400, 100);

    SDL_Texture* buttonSettingsNormal = loadTexture("Assets\\Sprites\\Buttons\\Settings_button.png", renderer);
    SDL_Texture* buttonSettingsHover = loadTexture("Assets\\Sprites\\Buttons\\Settings_button_hover.png", renderer);
    Button buttonSettings(buttonSettingsNormal, buttonSettingsHover, 400, 200);

    SDL_Texture* buttonExitNormal = loadTexture("Assets\\Sprites\\Buttons\\Exit_button.png", renderer);
    SDL_Texture* buttonExitHover = loadTexture("Assets\\Sprites\\Buttons\\Exit_button_hover.png", renderer);
    Button buttonExit(buttonExitNormal, buttonExitHover, 400, 300);

    SDL_Texture* buttonBackNormal = loadTexture("Assets\\Sprites\\Buttons\\Back_button.png", renderer);
    SDL_Texture* buttonBackHover = loadTexture("Assets\\Sprites\\Buttons\\Back_button_hover.png", renderer);
    Button backButton(buttonBackNormal, buttonBackHover, 400, 400);

    SettingsScene settingsScene(renderer, backButton, background);
    MainMenuScene mainMenuScene(renderer, buttonStart, buttonSettings, buttonExit, background);

    // Глеавный цикл
    bool running = true;
    GameState gameState = GameState::MainMenu;

    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            
            switch (gameState) {
            case GameState::MainMenu:
                mainMenuScene.handleEvents(event);
                //std::cout << "Game state updated to: " << static_cast<int>(gameState) << std::endl;
                gameState = mainMenuScene.updateState();
                //std::cout << "Game state updated to: " << static_cast<int>(gameState) << std::endl;
                break;

            case GameState::Settings:
                settingsScene.handleEvents(event);
                gameState = settingsScene.updateState();
                break;

            case GameState::Playing:
                // Обработка событий игровой сцены
                break;

            case GameState::Exit:
                running = false;
            }

        }

        switch (gameState) {
        case GameState::MainMenu:
            std::cout << "Calling render for Main Menu" << std::endl;
            mainMenuScene.render();
            break;

        case GameState::Settings:
            settingsScene.render();
            break;

        case GameState::Playing:
            // Отрисовка игровой сцены
            break;

        }
    }

    SDL_DestroyTexture(background);

    SDL_DestroyTexture(buttonStartNormal);
    SDL_DestroyTexture(buttonStartHover);

    SDL_DestroyTexture(buttonSettingsNormal);
    SDL_DestroyTexture(buttonSettingsHover);

    SDL_DestroyTexture(buttonExitNormal);
    SDL_DestroyTexture(buttonExitHover);

    SDL_DestroyTexture(buttonBackNormal);
    SDL_DestroyTexture(buttonBackHover);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
