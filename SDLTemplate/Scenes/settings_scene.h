// settings_scene.h
#ifndef SETTINGS_SCENE_H
#define SETTINGS_SCENE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../game_states.h"
#include "../Objects/button.h"

class SettingsScene {
private:
    SDL_Renderer* renderer;
    Button backButton;
    SDL_Texture* backgroundTexture;
    bool backButtonClicked;

public:
    SettingsScene(SDL_Renderer* renderer, Button backButton, SDL_Texture* backgroundTexture);
    void handleEvents(const SDL_Event& event);
    void render();
    GameState updateState();
};

#endif // SETTINGS_SCENE_H
