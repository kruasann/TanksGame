// credits_scene.h
#ifndef CREDITS_SCENE_H
#define CREDITS_SCENE_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "../game_states.h"
#include "../Objects/button.h"
#include "../Utils/Utils.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"

// Класс CreditsScene для представления сцены инфы в игре.
class CreditsScene {
public:
    // Конструктор класса, инициализирует сцену инфы.
    CreditsScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);

    // Метод для обработки событий SDL.
    void handleEvents(const SDL_Event& event);

    // Метод для рендеринга сцены инфы.
    void render();

    // Метод для обновления состояния сцены.
    GameState updateState();

private:
    SDL_Renderer* renderer;        // Рендерер SDL для отрисовки
    MusicPlayer& musicPlayer;
    SoundPlayer& soundPlayer;
    SDL_Texture* backgroundTexture; // Текстура фона
    Button returnToMenuButton;              // Кнопка "Назад"
    std::vector<std::string> creditsTextLines; // Строки текста кредитов
};

#endif // CREDITS_SCENE_H
