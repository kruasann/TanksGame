#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <SDL2/SDL.h>
#include "../game_states.h"
#include "../Objects/button.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"

class MainMenuScene {
private:
    SDL_Renderer* renderer;
    MusicPlayer& musicPlayer;
    SoundPlayer& soundPlayer;
    bool initializedSuccessfully;

public:
    MainMenuScene(SDL_Renderer* ren, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);
    ~MainMenuScene();
    Button buttonStart;
    Button buttonSettings;
    Button buttonExit;
    SDL_Texture* backgroundTexture;
    bool isInitializedSuccessfully() const;
    void handleEvents(const SDL_Event& event);
    void render();
    GameState updateState();
};

#endif // MAINMENUSCENE_H
