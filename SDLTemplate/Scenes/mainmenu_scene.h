// mainmenu_scene.h
#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <SDL2/SDL.h>
#include "../game_states.h"
#include "../Objects/button.h"

class MainMenuScene {
private:
    SDL_Renderer* renderer;
    Button buttonStart;
    Button buttonSettings;
    Button buttonExit;
    SDL_Texture* backgroundTexture;

public:
    MainMenuScene(SDL_Renderer* ren, Button startBtn, Button settingsBtn, Button exitBtn, SDL_Texture* bgTexture);
    void handleEvents(const SDL_Event& event);
    void render();
    GameState updateState();
};

#endif // MAINMENUSCENE_H
