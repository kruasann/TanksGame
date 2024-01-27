#ifndef PAUSE_MENU_SCENE_H
#define PAUSE_MENU_SCENE_H

#include <SDL2/SDL.h>
#include "BaseScene.h"
#include "../game_states.h"
#include "../Objects/button.h"
#include "../Objects/slider.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"

// Класс сцены паузы.
class PauseMenuScene : BaseScene{
public:
    // Конструктор.
    PauseMenuScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer, bool& pauseEnabled);
    // Деструктор.
    ~PauseMenuScene();
    // Обработка событий.
    void handleEvents(const SDL_Event& event, GameState& gameState);
    // Рендер сцены.
    void render();
    // Обновление состояния сцены.
    GameState updateState();

private:
    MusicPlayer& musicPlayer;
    SoundPlayer& soundPlayer;
    SDL_Texture* backgroundTexture;
    Button resumeButton;
    Button returnToMenuButton;
    Button buttonMusic;
    Button buttonSound;
    Slider sliderMusic;
    Slider sliderSound;
    bool& pauseEnabled;
    bool musicEnabled = true;
    bool soundEnabled = true;
};

#endif // PAUSE_MENU_SCENE_H