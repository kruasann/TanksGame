// PhysicalObject.h
#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include "ObjectType.h"

class PhysicalObject {
public:
    virtual ~PhysicalObject() = default;
    virtual ObjectType getType() const = 0;
};

#endif // PHYSICAL_OBJECT_H