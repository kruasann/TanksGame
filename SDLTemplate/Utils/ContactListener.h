#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include <box2d/box2d.h>
#include "../Assets/Projectile.h"
#include "../Objects/Physics/Target.h"
#include "../Utils/SoundPlayer.h"
#include <SDL2/SDL_mixer.h>

class ContactListener : public b2ContactListener {
public:
    ContactListener(SoundPlayer& soundPlayer);
    ~ContactListener();

    void BeginContact(b2Contact* contact) override;

private:
    SoundPlayer& soundPlayer;
    Mix_Chunk* hitSound; // Звук попадания
};

#endif // CONTACT_LISTENER_H
