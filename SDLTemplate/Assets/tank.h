// Tank.h
#ifndef TANK_H
#define TANK_H

#include <SDL2/SDL.h>
#include <box2d/box2d.h>

class Tank {
public:
    Tank(SDL_Renderer* renderer, b2World* world, float x, float y);
    ~Tank();
    void handleEvent(const SDL_Event& event);
    void update();
    void render();

private:
    SDL_Renderer* renderer;
    b2Body* body;         // Box2D body for the tank
    SDL_Texture* texture; // Texture for the tank
    int textureWidth;
    int textureHeight;
    bool movingLeft;      // Is the tank moving left?
    bool movingRight;     // Is the tank moving right?
    float speed;          // Movement speed of the tank
};

#endif // TANK_H
