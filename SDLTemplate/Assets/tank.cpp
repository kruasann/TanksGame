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

    fireCooldown = 1000;  // Задержка в миллисекундах
    lastFireTime = 0;     // Инициализация времени последнего выстрела

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
    float barrelLength = 45.f / SCALE;
    float offsetX = cos(angleRad) * barrelLength;
    float offsetY = sin(angleRad) * barrelLength;

    // Вычисляем положение конца ствола
    float barrelEndX = body->GetPosition().x + offsetX;
    float barrelEndY = body->GetPosition().y + offsetY; // Убедитесь, что инверсия оси Y корректна для вашей системы координат

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFireTime < fireCooldown) {
        return; // Если не прошло достаточно времени, не стреляем
    }

    lastFireTime = currentTime; // Обновляем время последнего выстрела

    // Создаем снаряд в этой позиции
    Projectile* newProjectile = new Projectile(renderer, body->GetWorld(), barrelEndX, barrelEndY, barrelAngle, fireForce);
    projectiles.push_back(newProjectile);

    Mix_PlayChannel(-1, fireSound, 0); // Воспроизведение один раз на любом свободном канале

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

    // Проверка, движется ли танк
    if (movingLeft || movingRight) {
        // Воспроизводим звук, если танк начал движение и звук еще не воспроизводится
        if (movingSoundChannel == -1) {
            movingSoundChannel = Mix_PlayChannel(-1, movingSound, -1); // Воспроизведение на любом свободном канале, -1 для бесконечного повторения
        }
    }
    else {
        // Остановка звука, если танк остановился
        if (movingSoundChannel != -1) {
            Mix_HaltChannel(movingSoundChannel);
            movingSoundChannel = -1;
        }
    }

    if (rotatingBarrelUp || rotatingBarrelDown) {
        // Воспроизводим звук, если башня начала поворачиваться и звук еще не воспроизводится
        if (barrelRotationSoundChannel == -1) {
            barrelRotationSoundChannel = Mix_PlayChannel(-1, barrelRotationSound, -1); // Воспроизведение на любом свободном канале, -1 для бесконечного повторения
        }
    }
    else {
        // Остановка звука, если башня остановилась
        if (barrelRotationSoundChannel != -1) {
            Mix_HaltChannel(barrelRotationSoundChannel);
            barrelRotationSoundChannel = -1;
        }
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