#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <box2d/box2d.h>
#include <vector>
#include <iostream>

class Projectile {
public:
    Projectile(SDL_Renderer* renderer, b2World* world, float x, float y, float angle, float force);
    ~Projectile();
    b2Body* getBody() const { return body; }
    void update();
    void render();
    bool isMarkedForDeletion() const { return markedForDeletion; }
    void markForDeletion() { markedForDeletion = true; }
    // ����� ��� ������ ��� ������������ �������
    void collide();

    // ������� ��� ��������, ���������� �� ������
    bool isCollided() const {
        return hasCollided;
    }

private:
    SDL_Renderer* renderer;
    Mix_Chunk* collisionSound;
    b2Body* body;
    SDL_Texture* texture;
    SDL_Texture* explosionTexture; // �������� ������
    int explosionTimer = 0;       // ������ ��� ������� ������� ������
    int textureWidth, textureHeight;
    bool markedForDeletion = false; // ���� ��� �������� �������
    bool hasCollided = false;
    std::vector<b2Vec2> tracerPositions;
    const size_t maxTracerCount = 120; // ������������ ���������� ����������� �������

};

#endif // PROJECTILE_H
