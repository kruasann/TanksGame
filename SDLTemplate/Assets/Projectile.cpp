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

    // Определение физических свойств тела (плотность)
    // Масса снаряда в Box2D вычисляется автоматически на основе его формы и плотности.
    // Масса снаряда рассчитывается как плотность, умноженная на площадь этой формы.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;          // Плотность

    // Применение определенных свойств к телу
    body->CreateFixture(&fixtureDef);

    // Применение силы к снаряду
    // Расчет горизонтальной и вертикальной компонент силы, исходя из угла

    // Преобразование угла из градусов в радианы для тригонометрических функций
    // Угол умножается на pi и делится на 180 для перевода в радианы
    float forceX = cos(angle * M_PI / 180.0f) * force; // Горизонтальная компонента силы
    float forceY = sin(angle * M_PI / 180.0f) * force; // Вертикальная компонента силы

    // Применение рассчитанных горизонтальной (forceX) и вертикальной (forceY) компонент силы
    // к центру масс тела снаряда
    // b2Vec2(forceX, forceY) создает вектор силы с указанными компонентами
    // 'true' указывает на то, что сила должна быть приложена немедленно
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
    // Добавляем текущую позицию в начало списка
    tracerPositions.insert(tracerPositions.begin(), body->GetPosition());

    // Удаляем старые позиции, чтобы ограничить размер списка
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


// Метод render вызывается для отрисовки снаряда и его трассеров на экране.

void Projectile::render() {

    // Установка цвета для рисования трассеров.
    // В данном случае выбран желтый цвет с полной непрозрачностью.
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    // Цикл по всем позициям трассеров, сохраненным в tracerPositions.
    for (const auto& pos : tracerPositions) {
        // Создание прямоугольника для отрисовки каждого трассера.
        // pos.x и pos.y - это координаты позиции трассера в мировых координатах.
        // Умножаем на 5.0f для масштабирования в пиксели и вычитаем 2, чтобы центрировать трассер.
        SDL_Rect tracerRect = { static_cast<int>(pos.x * 5.0f - 2), static_cast<int>(pos.y * 5.0f - 2), 4, 4 };

        // Отрисовка прямоугольника на экране, представляющего трассер.
        SDL_RenderFillRect(renderer, &tracerRect);
    }

    // Получение текущей позиции снаряда из его физического тела.
    b2Vec2 position = body->GetPosition();

    // Получение текущего угла поворота снаряда и преобразование его из радианов в градусы.
    float angle = body->GetAngle() * 180.0f / M_PI;

    // Создание прямоугольника для отрисовки текстуры снаряда.
    // Расчет координат таким образом, чтобы центр текстуры совпадал с позицией физического тела.
    SDL_Rect rect = {
        static_cast<int>(position.x * 5.0f - textureWidth / 2),
        static_cast<int>(position.y * 5.0f - textureHeight / 2),
        textureWidth,
        textureHeight
    };

    // Отрисовка текстуры снаряда на экране с учетом его позиции, угла поворота и без отражения.
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}
