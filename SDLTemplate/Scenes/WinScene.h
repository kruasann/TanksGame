// WinScene.h
#ifndef WIN_SCENE_H
#define WIN_SCENE_H

#include <SDL2/SDL.h>
#include "../Objects/button.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"
#include "../game_states.h"

class WinScene {
public:
    WinScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);
    ~WinScene();
    void handleEvents(const SDL_Event& event, GameState& gameState);
    void render();
    // ���������� ��������� �����.
    GameState updateState();

private:
    SDL_Texture* backgroundTexture;
    SDL_Renderer* renderer;
    Button returnToMenuButton; // ������ "Back to Menu"
    // ������ ����������� ����� � ������
};

#endif // WIN_SCENE_H
