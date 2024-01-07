#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include <box2d/box2d.h>
#include "../Assets/Projectile.h" // ������ ����������� ������ Projectile
#include "../Objects/Physics/Target.h"

// ����� ContactListener, ����������� �� b2ContactListener
class ContactListener : public b2ContactListener {
public:
    // ��������������� ������ BeginContact, ������� ���������� ��� ������ �������� ����� ����� ����������� ������
    void BeginContact(b2Contact* contact) override;
};

#endif // CONTACT_LISTENER_H
