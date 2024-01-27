#include "Projectile.h"
#include "../Utils/Utils.h"

// Конструктор класса Projectile
Projectile::Projectile(SDL_Renderer* ren, b2World* world, float x, float y, float angle, float force)
    : renderer(ren) {
    // Загрузка текстуры снаряда
    texture = loadTexture("Assets/Sprites/Tanks_parts/projectile.png", renderer);
    // Загрузка текстуры взрыва
    explosionTexture = loadTexture("Assets/Sprites/Tanks_parts/explosion.png", renderer);
    // Получение размеров текстуры снаряда
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    // Загрузка звука столкновения
    collisionSound = Mix_LoadWAV("Assets/Sounds/boom_sound.mp3");

    // Определение параметров физического тела
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody; // Динамическое тело
    bodyDef.position.Set(x, y);    // Начальная позиция
    bodyDef.angle = angle * M_PI / 180.0f; // Начальный угол

    // Создание физического тела в мире
    body = world->CreateBody(&bodyDef);

    // Создание формы (круга) для физического тела
    b2CircleShape circleShape;
    circleShape.m_radius = 5.0f / 5.0f; // Размер радиуса

    // Привязка объекта к физическому телу
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    // Определение физических свойств тела (плотность, упругость, трение)
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;          // Плотность
    //fixtureDef.restitution = 0.5f;      // Упругость
    //fixtureDef.friction = 0.3f;         // Трение

    // Применение определенных свойств к телу
    body->CreateFixture(&fixtureDef);

    // Применение силы к снаряду
    float forceX = cos(angle * M_PI / 180.0f) * force;
    float forceY = sin(angle * M_PI / 180.0f) * force;
    body->ApplyForceToCenter(b2Vec2(forceX, forceY), true);
}

// Деструктор класса Projectile
Projectile::~Projectile() {
    // Удаление физического тела
    if (body) {
        body->GetWorld()->DestroyBody(body);
        body = nullptr;
    }
    // Уничтожение текстуры снаряда
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    // Уничтожение текстуры взрыва
    if (explosionTexture) {
        SDL_DestroyTexture(explosionTexture);
    }
    // Освобождение памяти звука столкновения
    if (collisionSound) {
        Mix_FreeChunk(collisionSound);
    }
}

void Projectile::collide() {
    Mix_PlayChannel(-1, collisionSound, 0);
    texture = explosionTexture; // Смена на текстуру взрыва
    hasCollided = true;
    explosionTimer = 1; // Установка таймера для отображения взрыва
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
