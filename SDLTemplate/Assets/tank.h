#ifndef TANK_H
#define TANK_H

#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include "Projectile.h"
#include <vector>

class Tank {
public:
    Tank(SDL_Renderer* renderer, b2World* world, float x, float y);
    ~Tank();
    void handleEvent(const SDL_Event& event);
    void update();
    void render();
    void fire(); // Добавлен метод стрельбы
    void clearProjectiles(); // Очистить снаряды
    std::vector<Projectile*>& getProjectiles() { return projectiles; }

private:
    SDL_Renderer* renderer;
    b2Body* body;
    SDL_Texture* texture;
    SDL_Texture* barrelTexture;
    int textureWidth, textureHeight;
    bool movingLeft, movingRight;
    bool rotatingBarrelUp, rotatingBarrelDown;
    float speed, barrelAngle, rotationSpeed, fireForce;
    std::vector<Projectile*> projectiles; // Снаряды
};

#endif // TANK_H
