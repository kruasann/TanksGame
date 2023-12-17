// settings_scene.cpp
#include "settings_scene.h"
#include "../game_states.h"

#include "../Objects/button.h"
#include "../Objects/slider.h"

#include "../Utils/Utils.h"
#include "../Utils/ConfigurationManager.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"

#include <iostream>

// Конструктор сцены настроек.
SettingsScene::SettingsScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(renderer),
    musicPlayer(musicPlayer),
    soundPlayer(soundPlayer),
    // Загрузка текстур фона и кнопок.
    backgroundTexture(loadTexture("Assets/Sprites/Main_menu.png", renderer)),
    backButton(loadTexture("Assets\\Sprites\\Buttons\\Back_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Back_button_hover.png", renderer),
        400, 400, &soundPlayer),
    buttonMusic(loadTexture("Assets\\Sprites\\Buttons\\Music_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Music_button.png", renderer),
        275, 100, nullptr, loadTexture("Assets\\Sprites\\Buttons\\MuteMusic_button.png", renderer), true),
    buttonSound(loadTexture("Assets\\Sprites\\Buttons\\Sound_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\Sound_button.png", renderer),
        275, 200, nullptr, loadTexture("Assets\\Sprites\\Buttons\\MuteSound_button.png", renderer), true),
    // Создание слайдеров для регулировки громкости.
    sliderMusic(375, 125, 300, 20, 0, 100, musicPlayer.currentVolume()),
    sliderSound(375, 225, 300, 20, 0, 100, soundPlayer.getCurrentVolume())
{
    // Инициализация настроек из ConfigurationManager.
    auto& config = ConfigurationManager::getInstance();
    musicEnabled = config.musicEnabled;
    soundEnabled = config.soundEnabled;
}

// Обработка событий в сцене настроек.
void SettingsScene::handleEvents(const SDL_Event& event) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mousePoint = { x, y };

    // Проверка, находится ли курсор над кнопками.
    backButton.isHovered = SDL_PointInRect(&mousePoint, &backButton.position);
    buttonMusic.isHovered = SDL_PointInRect(&mousePoint, &buttonMusic.position);
    buttonSound.isHovered = SDL_PointInRect(&mousePoint, &buttonSound.position);

    // Обработка нажатия кнопки мыши.
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (backButton.isHovered) {
            backButton.isClicked = true;
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
        // Логика перетаскивания слайдеров громкости.
        // Слайдер музыки.
        if (x >= sliderMusic.thumb.x && x <= sliderMusic.thumb.x + sliderMusic.thumb.w &&
            y >= sliderMusic.thumb.y && y <= sliderMusic.thumb.y + sliderMusic.thumb.h) {
            sliderMusic.isDragging = true;
        }
        // Слайдер звуковых эффектов.
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
        // Прекращение перетаскивания слайдеров при отпускании кнопки мыши.
        sliderMusic.isDragging = false;
        sliderSound.isDragging = false;
    }
    else if (event.type == SDL_MOUSEMOTION) {
        // Обновление положения слайдеров при движении мыши.
        if (sliderMusic.isDragging) {
            sliderMusic.update(x);
            musicPlayer.setVolume(sliderMusic.getValue());
            auto& config = ConfigurationManager::getInstance();
            config.musicVolume = sliderMusic.getValue();
        }
        if (sliderSound.isDragging) {
            sliderSound.update(x);
            soundPlayer.setVolume(sliderSound.getValue());
            auto& config = ConfigurationManager::getInstance();
            config.soundVolume = sliderSound.getValue();
        }
    }
}

// Рендеринг сцены настроек.
void SettingsScene::render() {
    // Очистка рендерера.
    SDL_RenderClear(renderer);

    // Отрисовка фона и элементов интерфейса.
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    backButton.render(renderer);
    buttonMusic.render(renderer);
    buttonSound.render(renderer);
    sliderMusic.render(renderer);
    sliderSound.render(renderer);

    // Вывод рендерера на экран.
    SDL_RenderPresent(renderer);
}

// Обновление состояния сцены.
GameState SettingsScene::updateState() {
    // Переход обратно в главное меню.
    if (backButton.isClicked) {
        backButton.isClicked = false;
        return GameState::MainMenu;
    }
    return GameState::Settings;
}
