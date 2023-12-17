#ifndef PHYSICAL_ENTITY_H
#define PHYSICAL_ENTITY_H

#include <box2d/box2d.h>

class PhysicalEntity {
public:
    PhysicalEntity(b2World* world);
    b2Body* createGround(float x, float y, float width, float height);

private:
    b2World* m_world;
};

#endif // PHYSICAL_ENTITY_H
