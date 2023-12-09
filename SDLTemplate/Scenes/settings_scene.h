// settings_scene.h
#ifndef SETTINGS_SCENE_H
#define SETTINGS_SCENE_H

#include <SDL2/SDL.h>
#include "../game_states.h"

#include "../Objects/button.h"
#include "../Objects/slider.h"

#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"
#include "../Utils/ConfigurationManager.h"

class SettingsScene {
public:
    SettingsScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);
    void handleEvents(const SDL_Event& event);
    void render();
    GameState updateState();

private:
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

#endif // SETTINGS_SCENE_H
