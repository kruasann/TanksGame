#include "ContactListener.h"
#include <iostream>

// Конструктор класса ContactListener
ContactListener::ContactListener(SoundPlayer& soundPlayer)
    : soundPlayer(soundPlayer) {
    hitSound = Mix_LoadWAV("Assets/Sounds/Target_down_v2.mp3"); // Загрузка звукового эффекта попадания
}

// Деструктор класса ContactListener
ContactListener::~ContactListener() {
    if (hitSound) {
        Mix_FreeChunk(hitSound); // Освобождение ресурсов, занятых звуковым эффектом
    }
}

// Функция, вызываемая при начале контакта между двумя физическими телами
void ContactListener::BeginContact(b2Contact* contact) {
    b2Fixture* fixtureA = contact->GetFixtureA(); // Получение первого участника контакта
    b2Fixture* fixtureB = contact->GetFixtureB(); // Получение второго участника контакта

    // Получение пользовательских данных
    auto userDataA = reinterpret_cast<void*>(fixtureA->GetBody()->GetUserData().pointer);
    auto userDataB = reinterpret_cast<void*>(fixtureB->GetBody()->GetUserData().pointer);

    // Приведение типов пользовательских данных к соответствующим классам
    Projectile* projectileA = static_cast<Projectile*>(userDataA);
    Projectile* projectileB = static_cast<Projectile*>(userDataB);
    Target* targetA = static_cast<Target*>(userDataA);
    Target* targetB = static_cast<Target*>(userDataB);

    // Проверка и обработка столкновений
    // Если снаряд сталкивается с целью и цель не была ранее поражена
    if (projectileA && !projectileA->isMarkedForDeletion() && targetB && !targetB->isHit()) {
        projectileA->collide(); // Обработка столкновения снаряда
        targetB->markAsHit(); // Отметка цели как пораженной
        Mix_PlayChannel(-1, hitSound, 0); // Воспроизведение звука попадания
    }
    else if (projectileB && !projectileB->isMarkedForDeletion() && targetA && !targetA->isHit()) {
        projectileB->collide(); // Аналогично для снаряда B и цели A
        targetA->markAsHit();
        Mix_PlayChannel(-1, hitSound, 0);
    }
    else if (projectileA) {
        projectileA->collide(); // Обработка столкновения снаряда A
    }
    else if (projectileB) {
        projectileB->collide(); // Обработка столкновения снаряда B
    }
}