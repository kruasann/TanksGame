#include "ContactListener.h"
#include <iostream>

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
    }
    else if (projectileB && !projectileB->isMarkedForDeletion() && targetA && !targetA->isHit()) {
        projectileB->collide();
        targetA->markAsHit();
    }
}

