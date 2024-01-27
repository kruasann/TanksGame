#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <SDL2/SDL.h>
#include "BaseScene.h"
#include "../game_states.h"
#include "../Objects/button.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"

// Класс главного меню игры.
class MainMenuScene : public BaseScene {
private:
    MusicPlayer& musicPlayer;
    SoundPlayer& soundPlayer;
    bool initializedSuccessfully;

public:
    MainMenuScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);
    ~MainMenuScene();
    Button buttonStart;
    Button buttonSettings;
    Button buttonHelp;
    Button buttonCredits;
    Button buttonLeaderboard;
    Button buttonExit;
    SDL_Texture* backgroundTexture;
    bool isInitializedSuccessfully() const;
    void handleEvents(const SDL_Event& event, GameState& gameState);
    void render();
    GameState updateState();
};

#endif // MAINMENUSCENE_H