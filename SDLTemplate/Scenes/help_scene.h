// help_scene.h
#ifndef HELP_SCENE_H
#define HELP_SCENE_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "../game_states.h"
#include "../Objects/button.h"
#include "../Utils/Utils.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"

// ����� HelpScene ��� ������������� ����� ������ � ���������� � ����.
class HelpScene {
public:
    // ����������� ������, �������������� ����� ������.
    HelpScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);

    // ����� ��� ��������� ������� SDL.
    void handleEvents(const SDL_Event& event);

    // ����� ��� ���������� ����� ������.
    void render();

    // ����� ��� ���������� ��������� �����.
    GameState updateState();

private:
    SDL_Renderer* renderer;        // �������� SDL ��� ���������
    MusicPlayer& musicPlayer;
    SoundPlayer& soundPlayer;
    SDL_Texture* backgroundTexture; // �������� ����
    Button returnToMenuButton;              // ������ "�����"
    std::vector<std::string> helpTextLines; // ������ ������ ������
};

#endif // HELP_SCENE_H
