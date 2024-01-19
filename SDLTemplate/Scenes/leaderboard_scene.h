// leaderboard_scene.h
#ifndef LEADERBOARD_SCENE_H
#define LEADERBOARD_SCENE_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "../game_states.h"
#include "../Objects/button.h"
#include "../Objects/board.h"
#include "../Utils/Utils.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"

// ����� LeaderboardScene ��� ������������� ����� ������� �������.
class LeaderboardScene {
public:
    // ����������� ������, �������������� ����� ������� �������.
    LeaderboardScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);

    // ����� ��� ��������� ������� SDL.
    void handleEvents(const SDL_Event& event);

    // ����� ��� ���������� ����� ������� �������.
    void render();

    // ����� ��� ���������� ��������� �����.
    GameState updateState();

private:
    SDL_Renderer* renderer;        // �������� SDL ��� ���������
    MusicPlayer& musicPlayer;
    SoundPlayer& soundPlayer;
    SDL_Texture* backgroundTexture; // �������� ����
    Button returnToMenuButton;              // ������ "�����"
    std::vector<LeaderboardEntry> leaderboardEntries;
};

#endif // LEADERBOARD_SCENE_H
