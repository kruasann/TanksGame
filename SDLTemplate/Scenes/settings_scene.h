#ifndef SETTINGS_SCENE_H
#define SETTINGS_SCENE_H

#include <SDL2/SDL.h>
#include "BaseScene.h"
#include "../game_states.h"
#include "../Objects/button.h"
#include "../Objects/slider.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"
#include "../Utils/ConfigurationManager.h"

// ����� SettingsScene ��� ������������� ����� �������� � ����.
class SettingsScene : public BaseScene {
public:
    // ����������� ������, �������������� ����� ��������.
    SettingsScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);

    // ����� ��� ��������� ������� SDL.
    void handleEvents(const SDL_Event& event, GameState& gameState);

    // ����� ��� ���������� ����� ��������.
    void render();

    // ����� ��� ���������� ��������� �����.
    GameState updateState();

private:
    // ��������� ���������� ������.
    MusicPlayer& musicPlayer;     // ������ ��� ���������� �������
    SoundPlayer& soundPlayer;     // ������ ��� ���������� ��������� ���������

    SDL_Texture* backgroundTexture; // �������� ����
    Button backButton;              // ������ "�����"
    Button buttonMusic;             // ������ ���������� �������
    Button buttonSound;             // ������ ���������� �������
    Slider sliderMusic;             // ������� ��������� ������
    Slider sliderSound;             // ������� ��������� ������

    bool musicEnabled;              // ��������� ������ (��������/���������)
    bool soundEnabled;              // ��������� ������ (��������/���������)
};

#endif // SETTINGS_SCENE_H
