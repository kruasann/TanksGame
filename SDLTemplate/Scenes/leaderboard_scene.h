// leaderboard_scene.h
#ifndef LEADERBOARD_SCENE_H
#define LEADERBOARD_SCENE_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "BaseScene.h"
#include "../game_states.h"
#include "../Objects/button.h"
#include "../Objects/board.h"
#include "../Utils/Utils.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"

// ����� LeaderboardScene ��� ������������� ����� ������� �������.
class LeaderboardScene : public BaseScene {
public:
    // ����������� ������, �������������� ����� ������� �������.
    LeaderboardScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);

    // ����� ��� ��������� ������� SDL.
    void handleEvents(const SDL_Event& event, GameState& gameState);

    // ����� ��� ���������� ����� ������� �������.
    void render();

    // ����� ��� ���������� ��������� �����.
    GameState updateState();

private:
    MusicPlayer& musicPlayer;
    SoundPlayer& soundPlayer;
    SDL_Texture* backgroundTexture; // �������� ����
    Button returnToMenuButton;              // ������ "�����"
    std::vector<LeaderboardEntry> leaderboardEntries;
};

#endif // LEADERBOARD_SCENE_H
