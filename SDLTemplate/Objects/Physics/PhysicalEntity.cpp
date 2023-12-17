#include "PhysicalEntity.h"

PhysicalEntity::PhysicalEntity(b2World* world) : m_world(world) {}

b2Body* PhysicalEntity::createGround(float x, float y, float width, float height) {
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(x, y);

    b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(width / 2.0f, height / 2.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    return groundBody;
}
