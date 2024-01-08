#ifndef SETTINGS_SCENE_H
#define SETTINGS_SCENE_H

#include <SDL2/SDL.h>
#include "../game_states.h"
#include "../Objects/button.h"
#include "../Objects/slider.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"
#include "../Utils/ConfigurationManager.h"

// Класс SettingsScene для представления сцены настроек в игре.
class SettingsScene {
public:
    // Конструктор класса, инициализирует сцену настроек.
    SettingsScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);

    // Метод для обработки событий SDL.
    void handleEvents(const SDL_Event& event);

    // Метод для рендеринга сцены настроек.
    void render();

    // Метод для обновления состояния сцены.
    GameState updateState();

private:
    // Приватные переменные класса.
    SDL_Renderer* renderer;       // Рендерер SDL для отрисовки
    MusicPlayer& musicPlayer;     // Объект для управления музыкой
    SoundPlayer& soundPlayer;     // Объект для управления звуковыми эффектами

    SDL_Texture* backgroundTexture; // Текстура фона
    Button backButton;              // Кнопка "Назад"
    Button buttonMusic;             // Кнопка управления музыкой
    Button buttonSound;             // Кнопка управления звуками
    Slider sliderMusic;             // Слайдер громкости музыки
    Slider sliderSound;             // Слайдер громкости звуков

    bool musicEnabled;              // Состояние музыки (включено/выключено)
    bool soundEnabled;              // Состояние звуков (включено/выключено)
};

#endif // SETTINGS_SCENE_H
