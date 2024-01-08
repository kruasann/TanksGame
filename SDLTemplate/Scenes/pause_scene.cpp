// PauseMenuScene.cpp
#include "pause_scene.h"

#include "../Objects/button.h"
#include "../Objects/slider.h"

#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"
#include "../Utils/Utils.h"
#include "../Utils/ConfigurationManager.h"
#include <iostream>

// Конструктор сцены паузы.
PauseMenuScene::PauseMenuScene(SDL_Renderer* ren, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer, bool& pauseEnabled)
    : renderer(ren),
    musicPlayer(musicPlayer),
    soundPlayer(soundPlayer),
    pauseEnabled(pauseEnabled),
    resumeButton(loadTexture("Assets/Sprites/Buttons/Resume_button.png", renderer),
        loadTexture("Assets/Sprites/Buttons/Resume_button_hover.png", renderer),
        400, 500, &soundPlayer),
    returnToMenuButton(loadTexture("Assets/Sprites/Buttons/Menu_button.png", renderer),
        loadTexture("Assets/Sprites/Buttons/Menu_button_hover.png", renderer),
        400, 600, &soundPlayer),
    buttonMusic(loadTexture("Assets/Sprites/Buttons/Music_button.png", renderer),
        loadTexture("Assets/Sprites/Buttons/Music_button.png", renderer),
        275, 100, nullptr,
        loadTexture("Assets/Sprites/Buttons/MuteMusic_button.png", renderer),
        true),
    buttonSound(loadTexture("Assets/Sprites/Buttons/Sound_button.png", renderer),
        loadTexture("Assets/Sprites/Buttons/Sound_button.png", renderer),
        275, 200, nullptr,
        loadTexture("Assets/Sprites/Buttons/MuteSound_button.png", renderer),
        true),
    sliderMusic(375, 125, 300, 20, 0, 100, musicPlayer.currentVolume()),
    sliderSound(375, 225, 300, 20, 0, 100, soundPlayer.getCurrentVolume())
{
    // Загрузка и настройка фона.
    backgroundTexture = loadTexture("Assets/Sprites/transparent.png", renderer);
    SDL_SetTextureBlendMode(backgroundTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(backgroundTexture, 128);
}

// Деструктор сцены паузы.
PauseMenuScene::~PauseMenuScene() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
    }
}

// Обработка событий в сцене паузы.
void PauseMenuScene::handleEvents(const SDL_Event& event, GameState& gameState) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mousePoint = { x, y };

    // Определение, находится ли курсор на кнопках.
    resumeButton.isHovered = SDL_PointInRect(&mousePoint, &resumeButton.position);
    returnToMenuButton.isHovered = SDL_PointInRect(&mousePoint, &returnToMenuButton.position);
    buttonMusic.isHovered = SDL_PointInRect(&mousePoint, &buttonMusic.position);
    buttonSound.isHovered = SDL_PointInRect(&mousePoint, &buttonSound.position);

    // Обработка нажатия кнопки мыши.
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        resumeButton.isClicked = true; // Используйте флаг кнопки "Продолжить" для выхода из паузы
        pauseEnabled = false;
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (resumeButton.isHovered) {
            resumeButton.isClicked = true;
            pauseEnabled = false;
        }
        if (returnToMenuButton.isHovered) {
            returnToMenuButton.isClicked = true;
            pauseEnabled = false;
        }
        // Переключение музыки.
        if (buttonMusic.isHovered) {
            buttonMusic.toggle();
            musicEnabled = !musicEnabled;
            // Включение/выключение музыки.
            if (musicEnabled) {
                musicPlayer.playMusic();
                std::cout << "Music Effects toggled ON" << std::endl;
                musicPlayer.enableMusic();
            }
            else {
                musicPlayer.stopMusic();
                std::cout << "Music Effects toggled OFF" << std::endl;
                musicPlayer.disableMusic();
            }
        }
        // Логика для слайдеров громкости.
        // Слайдер музыки.
        if (x >= sliderMusic.thumb.x && x <= sliderMusic.thumb.x + sliderMusic.thumb.w &&
            y >= sliderMusic.thumb.y && y <= sliderMusic.thumb.y + sliderMusic.thumb.h) {
            sliderMusic.isDragging = true;
        }
        // Слайдер звуков.
        if (x >= sliderSound.thumb.x && x <= sliderSound.thumb.x + sliderSound.thumb.w &&
            y >= sliderSound.thumb.y && y <= sliderSound.thumb.y + sliderSound.thumb.h) {
            sliderSound.isDragging = true;
        }
        // Переключение звуковых эффектов.
        if (buttonSound.isHovered) {
            buttonSound.toggle();
            soundEnabled = !soundEnabled;
            // Включение/выключение звуковых эффектов.
            if (soundEnabled) {
                soundPlayer.enableSoundEffects();
                std::cout << "Sound Effects toggled ON" << std::endl;
            }
            else {
                soundPlayer.disableSoundEffects();
                std::cout << "Sound Effects toggled OFF" << std::endl;
            }
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP) {
        // Прекращение перетаскивания слайдера при отпускании кнопки мыши.
        sliderMusic.isDragging = false;
        sliderSound.isDragging = false;
    }
    else if (event.type == SDL_MOUSEMOTION) {
        // Обновление положения слайдера при движении мыши.
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

// Рендер сцены паузы.
void PauseMenuScene::render() {
    // Отображение фона и элементов интерфейса.
    renderTexture(backgroundTexture, renderer, 0, 0);
    resumeButton.render(renderer);
    returnToMenuButton.render(renderer);
    buttonMusic.render(renderer);
    buttonSound.render(renderer);
    sliderMusic.render(renderer);
    sliderSound.render(renderer);
    SDL_RenderPresent(renderer);
}

// Обновление состояния сцены паузы.
GameState PauseMenuScene::updateState() {
    // Возвращение к игре или выход в главное меню.
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