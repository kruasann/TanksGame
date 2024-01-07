#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include <box2d/box2d.h>
#include "../Assets/Projectile.h" // Импорт определения класса Projectile
#include "../Objects/Physics/Target.h"

// Класс ContactListener, наследуемый от b2ContactListener
class ContactListener : public b2ContactListener {
public:
    // Переопределение метода BeginContact, который вызывается при начале контакта между двумя физическими телами
    void BeginContact(b2Contact* contact) override;
};

#endif // CONTACT_LISTENER_H
