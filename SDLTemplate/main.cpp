#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "game_states.h"

#include "Scenes/mainmenu_scene.h"
#include "Scenes/settings_scene.h"
#include "Scenes/pause_scene.h"
#include "Scenes/Level1Scene.h"

#include "Objects/button.h"
#include "Objects/slider.h"

#include "Utils/Utils.h"
#include "Utils/MusicPlayer.h"
#include "Utils/SoundPlayer.h"

int main(int argc, char* argv[]) {
    // Инициализация SDL и создание окна и рендерера
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Game Menu", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 1024, 1024, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    MusicPlayer musicPlayer;
    SoundPlayer soundPlayer;

    MainMenuScene mainMenuScene(renderer, musicPlayer, soundPlayer);
    SettingsScene settingsScene(renderer, musicPlayer, soundPlayer);
    Level1Scene level1Scene(renderer, musicPlayer, soundPlayer);
    PauseMenuScene pauseScene(renderer, musicPlayer, soundPlayer);

    // Глеавный цикл
    bool running = true;
    GameState gameState = GameState::MainMenu;

    SDL_Event event;
    while (running) {
        level1Scene.update();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

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
                level1Scene.handleEvents(event, gameState);
                level1Scene.updateState();
                break;
            case GameState::Pause:
                pauseScene.handleEvents(event, gameState);
                gameState = pauseScene.updateState();
                break;
            case GameState::Exit:
                running = false;
            }
        }

        switch (gameState) {
        case GameState::MainMenu:
            mainMenuScene.render();
            break;
        case GameState::Settings:
            settingsScene.render();
            break;
        case GameState::Level1:
            level1Scene.render();
            break;
        case GameState::Pause:
            pauseScene.render();
            break;
        }
    }

    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
