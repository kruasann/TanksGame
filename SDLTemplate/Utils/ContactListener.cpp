#include "ContactListener.h"
#include <iostream>

ContactListener::ContactListener(SoundPlayer& soundPlayer)
    : soundPlayer(soundPlayer) {
    hitSound = Mix_LoadWAV("Assets/Sounds/Target_down_v2.mp3");
}

ContactListener::~ContactListener() {
    if (hitSound) {
        Mix_FreeChunk(hitSound);
    }
}

void ContactListener::BeginContact(b2Contact* contact) {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    // ѕолучение пользовательских данных
    auto userDataA = reinterpret_cast<void*>(fixtureA->GetBody()->GetUserData().pointer);
    auto userDataB = reinterpret_cast<void*>(fixtureB->GetBody()->GetUserData().pointer);

    Projectile* projectileA = static_cast<Projectile*>(userDataA);
    Projectile* projectileB = static_cast<Projectile*>(userDataB);
    Target* targetA = static_cast<Target*>(userDataA);
    Target* targetB = static_cast<Target*>(userDataB);

    // ѕроверка и обработка столкновений
    if (projectileA && !projectileA->isMarkedForDeletion() && targetB && !targetB->isHit()) {
        projectileA->collide();
        targetB->markAsHit();
        Mix_PlayChannel(-1, hitSound, 0); // ¬оспроизведение один раз на любом свободном канале
    }
    else if (projectileB && !projectileB->isMarkedForDeletion() && targetA && !targetA->isHit()) {
        projectileB->collide();
        targetA->markAsHit();
        Mix_PlayChannel(-1, hitSound, 0); // ¬оспроизведение один раз на любом свободном канале
    }
    else if (projectileA) {
        projectileA->collide();
    }
    else if (projectileB) {
        projectileB->collide();
    }
}

