#include "Projectile.h"
#include "../Utils/Utils.h"

Projectile::Projectile(SDL_Renderer* ren, b2World* world, float x, float y, float angle, float force) 
    : renderer(ren) {
    texture = loadTexture("Assets/Sprites/Tanks_parts/projectile.png", renderer);
    explosionTexture = loadTexture("Assets/Sprites/Tanks_parts/explosion.png", renderer);
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    collisionSound = Mix_LoadWAV("Assets/Sounds/boom_sound.mp3");

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    bodyDef.angle = angle * M_PI / 180.0f;
    body = world->CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 5.0f / 5.0f; // Adjust size as needed

    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.5f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    // Apply force to the projectile
    float forceX = cos(angle * M_PI / 180.0f) * force;
    float forceY = sin(angle * M_PI / 180.0f) * force;
    body->ApplyForceToCenter(b2Vec2(forceX, forceY), true);
}

Projectile::~Projectile() {
    if (body) {
        body->GetWorld()->DestroyBody(body);
        body = nullptr;
    }
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    if (explosionTexture) {
        SDL_DestroyTexture(explosionTexture);
    }
    if (collisionSound) {
        Mix_FreeChunk(collisionSound);
    }
}

void Projectile::collide() {
    Mix_PlayChannel(-1, collisionSound, 0);
    texture = explosionTexture; // Смена на текстуру взрыва
    hasCollided = true;
    explosionTimer = 10; // Установка таймера для отображения взрыва
}

void Projectile::update() {
    if (hasCollided && explosionTimer > 0) {
        explosionTimer--;
        if (explosionTimer == 0) {
            markedForDeletion = true;
        }
    }
}


void Projectile::render() {
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle() * 180.0f / M_PI;

    SDL_Rect rect = {
        static_cast<int>(position.x * 5.0f - textureWidth / 2),
        static_cast<int>(position.y * 5.0f - textureHeight / 2),
        textureWidth,
        textureHeight
    };

    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}
