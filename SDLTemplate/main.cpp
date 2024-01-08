#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>

// Подключение заголовочных файлов состояний игры и сцен
#include "game_states.h"
#include "Scenes/mainmenu_scene.h"
#include "Scenes/settings_scene.h"
#include "Scenes/pause_scene.h"
#include "Scenes/Level1Scene.h"
#include "Scenes/WinScene.h"

// Подключение объектов интерфейса и утилит
#include "Objects/button.h"
#include "Objects/slider.h"
#include "Utils/Utils.h"
#include "Utils/MusicPlayer.h"
#include "Utils/SoundPlayer.h"

// Основная функция программы
int main(int argc, char* argv[]) {
    // Инициализация SDL и создание окна и рендерера
    // Если SDL_Init вернет значение меньше 0, это указывает на ошибку.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        // Вывод ошибки в stderr, если SDL не удалось инициализировать.
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1; // Выход из программы с кодом ошибки 1
    }

    // Инициализация аудио подсистемы SDL
    // Если Mix_OpenAudio вернет значение меньше 0, это указывает на ошибку.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        // Вывод ошибки, если SDL_mixer не удалось инициализировать
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return 1; // Выход из программы с кодом ошибки 1
    }

    // Инициализация SDL_ttf
    // Если TTF_Init вернет -1, это указывает на ошибку.
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1; // Выход из программы с кодом ошибки 1
    }

    // Создание окна с указанными параметрами
    SDL_Window* window = SDL_CreateWindow("Game Menu", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 1024, 1024, SDL_WINDOW_SHOWN);
    // Создание рендерера для окна
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Создание экземпляров проигрывателей музыки и звуков
    MusicPlayer musicPlayer;
    SoundPlayer soundPlayer;

    // Создание сцен для разных состояний игры
    MainMenuScene mainMenuScene(renderer, musicPlayer, soundPlayer);
    SettingsScene settingsScene(renderer, musicPlayer, soundPlayer);
    std::unique_ptr<Level1Scene> level1Scene;
    bool pauseEnabled = false;
    PauseMenuScene pauseScene(renderer, musicPlayer, soundPlayer, pauseEnabled);
    WinScene winScene(renderer, musicPlayer, soundPlayer);

    // Главный цикл игры
    bool running = true;
    GameState gameState = GameState::MainMenu;

    // Объект для обработки событий SDL
    SDL_Event event;
    while (running) {

        // Обновление сцены только если она существует
        if (level1Scene) {
            level1Scene->update();
        }

        // Опрос событий SDL
        while (SDL_PollEvent(&event)) {
            // Обработка события выхода из игры
            if (event.type == SDL_QUIT) {
                running = false;
            }

            std::cout << "Pause: " << (pauseEnabled) << std::endl;

            // Обработка событий в зависимости от текущего состояния игры
            switch (gameState) {
            case GameState::MainMenu:
                mainMenuScene.handleEvents(event);
                gameState = mainMenuScene.updateState();
                break;
            case GameState::Settings:
                settingsScene.handleEvents(event);
                gameState = settingsScene.updateState();
                break;
            case GameState::Level1:
                if (!level1Scene) {
                    // Создание сцены, если она еще не создана
                    level1Scene = std::make_unique<Level1Scene>(renderer, musicPlayer, soundPlayer, pauseEnabled);
                }
                level1Scene->handleEvents(event, gameState);
                gameState = level1Scene->updateState();
                break;
            case GameState::Pause:
                pauseScene.handleEvents(event, gameState);
                gameState = pauseScene.updateState();
                if (gameState == GameState::MainMenu) {
                    // Удаляем сцену при возвращении в главное меню
                    level1Scene.reset();
                }
                break;
            case GameState::Win:
                winScene.handleEvents(event, gameState);
                gameState = winScene.updateState();
                if (gameState == GameState::MainMenu) {
                    // Удаляем сцену при возвращении в главное меню
                    level1Scene.reset();
                }
                break;
            case GameState::Exit:
                running = false;
            }
        }

        // Отрисовка текущей сцены в зависимости от состояния игры
        switch (gameState) {
        case GameState::MainMenu:
            mainMenuScene.render();
            break;
        case GameState::Settings:
            settingsScene.render();
            break;
        case GameState::Level1:
            if (level1Scene) {
                level1Scene->render();
            }
            break;
        case GameState::Pause:
            pauseScene.render();
            break;
        case GameState::Win:
            winScene.render();
            break;
        }
    }

    // Очистка ресурсов и завершение работы SDL
    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
