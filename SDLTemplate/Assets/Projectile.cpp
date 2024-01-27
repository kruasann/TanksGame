#include "Projectile.h"
#include "../Utils/Utils.h"

// ����������� ������ Projectile
Projectile::Projectile(SDL_Renderer* ren, b2World* world, float x, float y, float angle, float force)
    : renderer(ren) {
    // �������� �������� �������
    texture = loadTexture("Assets/Sprites/Tanks_parts/projectile.png", renderer);
    // �������� �������� ������
    explosionTexture = loadTexture("Assets/Sprites/Tanks_parts/explosion.png", renderer);
    // ��������� �������� �������� �������
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    // �������� ����� ������������
    collisionSound = Mix_LoadWAV("Assets/Sounds/boom_sound.mp3");

    // ����������� ���������� ����������� ����
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody; // ������������ ����
    bodyDef.position.Set(x, y);    // ��������� �������
    bodyDef.angle = angle * M_PI / 180.0f; // ��������� ����

    // �������� ����������� ���� � ����
    body = world->CreateBody(&bodyDef);

    // �������� ����� (�����) ��� ����������� ����
    b2CircleShape circleShape;
    circleShape.m_radius = 5.0f / 5.0f; // ������ �������

    // �������� ������� � ����������� ����
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    // ����������� ���������� ������� ���� (���������)
    // ����� ������� � Box2D ����������� ������������� �� ������ ��� ����� � ���������.
    // ����� ������� �������������� ��� ���������, ���������� �� ������� ���� �����.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;          // ���������

    // ���������� ������������ ������� � ����
    body->CreateFixture(&fixtureDef);

    // ���������� ���� � �������
    // ������ �������������� � ������������ ��������� ����, ������ �� ����

    // �������������� ���� �� �������� � ������� ��� ������������������ �������
    // ���� ���������� �� pi � ������� �� 180 ��� �������� � �������
    float forceX = cos(angle * M_PI / 180.0f) * force; // �������������� ���������� ����
    float forceY = sin(angle * M_PI / 180.0f) * force; // ������������ ���������� ����

    // ���������� ������������ �������������� (forceX) � ������������ (forceY) ��������� ����
    // � ������ ���� ���� �������
    // b2Vec2(forceX, forceY) ������� ������ ���� � ���������� ������������
    // 'true' ��������� �� ��, ��� ���� ������ ���� ��������� ����������
    body->ApplyForceToCenter(b2Vec2(forceX, forceY), true);

}

// ���������� ������ Projectile
Projectile::~Projectile() {
    // �������� ����������� ����
    if (body) {
        body->GetWorld()->DestroyBody(body);
        body = nullptr;
    }
    // ����������� �������� �������
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    // ����������� �������� ������
    if (explosionTexture) {
        SDL_DestroyTexture(explosionTexture);
    }
    // ������������ ������ ����� ������������
    if (collisionSound) {
        Mix_FreeChunk(collisionSound);
    }
}

void Projectile::collide() {
    Mix_PlayChannel(-1, collisionSound, 0);
    texture = explosionTexture; // ����� �� �������� ������
    hasCollided = true;
    explosionTimer = 1; // ��������� ������� ��� ����������� ������
}

void Projectile::update() {
    // ��������� ������� ������� � ������ ������
    tracerPositions.insert(tracerPositions.begin(), body->GetPosition());

    // ������� ������ �������, ����� ���������� ������ ������
    if (tracerPositions.size() > maxTracerCount) {
        tracerPositions.pop_back();
    }

    if (hasCollided && explosionTimer > 0) {
        explosionTimer--;
        if (explosionTimer == 0) {
            markedForDeletion = true;
        }
    }
}


// ����� render ���������� ��� ��������� ������� � ��� ��������� �� ������.

void Projectile::render() {

    // ��������� ����� ��� ��������� ���������.
    // � ������ ������ ������ ������ ���� � ������ ���������������.
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    // ���� �� ���� �������� ���������, ����������� � tracerPositions.
    for (const auto& pos : tracerPositions) {
        // �������� �������������� ��� ��������� ������� ��������.
        // pos.x � pos.y - ��� ���������� ������� �������� � ������� �����������.
        // �������� �� 5.0f ��� ��������������� � ������� � �������� 2, ����� ������������ �������.
        SDL_Rect tracerRect = { static_cast<int>(pos.x * 5.0f - 2), static_cast<int>(pos.y * 5.0f - 2), 4, 4 };

        // ��������� �������������� �� ������, ��������������� �������.
        SDL_RenderFillRect(renderer, &tracerRect);
    }

    // ��������� ������� ������� ������� �� ��� ����������� ����.
    b2Vec2 position = body->GetPosition();

    // ��������� �������� ���� �������� ������� � �������������� ��� �� �������� � �������.
    float angle = body->GetAngle() * 180.0f / M_PI;

    // �������� �������������� ��� ��������� �������� �������.
    // ������ ��������� ����� �������, ����� ����� �������� �������� � �������� ����������� ����.
    SDL_Rect rect = {
        static_cast<int>(position.x * 5.0f - textureWidth / 2),
        static_cast<int>(position.y * 5.0f - textureHeight / 2),
        textureWidth,
        textureHeight
    };

    // ��������� �������� ������� �� ������ � ������ ��� �������, ���� �������� � ��� ���������.
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}
