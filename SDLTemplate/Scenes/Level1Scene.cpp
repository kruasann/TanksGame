// Level1Scene.cpp

#include "Level1Scene.h"
#include "../Utils/Utils.h"
#include "../Utils/ContactListener.h"
#include "../Objects/button.h"
#include <iostream>
#include <vector>

const float SCALE = 5.0f; // ����������� ��������������� ����� Box2D � ���������

// ����������� ������ Level1Scene
Level1Scene::Level1Scene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(renderer),
    musicPlayer(musicPlayer),
    soundPlayer(soundPlayer),
    musicStarted(false),
    backgroundTexture(loadTexture("Assets/Sprites/Level1_background.png", renderer)),
    pauseButton(loadTexture("Assets\\Sprites\\Buttons\\pause_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\pause_button_hover.png", renderer),
        25, 25, &soundPlayer) {

    // �������� ����������� ���� Box2D � �����������
    createPhysicsWorld();

    std::cout << "Was Volume: " << static_cast<int>(musicPlayer.currentVolume()) << std::endl;

    // �������� ��������, ������� ����� � �����
    createTerrain();

    // ������������� ��������� ������� �����
    float initialXPosition = 400.0f / SCALE;
    float initialYPosition = 400.0f / SCALE;

    // �������� �����
    tank = new Tank(renderer, physicsWorld, initialXPosition, initialYPosition);

    myContactListener = new ContactListener();
    physicsWorld->SetContactListener(myContactListener);
}

// ���������� ������ Level1Scene
Level1Scene::~Level1Scene() {
    // ����������� ����
    SDL_DestroyTexture(backgroundTexture);

    // �������� �����
    if (tank) {
        delete tank;
        tank = nullptr;
    }

    // ������������ �������� ����������� ���� Box2D
    delete myContactListener;
    delete physicsWorld;
}

// ��������� ��������
// �������� ����������� ���� Box2D
void Level1Scene::createPhysicsWorld() {
    // ��������� ����������
    b2Vec2 gravity(0.0f, 10.0f * SCALE); // �������� ������� ����������, ��� 10.0f - ��������� ���������� ������� �� ��� Y (x, y)
    physicsWorld = new b2World(gravity); // ������������� ����������� ���� � �������� �����������
}

// �������� ��������
void Level1Scene::createTerrain() {
    // ����������� � �������� �����
    b2BodyDef groundBodyDef;
    // ������� ����� � ������ ����� ������
    float groundHeight = 256.0f; // ������ �����������
    groundBodyDef.position.Set(1024 / 2.0f / SCALE, (1024 - groundHeight / 2) / SCALE);

    b2Body* groundBody = physicsWorld->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    // ��������� ������� ����� (������, ������)
    groundBox.SetAsBox(1024 / 2.0f / SCALE, groundHeight / 2 / SCALE);
    groundBody->CreateFixture(&groundBox, 0.0f);

    terrainBodies.push_back(groundBody);

    // �������� ����
    // ����� �����
    b2BodyDef leftWallBodyDef;
    leftWallBodyDef.position.Set(10.0f / SCALE / 2, 1024 / 2.0f / SCALE); // ��������� ������� ��� ����� �����
    b2Body* leftWallBody = physicsWorld->CreateBody(&leftWallBodyDef); // �������� ���� ��� ����� �����
    b2PolygonShape leftWallBox;
    leftWallBox.SetAsBox(10.0f / SCALE / 2, 1024 / SCALE); // ����������� ����� ����� �����
    leftWallBody->CreateFixture(&leftWallBox, 0.0f); // ������������� ����� � ���� ����� �����

    // ������ �����
    b2BodyDef rightWallBodyDef;
    rightWallBodyDef.position.Set((1024 - 10.0f / 2) / SCALE, 1024 / 2.0f / SCALE); // ��������� ������� ��� ������ �����
    b2Body* rightWallBody = physicsWorld->CreateBody(&rightWallBodyDef); // �������� ���� ��� ������ �����
    b2PolygonShape rightWallBox;
    rightWallBox.SetAsBox(10.0f / SCALE / 2, 1024 / 2.0f / SCALE); // ����������� ����� ������ �����
    rightWallBody->CreateFixture(&rightWallBox, 0.0f); // ������������� ����� � ���� ������ �����

    terrainBodies.push_back(leftWallBody); // ���������� ����� ����� � ������ ���������
    terrainBodies.push_back(rightWallBody); // ���������� ������ ����� � ������ ���������
}

// ��������� ��������
void Level1Scene::renderTerrain() {
    // ��������� ���� ���������� ��� � ��������
    for (b2Body* body : terrainBodies) {
        b2PolygonShape* shape = dynamic_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape()); // ��������� ����� ����
        if (shape) {
            b2Vec2 pos = body->GetPosition(); // ��������� ������� ����
            float angle = body->GetAngle(); // ��������� ���� ������� ����

            bool isWall = (shape->m_vertices[1].x * 2 * SCALE < 1024 / 2); // �����������, �������� �� ���� ������

            // ��������� ����� ��� ����������
            if (isWall) {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // ��������� ������ ����� ��� ����
            }
            else {
                SDL_SetRenderDrawColor(renderer, 45, 158, 230, 255); // ��������� �������� ����� ��� �����
            }

            SDL_Rect rect;
            rect.x = (pos.x * SCALE) - (shape->m_vertices[1].x * SCALE); // ��������� ���������� X ��� ����������
            rect.y = (pos.y * SCALE) - (shape->m_vertices[1].y * SCALE);  // ��������� ���������� Y ��� ����������
            rect.w = shape->m_vertices[1].x * 2 * SCALE; // ��������� ������ �������������� ��� ����������
            rect.h = shape->m_vertices[1].y * 2 * SCALE; // ��������� ������ �������������� ��� ����������

            SDL_RenderFillRect(renderer, &rect); // ��������� ��������������
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
    // ���������� ��������� ����������� ���� � �����

    // ��������� ���������� ���� ��� ���������� ���������
    const float timeStep = 1.0f / 60.0f;
    // ��������� ���������� �������� ��� ������� �������� ��� � ���������� ����
    const int32 velocityIterations = 100;
    // ��������� ���������� �������� ��� ������� ������� ��� � ���������� ����
    const int32 positionIterations = 100;
    // ���������� ��������� ����������� ���� �� ���� ��������� ���
    physicsWorld->Step(timeStep, velocityIterations, positionIterations);


    if (tank) {
        tank->update();
    }

    if (tank) {
        auto& projectiles = tank->getProjectiles();
        for (auto it = projectiles.begin(); it != projectiles.end();) {
            (*it)->update(); // ���������, ��� ���� ����� ������������
            if ((*it)->isMarkedForDeletion()) {
                delete* it;
                it = projectiles.erase(it);
            }
            else {
                ++it;
            }
        }
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
