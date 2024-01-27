// help_scene.h
#ifndef HELP_SCENE_H
#define HELP_SCENE_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "BaseScene.h"
#include "../game_states.h"
#include "../Objects/button.h"
#include "../Utils/Utils.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"

// Класс HelpScene для представления сцены помощи и информации в игре.
class HelpScene : public BaseScene {
public:
    // Конструктор класса, инициализирует сцену помощи.
    HelpScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);

    // Метод для обработки событий SDL.
    void handleEvents(const SDL_Event& event, GameState& gameState);

    // Метод для рендеринга сцены помощи.
    void render();

    // Метод для обновления состояния сцены.
    GameState updateState();

private:
    MusicPlayer& musicPlayer;
    SoundPlayer& soundPlayer;
    SDL_Texture* backgroundTexture; // Текстура фона
    Button returnToMenuButton;              // Кнопка "Назад"
    std::vector<std::string> helpTextLines; // Строки текста помощи
};

#endif // HELP_SCENE_H
