#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>

// ����������� ������������ ������ ��������� ���� � ����
#include "game_states.h"
#include "Scenes/mainmenu_scene.h"
#include "Scenes/settings_scene.h"
#include "Scenes/pause_scene.h"
#include "Scenes/Level1Scene.h"
#include "Scenes/WinScene.h"

// ����������� �������� ���������� � ������
#include "Objects/button.h"
#include "Objects/slider.h"
#include "Utils/Utils.h"
#include "Utils/MusicPlayer.h"
#include "Utils/SoundPlayer.h"

// �������� ������� ���������
int main(int argc, char* argv[]) {
    // ������������� SDL � �������� ���� � ���������
    // ���� SDL_Init ������ �������� ������ 0, ��� ��������� �� ������.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        // ����� ������ � stderr, ���� SDL �� ������� ����������������.
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1; // ����� �� ��������� � ����� ������ 1
    }

    // ������������� ����� ���������� SDL
    // ���� Mix_OpenAudio ������ �������� ������ 0, ��� ��������� �� ������.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        // ����� ������, ���� SDL_mixer �� ������� ����������������
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return 1; // ����� �� ��������� � ����� ������ 1
    }

    // ������������� SDL_ttf
    // ���� TTF_Init ������ -1, ��� ��������� �� ������.
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1; // ����� �� ��������� � ����� ������ 1
    }

    // �������� ���� � ���������� �����������
    SDL_Window* window = SDL_CreateWindow("Game Menu", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 1024, 1024, SDL_WINDOW_SHOWN);
    // �������� ��������� ��� ����
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // �������� ����������� �������������� ������ � ������
    MusicPlayer musicPlayer;
    SoundPlayer soundPlayer;

    // �������� ���� ��� ������ ��������� ����
    MainMenuScene mainMenuScene(renderer, musicPlayer, soundPlayer);
    SettingsScene settingsScene(renderer, musicPlayer, soundPlayer);
    std::unique_ptr<Level1Scene> level1Scene;
    bool pauseEnabled = false;
    PauseMenuScene pauseScene(renderer, musicPlayer, soundPlayer, pauseEnabled);
    WinScene winScene(renderer, musicPlayer, soundPlayer);

    // ������� ���� ����
    bool running = true;
    GameState gameState = GameState::MainMenu;

    // ������ ��� ��������� ������� SDL
    SDL_Event event;
    while (running) {

        // ���������� ����� ������ ���� ��� ����������
        if (level1Scene) {
            level1Scene->update();
        }

        // ����� ������� SDL
        while (SDL_PollEvent(&event)) {
            // ��������� ������� ������ �� ����
            if (event.type == SDL_QUIT) {
                running = false;
            }

            std::cout << "Pause: " << (pauseEnabled) << std::endl;

            // ��������� ������� � ����������� �� �������� ��������� ����
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
                    // �������� �����, ���� ��� ��� �� �������
                    level1Scene = std::make_unique<Level1Scene>(renderer, musicPlayer, soundPlayer, pauseEnabled);
                }
                level1Scene->handleEvents(event, gameState);
                gameState = level1Scene->updateState();
                break;
            case GameState::Pause:
                pauseScene.handleEvents(event, gameState);
                gameState = pauseScene.updateState();
                if (gameState == GameState::MainMenu) {
                    // ������� ����� ��� ����������� � ������� ����
                    level1Scene.reset();
                }
                break;
            case GameState::Win:
                winScene.handleEvents(event, gameState);
                gameState = winScene.updateState();
                if (gameState == GameState::MainMenu) {
                    // ������� ����� ��� ����������� � ������� ����
                    level1Scene.reset();
                }
                break;
            case GameState::Exit:
                running = false;
            }
        }

        // ��������� ������� ����� � ����������� �� ��������� ����
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

    // ������� �������� � ���������� ������ SDL
    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
