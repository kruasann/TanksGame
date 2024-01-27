// credits_scene.h
#ifndef CREDITS_SCENE_H
#define CREDITS_SCENE_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "BaseScene.h"
#include "../game_states.h"
#include "../Objects/button.h"
#include "../Utils/Utils.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"

// ����� CreditsScene ��� ������������� ����� ���� � ����.
class CreditsScene : public BaseScene {
public:
    // ����������� ������, �������������� ����� ����.
    CreditsScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);

    // ����� ��� ��������� ������� SDL.
    void handleEvents(const SDL_Event& event, GameState& gameState);

    // ����� ��� ���������� ����� ����.
    void render();

    // ����� ��� ���������� ��������� �����.
    GameState updateState();

private:
    MusicPlayer& musicPlayer;
    SoundPlayer& soundPlayer;
    SDL_Texture* backgroundTexture; // �������� ����
    Button returnToMenuButton;              // ������ "�����"
    std::vector<std::string> creditsTextLines; // ������ ������ ��������
};

#endif // CREDITS_SCENE_H
