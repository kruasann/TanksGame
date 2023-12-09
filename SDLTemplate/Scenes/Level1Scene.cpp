// Level1Scene.cpp

// ���������� ������������ �����
#include "Level1Scene.h"
#include "../Utils/Utils.h"
#include "../Objects/button.h"
#include <iostream>
#include <vector>

// ���������� ������� �������������� �� ������ � ������� ��� Box2D
const float SCALE = 32.0f;

// ����������� ������ Level1Scene
Level1Scene::Level1Scene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(renderer), 
    musicPlayer(musicPlayer), 
    soundPlayer(soundPlayer), 
    musicStarted(false),
    backgroundTexture(loadTexture("Assets/Sprites/Level1_background.png", renderer)),
    pauseButton(loadTexture("Assets\\Sprites\\Buttons\\pause_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\pause_button_hover.png", renderer),
        25, 25, &soundPlayer)
{
    // ������� ���������� ��� Box2D
    createPhysicsWorld();
    std::cout << "Was Volume: " << static_cast<int>(musicPlayer.currentVolume()) << std::endl;
    // ������� ������� (����������� ����� � �����������)
    createTerrain();
    float initialXPosition = 300.0f / SCALE; // ��������� ��������, ����� ���� ��������
    float initialYPosition = 400.0f / SCALE; // ��������� ��������, ����� ���� ��������

    tank = new Tank(renderer, physicsWorld, initialXPosition, initialYPosition);

}

// ���������� ������ Level1Scene
Level1Scene::~Level1Scene() {
    // ���������� �������� ����
    SDL_DestroyTexture(backgroundTexture);
    if (tank) {
        delete tank;
        tank = nullptr;
    }

    // ����������� �������, ������� ���������� ����� Box2D
    delete physicsWorld;
}

// ������� ���������� ��� Box2D
void Level1Scene::createPhysicsWorld() {
    // ������������� ���������� (0 �� X � -10 �� Y)
    b2Vec2 gravity(0.0f, -10.0f); // ��������, ���������� ����
    physicsWorld = new b2World(gravity);

}

// ������� �������
void Level1Scene::createTerrain() {
    // ���������� ����������� ���� ��� �����
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f / SCALE); // ������� � ���� Box2D, ������������ � �����

    // ������� ���� � ���������� ����
    b2Body* groundBody = physicsWorld->CreateBody(&groundBodyDef);

    // ���������� ����� ��� ����� (�������������)
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f); // 50 ������ ������ � 10 ������ ������

    // ��������� ������������� ����� � ����
    groundBody->CreateFixture(&groundBox, 0.0f);

    // ��������� ���� ��� ����������
    terrainBodies.push_back(groundBody);

}

// ������� ��� ���������� ��������
void Level1Scene::renderTerrain() {
    // ������������� ���� ��� ���������� ��� Box2D (������� ��� �����)
    SDL_SetRenderDrawColor(renderer, 45, 158, 230, 255);

    // �������� ���� Box2D
    for (b2Body* body : terrainBodies) {
        b2PolygonShape* shape = dynamic_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape());
        if (shape) {
            // �������� ������� � ���� ����
            b2Vec2 pos = body->GetPosition();
            float angle = body->GetAngle();

            // ������� ������������� ��� ����������
            SDL_Rect rect;
            rect.x = (pos.x * SCALE);
            rect.y = (1024 - (pos.y * SCALE)) - (shape->m_vertices[1].y * SCALE);
            rect.w = shape->m_vertices[1].x * 2 * SCALE;
            rect.h = shape->m_vertices[1].y * 2 * SCALE;

            // �������� �������������
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

// ��������� �������
void Level1Scene::handleEvents(const SDL_Event& event, GameState& gameState) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mousePoint = { x, y };

    if (tank) {
        tank->handleEvent(event);
    }

    pauseButton.isHovered = SDL_PointInRect(&mousePoint, &pauseButton.position);

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (pauseButton.isHovered) {
            pauseButton.isClicked = true;
            gameState = GameState::Pause;
        }
    }

    // ��������� ������� ������� ESC
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        if (gameState == GameState::Pause) {
            // ���� ���� ��� �� �����, ������������ � ������� �����
            gameState = GameState::Level1;
        }
        else {
            // ���� ���� �� �� �����, ��������� � ����� �����
            gameState = GameState::Pause;
        }
    }
}

void Level1Scene::update() {

    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;
    physicsWorld->Step(timeStep, velocityIterations, positionIterations);

    if (tank) {
        tank->update();
    }
}

// ���������� ��������� �����
GameState Level1Scene::updateState() {
    if (pauseEnabled) {
        pauseEnabled = true;
        return GameState::Pause;
    }

    // ���������� ������� ��������� ����
    return GameState::Level1;
}

// ��������� �����
void Level1Scene::render() {
    // ������� �����
    SDL_RenderClear(renderer);
    // �������� ���
    renderTexture(backgroundTexture, renderer, 0, 0);
    pauseButton.render(renderer);
    // �������� ������� ���������� ��������
    renderTerrain();
    if (tank) {
        tank->render();
    }
    // ���������� ������������� �� ������
    SDL_RenderPresent(renderer);
}

// ������ ��������������� ������
void Level1Scene::startMusic() {
    musicPlayer.stopMusic();
    if (musicPlayer.isMusicEnabled()) {
        musicPlayer.loadMusic("Assets\\Sounds\\Level1_music.mp3");
        musicPlayer.playMusic();
        musicStarted = true;
    }
}

// ��������, �������� �� ������
bool Level1Scene::isMusicStarted() const {
    return musicStarted;
}
