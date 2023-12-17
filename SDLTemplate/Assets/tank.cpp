#include "tank.h"
#include "../Utils/Utils.h"

const float SCALE = 5.0f;

Tank::Tank(SDL_Renderer* ren, b2World* world, float x, float y)
    : renderer(ren), movingLeft(false), movingRight(false),
    rotatingBarrelUp(false), rotatingBarrelDown(false),
    speed(8.0f), barrelAngle(0.0f), rotationSpeed(1.0f), fireForce(1000000.0f) {

    texture = loadTexture("Assets/Sprites/Tanks_parts/tracks.png", renderer);
    barrelTexture = loadTexture("Assets/Sprites/Tanks_parts/barrel.png", renderer);
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    body = world->CreateBody(&bodyDef);

    float halfWidth = 64.0f / SCALE / 2.0f;  // половина ширины танка в метрах
    float halfHeight = 32.0f / SCALE / 2.0f; // половина высоты танка в метрах
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
    for (auto& projectile : projectiles) {
        delete projectile;
    }
}

void Tank::handleEvent(const SDL_Event& event) {
    // Обработка событий клавиатуры
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
            fire(); // Вызов функции стрельбы
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

// Метод стрельбы
void Tank::fire() {
    // Угол ствола в радианах
    float angleRad = barrelAngle * M_PI / 180.0f;

    // Рассчитываем смещение конца ствола относительно центра танка
    float barrelLength = 32.f / SCALE;
    float offsetX = cos(angleRad) * barrelLength;
    float offsetY = sin(angleRad) * barrelLength;

    // Вычисляем положение конца ствола
    float barrelEndX = body->GetPosition().x + offsetX;
    float barrelEndY = body->GetPosition().y + offsetY; // Убедитесь, что инверсия оси Y корректна для вашей системы координат

    // Создаем снаряд в этой позиции
    Projectile* newProjectile = new Projectile(renderer, body->GetWorld(), barrelEndX, barrelEndY, barrelAngle, fireForce);
    projectiles.push_back(newProjectile);
}



void Tank::update() {
    // Обновление позиции танка
    float desiredVelocity = 0.0f;
    if (movingLeft) desiredVelocity -= speed;
    if (movingRight) desiredVelocity += speed;
    body->SetLinearVelocity(b2Vec2(desiredVelocity, body->GetLinearVelocity().y));

    // Обновление угла ствола
    if (rotatingBarrelUp) {
        barrelAngle += rotationSpeed;
        if (barrelAngle > 360.0f) barrelAngle -= 360.0f;
    }
    else if (rotatingBarrelDown) {
        barrelAngle -= rotationSpeed;
        if (barrelAngle < 0.0f) barrelAngle += 360.0f;
    }
}

void Tank::render() {
    b2Vec2 position = body->GetPosition();

    // Отрисовка ствола танка
    if (barrelTexture) {
        int barrelWidth, barrelHeight;
        SDL_QueryTexture(barrelTexture, NULL, NULL, &barrelWidth, &barrelHeight);

        // Позиционирование ствола так, чтобы ось вращения находилась на его краю
        SDL_Rect barrelRect = {
            static_cast<int>(position.x * SCALE), // Смещение позиции ствола
            static_cast<int>(position.y * SCALE - barrelHeight),
            barrelWidth,
            barrelHeight
        };

        // Точка вращения смещена вправо
        SDL_Point center = { 0, barrelHeight / 2 };

        SDL_RenderCopyEx(renderer, barrelTexture, NULL, &barrelRect, barrelAngle, &center, SDL_FLIP_NONE);
    }

    // Отрисовка танка
    SDL_Rect tankRect = {
        static_cast<int>(position.x * SCALE - textureWidth / 2),
        static_cast<int>(position.y * SCALE - textureHeight / 2),
        textureWidth,
        textureHeight
    };
    SDL_RenderCopy(renderer, texture, NULL, &tankRect);

    // Отрисовка снарядов
    for (auto& projectile : projectiles) {
        projectile->render();
    }

}