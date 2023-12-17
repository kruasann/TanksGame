// Защита от повторного включения заголовочного файла.
#ifndef SETTINGS_SCENE_H
#define SETTINGS_SCENE_H

// Подключение необходимых библиотек и файлов.
#include <SDL2/SDL.h>
#include "../game_states.h"

#include "../Objects/button.h"
#include "../Objects/slider.h"

#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"
#include "../Utils/ConfigurationManager.h"

// Объявление класса SettingsScene.
class SettingsScene {
public:
    // Конструктор класса, методы для обработки событий, отрисовки и обновления состояния.
    SettingsScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);
    void handleEvents(const SDL_Event& event);
    void render();
    GameState updateState();

private:
    // Приватные переменные класса, включая рендерер, плееры музыки и звуков, текстуры, кнопки и слайдеры.
    SDL_Renderer* renderer;
    MusicPlayer& musicPlayer;
    SoundPlayer& soundPlayer;

    SDL_Texture* backgroundTexture;
    Button backButton;
    Button buttonMusic;
    Button buttonSound;
    Slider sliderMusic;
    Slider sliderSound;

    bool musicEnabled;
    bool soundEnabled;
};

// Конец защиты от повторного включения.
#endif // SETTINGS_SCENE_H
