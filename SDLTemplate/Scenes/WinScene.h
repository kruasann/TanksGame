#ifndef WIN_SCENE_H
#define WIN_SCENE_H

#include <SDL2/SDL.h>
#include "../Objects/button.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"
#include "../game_states.h"

// Класс WinScene для сцены победы в игре.
class WinScene {
public:
    // Конструктор сцены победы.
    WinScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);

    // Деструктор сцены победы.
    ~WinScene();

    // Обработка событий SDL в сцене победы.
    void handleEvents(const SDL_Event& event, GameState& gameState);

    // Рендеринг сцены победы.
    void render();

    // Обновление состояния сцены победы.
    GameState updateState();

private:
    SDL_Texture* backgroundTexture; // Текстура фона сцены
    SDL_Renderer* renderer;         // Рендерер SDL
    Button returnToMenuButton;      // Кнопка "Вернуться в меню"
    // Другие необходимые члены и методы
};

#endif // WIN_SCENE_H