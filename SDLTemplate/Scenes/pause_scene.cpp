// PauseMenuScene.cpp
#include "pause_scene.h"

#include "../Objects/button.h"
#include "../Objects/slider.h"

#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"
#include "../Utils/Utils.h"
#include "../Utils/ConfigurationManager.h"
#include <iostream>

PauseMenuScene::PauseMenuScene(SDL_Renderer* ren, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(ren), musicPlayer(musicPlayer), soundPlayer(soundPlayer),
    resumeButton(loadTexture("Assets\\Sprites\\Buttons\\Resume_button.png", renderer), loadTexture("Assets\\Sprites\\Buttons\\Resume_button_hover.png", renderer), 400, 500, &soundPlayer),
    returnToMenuButton(loadTexture("Assets\\Sprites\\Buttons\\Menu_button.png", renderer), loadTexture("Assets\\Sprites\\Buttons\\Menu_button_hover.png", renderer), 400, 600, &soundPlayer),
    buttonMusic(loadTexture("Assets\\Sprites\\Buttons\\Music_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Music_button.png", renderer),
        275, 100, nullptr, loadTexture("Assets\\Sprites\\Buttons\\MuteMusic_button.png", renderer), true),
    buttonSound(loadTexture("Assets\\Sprites\\Buttons\\Sound_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Sound_button.png", renderer),
        275, 200, nullptr, loadTexture("Assets\\Sprites\\Buttons\\MuteSound_button.png", renderer), true),
    sliderMusic(375, 125, 300, 20, 0, 100, musicPlayer.currentVolume()),
    sliderSound(375, 225, 300, 20, 0, 100, soundPlayer.getCurrentVolume())
{

    // Load and set up background
    backgroundTexture = loadTexture("Assets/Sprites/transparent.png", renderer);
    SDL_SetTextureBlendMode(backgroundTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(backgroundTexture, 128);
}



PauseMenuScene::~PauseMenuScene() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
    }
}

void PauseMenuScene::handleEvents(const SDL_Event& event, GameState& gameState) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mousePoint = { x, y };

    resumeButton.isHovered = SDL_PointInRect(&mousePoint, &resumeButton.position);
    returnToMenuButton.isHovered = SDL_PointInRect(&mousePoint, &returnToMenuButton.position);
    buttonMusic.isHovered = SDL_PointInRect(&mousePoint, &buttonMusic.position);
    buttonSound.isHovered = SDL_PointInRect(&mousePoint, &buttonSound.position);

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (resumeButton.isHovered) {
            resumeButton.isClicked = true;
        }
        if (returnToMenuButton.isHovered) {
            returnToMenuButton.isClicked = true;
        }
        if (buttonMusic.isHovered) {
            buttonMusic.toggle();
            musicEnabled = !musicEnabled;
            if (musicEnabled) {
                musicPlayer.playMusic();
                std::cout << "Music Effects toggled ON" << std::endl; // Вывод в консоль
                musicPlayer.enableMusic();
            }
            else {
                musicPlayer.stopMusic();
                std::cout << "Music Effects toggled OFF" << std::endl; // Вывод в консоль
                musicPlayer.disableMusic();
            }
        }
        // Логика для слайдера громкости музыки
        if (x >= sliderMusic.thumb.x && x <= sliderMusic.thumb.x + sliderMusic.thumb.w &&
            y >= sliderMusic.thumb.y && y <= sliderMusic.thumb.y + sliderMusic.thumb.h) {
            sliderMusic.isDragging = true;
        }
        // Логика для слайдера громкости звуков
        if (x >= sliderSound.thumb.x && x <= sliderSound.thumb.x + sliderSound.thumb.w &&
            y >= sliderSound.thumb.y && y <= sliderSound.thumb.y + sliderSound.thumb.h) {
            sliderSound.isDragging = true;
        }
        if (buttonSound.isHovered) {
            buttonSound.toggle();
            soundEnabled = !soundEnabled;
            if (soundEnabled) {
                soundPlayer.enableSoundEffects();
                std::cout << "Sound Effects toggled ON" << std::endl; // Вывод в консоль
            }
            else {
                soundPlayer.disableSoundEffects();
                std::cout << "Sound Effects toggled OFF" << std::endl; // Вывод в консоль
            }
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP) {
        sliderMusic.isDragging = false;
        sliderSound.isDragging = false;
    }
    else if (event.type == SDL_MOUSEMOTION) {
        if (sliderMusic.isDragging) {
            sliderMusic.update(x);
            musicPlayer.setVolume(sliderMusic.getValue());
        }
        if (sliderSound.isDragging) {
            sliderSound.update(x);
            soundPlayer.setVolume(sliderSound.getValue());
        }

    }
}

void PauseMenuScene::render() {
    // Отображение фона и кнопок
    renderTexture(backgroundTexture, renderer, 0, 0);
    // Отрисовка кнопок
    resumeButton.render(renderer);
    returnToMenuButton.render(renderer);
    buttonMusic.render(renderer);
    buttonSound.render(renderer);
    sliderMusic.render(renderer);
    sliderSound.render(renderer);
    SDL_RenderPresent(renderer);
}

GameState PauseMenuScene::updateState() {
    if (resumeButton.isClicked) {
        resumeButton.isClicked = false;
        return GameState::Level1;
    }
    else if (returnToMenuButton.isClicked) {
        returnToMenuButton.isClicked = false;
        return GameState::MainMenu;
    }
    return GameState::Pause;
}