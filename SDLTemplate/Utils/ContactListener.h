#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include <box2d/box2d.h>
#include "../Assets/Projectile.h"
#include "../Objects/Physics/Target.h"
#include "../Utils/SoundPlayer.h"
#include <SDL2/SDL_mixer.h>

// Класс ContactListener, наследующийся от b2ContactListener из Box2D.
// Используется для обработки физических столкновений в игре.
class ContactListener : public b2ContactListener {
public:
    ContactListener(SoundPlayer& soundPlayer); // Конструктор
    ~ContactListener(); // Деструктор

    // Переопределенная функция, вызываемая при начале контакта между двумя физическими телами.
    void BeginContact(b2Contact* contact) override;

private:
    SoundPlayer& soundPlayer; // Ссылка на проигрыватель звуков
    Mix_Chunk* hitSound; // Звук попадания
};

#endif // CONTACT_LISTENER_H