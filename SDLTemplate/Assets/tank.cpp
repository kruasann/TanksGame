#include "tank.h"
#include "../Utils/Utils.h"

const float SCALE = 5.0f;

Tank::Tank(SDL_Renderer* ren, b2World* world, float x, float y)
    : renderer(ren), movingLeft(false), movingRight(false),
    rotatingBarrelUp(false), rotatingBarrelDown(false),
    speed(8.0f), barrelAngle(0.0f), rotationSpeed(1.0f), fireForce(3000000.0f) {

    texture = loadTexture("Assets/Sprites/Tanks_parts/tracks.png", renderer);
    barrelTexture = loadTexture("Assets/Sprites/Tanks_parts/barrel.png", renderer);
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    movingSound = Mix_LoadWAV("Assets/Sounds/tank_driving_sound.mp3");
    barrelRotationSound = Mix_LoadWAV("Assets/Sounds/barrel_moving_sound.mp3");
    fireSound = Mix_LoadWAV("Assets/Sounds/shoot_sound.mp3");

    fireCooldown = 1000;  // �������� � �������������
    lastFireTime = 0;     // ������������� ������� ���������� ��������

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    body = world->CreateBody(&bodyDef);

    float halfWidth = 64.0f / SCALE / 2.0f;  // �������� ������ ����� � ������
    float halfHeight = 32.0f / SCALE / 2.0f; // �������� ������ ����� � ������
    b2PolygonShape shape;
    shape.SetAsBox(halfWidth, halfHeight);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.9f;
    fixtureDef.friction = 1.9f;
    body->CreateFixture(&fixtureDef);
}

Tank::~Tank() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    if (barrelTexture) {
        SDL_DestroyTexture(barrelTexture);
    }

    if (movingSound) {
        Mix_FreeChunk(movingSound);
    }
    if (barrelRotationSound) {
        Mix_FreeChunk(barrelRotationSound);
    }
    if (fireSound) {
        Mix_FreeChunk(fireSound);
    }

    for (auto& projectile : projectiles) {
        delete projectile;
    }
}

void Tank::handleEvent(const SDL_Event& event) {
    // ��������� ������� ����������
    if (event.type == SDL_KEYDOWN && !event.key.repeat) {
        switch (event.key.keysym.sym) {
        case SDLK_a:
            movingLeft = true;
            break;
        case SDLK_d:
            movingRight = true;
            break;
        case SDLK_w:
            rotatingBarrelUp = true;
            break;
        case SDLK_s:
            rotatingBarrelDown = true;
            break;
        case SDLK_SPACE:
            fire(); // ����� ������� ��������
            break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
        case SDLK_a:
            movingLeft = false;
            break;
        case SDLK_d:
            movingRight = false;
            break;
        case SDLK_w:
            rotatingBarrelUp = false;
            break;
        case SDLK_s:
            rotatingBarrelDown = false;
            break;
        }
    }
}

// ����� ��������
void Tank::fire() {
    // ���� ������ � ��������
    float angleRad = barrelAngle * M_PI / 180.0f;

    // ������������ �������� ����� ������ ������������ ������ �����
    float barrelLength = 45.f / SCALE;
    float offsetX = cos(angleRad) * barrelLength;
    float offsetY = sin(angleRad) * barrelLength;

    // ��������� ��������� ����� ������
    float barrelEndX = body->GetPosition().x + offsetX;
    float barrelEndY = body->GetPosition().y + offsetY; // ���������, ��� �������� ��� Y ��������� ��� ����� ������� ���������

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFireTime < fireCooldown) {
        return; // ���� �� ������ ���������� �������, �� ��������
    }

    lastFireTime = currentTime; // ��������� ����� ���������� ��������

    // ������� ������ � ���� �������
    Projectile* newProjectile = new Projectile(renderer, body->GetWorld(), barrelEndX, barrelEndY, barrelAngle, fireForce);
    projectiles.push_back(newProjectile);

    Mix_PlayChannel(-1, fireSound, 0); // ��������������� ���� ��� �� ����� ��������� ������

}



void Tank::update() {
    // ���������� ������� �����
    float desiredVelocity = 0.0f;
    if (movingLeft) desiredVelocity -= speed;
    if (movingRight) desiredVelocity += speed;
    body->SetLinearVelocity(b2Vec2(desiredVelocity, body->GetLinearVelocity().y));

    // ���������� ���� ������
    if (rotatingBarrelUp) {
        barrelAngle += rotationSpeed;
        if (barrelAngle > 360.0f) barrelAngle -= 360.0f;
    }
    else if (rotatingBarrelDown) {
        barrelAngle -= rotationSpeed;
        if (barrelAngle < 0.0f) barrelAngle += 360.0f;
    }

    // ��������, �������� �� ����
    if (movingLeft || movingRight) {
        // ������������� ����, ���� ���� ����� �������� � ���� ��� �� ���������������
        if (movingSoundChannel == -1) {
            movingSoundChannel = Mix_PlayChannel(-1, movingSound, -1); // ��������������� �� ����� ��������� ������, -1 ��� ������������ ����������
        }
    }
    else {
        // ��������� �����, ���� ���� �����������
        if (movingSoundChannel != -1) {
            Mix_HaltChannel(movingSoundChannel);
            movingSoundChannel = -1;
        }
    }

    if (rotatingBarrelUp || rotatingBarrelDown) {
        // ������������� ����, ���� ����� ������ �������������� � ���� ��� �� ���������������
        if (barrelRotationSoundChannel == -1) {
            barrelRotationSoundChannel = Mix_PlayChannel(-1, barrelRotationSound, -1); // ��������������� �� ����� ��������� ������, -1 ��� ������������ ����������
        }
    }
    else {
        // ��������� �����, ���� ����� ������������
        if (barrelRotationSoundChannel != -1) {
            Mix_HaltChannel(barrelRotationSoundChannel);
            barrelRotationSoundChannel = -1;
        }
    }
}

void Tank::render() {
    b2Vec2 position = body->GetPosition();

    // ��������� ������ �����
    if (barrelTexture) {
        int barrelWidth, barrelHeight;
        SDL_QueryTexture(barrelTexture, NULL, NULL, &barrelWidth, &barrelHeight);

        // ���������������� ������ ���, ����� ��� �������� ���������� �� ��� ����
        SDL_Rect barrelRect = {
            static_cast<int>(position.x * SCALE), // �������� ������� ������
            static_cast<int>(position.y * SCALE - barrelHeight),
            barrelWidth,
            barrelHeight
        };

        // ����� �������� ������� ������
        SDL_Point center = { 0, barrelHeight / 2 };

        SDL_RenderCopyEx(renderer, barrelTexture, NULL, &barrelRect, barrelAngle, &center, SDL_FLIP_NONE);
    }

    // ��������� �����
    SDL_Rect tankRect = {
        static_cast<int>(position.x * SCALE - textureWidth / 2),
        static_cast<int>(position.y * SCALE - textureHeight / 2),
        textureWidth,
        textureHeight
    };
    SDL_RenderCopy(renderer, texture, NULL, &tankRect);

    // ��������� ��������
    for (auto& projectile : projectiles) {
        projectile->render();
    }

}