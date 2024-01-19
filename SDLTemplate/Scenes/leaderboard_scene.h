// leaderboard_scene.h
#ifndef LEADERBOARD_SCENE_H
#define LEADERBOARD_SCENE_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "../game_states.h"
#include "../Objects/button.h"
#include "../Objects/board.h"
#include "../Utils/Utils.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"

// Класс LeaderboardScene для представления сцены таблицы лидеров.
class LeaderboardScene {
public:
    // Конструктор класса, инициализирует сцену таблицы лидеров.
    LeaderboardScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);

    // Метод для обработки событий SDL.
    void handleEvents(const SDL_Event& event);

    // Метод для рендеринга сцены таблицы лидеров.
    void render();

    // Метод для обновления состояния сцены.
    GameState updateState();

private:
    SDL_Renderer* renderer;        // Рендерер SDL для отрисовки
    MusicPlayer& musicPlayer;
    SoundPlayer& soundPlayer;
    SDL_Texture* backgroundTexture; // Текстура фона
    Button returnToMenuButton;              // Кнопка "Назад"
    std::vector<LeaderboardEntry> leaderboardEntries;
};

#endif // LEADERBOARD_SCENE_H
