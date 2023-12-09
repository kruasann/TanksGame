// mainmenu_scene.cpp
#include "mainmenu_scene.h"
#include "../game_states.h"
#include "../Utils/Utils.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"
#include "../Objects/button.h"
#include <iostream>

MainMenuScene::MainMenuScene(SDL_Renderer* ren, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(ren), 
    musicPlayer(musicPlayer), 
    soundPlayer(soundPlayer),
    initializedSuccessfully(true),
    backgroundTexture(loadTexture("Assets/Sprites/Main_menu.png", renderer)),
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
    if (!musicPlayer.loadMusic("Assets\\Sounds\\MainMenu_music.mp3")) {
        std::cerr << "Failed to load main menu music" << std::endl;
        initializedSuccessfully = false;
    }
    musicPlayer.playMusic();
    musicPlayer.setVolume(75); // Начальная громкость

    if (!soundPlayer.loadSound("Assets\\Sounds\\chooseButton_sound.mp3")) {
        std::cerr << "Failed to load hover sound effect" << std::endl;
    }
}

MainMenuScene::~MainMenuScene() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
    }
}

bool MainMenuScene::isInitializedSuccessfully() const {
    return initializedSuccessfully;
}

void MainMenuScene::handleEvents(const SDL_Event& event) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mousePoint = { x, y };

    buttonStart.isHovered = SDL_PointInRect(&mousePoint, &buttonStart.position);
    buttonSettings.isHovered = SDL_PointInRect(&mousePoint, &buttonSettings.position);
    buttonExit.isHovered = SDL_PointInRect(&mousePoint, &buttonExit.position);

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

void MainMenuScene::render() {
    //std::cout << "Rendering Main Menu Scene" << std::endl;
    SDL_RenderClear(renderer);
    renderTexture(backgroundTexture, renderer, 0, 0);
    buttonStart.render(renderer);
    buttonSettings.render(renderer);
    buttonExit.render(renderer);
    SDL_RenderPresent(renderer);
}

GameState MainMenuScene::updateState() {
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

