// ������������ ���� ��� ������ Level1Scene
#ifndef LEVEL1_SCENE_H
#define LEVEL1_SCENE_H

#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <vector>
#include <chrono>
#include <string>
#include <sstream>   // ��� std::stringstream
#include <iomanip>   // ��� std::setfill � std::setw
#include "../game_states.h"
#include "../Assets/tank.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"
#include "../Utils/ContactListener.h"
#include "../Objects/button.h"
#include "../Objects/Physics/PhysicalEntity.h"
#include "../Objects/Physics/Target.h"

class Level1Scene {
public:
    // ����������� ������, ���������������� ����� ������ 1
    Level1Scene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer, bool& pauseEnabled);

    // ���������� ������, ������������� �������
    ~Level1Scene();

    // ��������� ������� ����� (��������, ���� � ����������)
    void handleEvents(const SDL_Event& event, GameState& gameState);

    // ���������� ��������� �����
    void update();
    ContactListener* myContactListener;

    // ��������� �������� ��������� ����
    GameState updateState();

    // ��������� �����
    void render();

    void createTargets();   // ����� ��� �������� �������
    void renderTargets();   // ����� ��� ���������� �������
    bool isValidPosition(const std::vector<Target*>& targets, float x, float y, float radius);
    void onTargetHit();

    // ������ ������ �� �����
    void startMusic();

    // ��������, �������� �� ������
    bool isMusicStarted() const;

    int totalTargets = 0; // ���������� ������� �� �����

    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point currentTime;
    std::string formattedTime; // ������ ��� �������� ������������������ �������

    // ���������� ������ ��� �������������� �������
    std::string formatTime(double milliseconds);

private:
    bool musicStarted = false; // ����, �����������, �������� �� ������
    bool& pauseEnabled;
    int targetsHit;   // ���������� ���������� �������
    int score;
    bool allTargetsHit;
    std::string endTime; // ��� �������� ������� ���������
    int pointsPerTarget; // ���� �� ���� ������
    SDL_Renderer* renderer;    // �������� SDL
    SDL_Texture* backgroundTexture; // �������� ����
    std::vector<Target*> targets; // ������ ��� �������� �������
    Button pauseButton;             // ������ �����
    MusicPlayer& musicPlayer;       // ����� ������
    SoundPlayer& soundPlayer;       // ����� ������
    b2World* physicsWorld;          // ���������� ��� Box2D
    std::vector<b2Body*> terrainBodies; // ���� ��������
    Tank* tank; // ��������� �� ������ �����

    // ������ ������:
    void createPhysicsWorld(); // �������� ����������� ���� Box2D
    void createTerrain();      // �������� ��������
    void renderTerrain();      // ��������� ��������
};

#endif // LEVEL1_SCENE_H