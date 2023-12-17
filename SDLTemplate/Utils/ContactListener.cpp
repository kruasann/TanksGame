#include "ContactListener.h"
#include <iostream>

void ContactListener::BeginContact(b2Contact* contact) {
    std::cout << "BeginContact called." << std::endl;
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    Projectile* projectileA = reinterpret_cast<Projectile*>(fixtureA->GetBody()->GetUserData().pointer);
    Projectile* projectileB = reinterpret_cast<Projectile*>(fixtureB->GetBody()->GetUserData().pointer);

    if (projectileA) {
        projectileA->collide();
    }
    else if (projectileB) {
        projectileB->collide();
    }
}
