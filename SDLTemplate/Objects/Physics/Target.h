#ifndef TARGET_H
#define TARGET_H

#include <box2d/box2d.h>
#include <SDL2/SDL.h>

class Target {
public:
    Target(b2World* world, float x, float y, float radius, SDL_Renderer* renderer);
    ~Target();

    SDL_Texture* targetTexture; // Текстура мишени
    void render(SDL_Renderer* renderer);
    void markForDeletion() {
        markedForDeletion = true;
    }
    bool isHit() const;
    void markAsHit();

    float getX() const;
    float getY() const;

private:
    b2Body* body;
    float radius;
    bool hit;
    bool markedForDeletion = false;
};

#endif // TARGET_H
