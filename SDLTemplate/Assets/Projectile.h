#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <box2d/box2d.h>
#include <vector>
#include <iostream>

class Projectile {
public:
    Projectile(SDL_Renderer* renderer, b2World* world, float x, float y, float angle, float force);
    ~Projectile();
    b2Body* getBody() const { return body; }
    void update();
    void render();
    bool isMarkedForDeletion() const { return markedForDeletion; }
    void markForDeletion() { markedForDeletion = true; }
    // Метод для вызова при столкновении снаряда
    void collide();

    // Функция для проверки, столкнулся ли снаряд
    bool isCollided() const {
        return hasCollided;
    }

private:
    SDL_Renderer* renderer;
    Mix_Chunk* collisionSound;
    b2Body* body;
    SDL_Texture* texture;
    SDL_Texture* explosionTexture; // Текстура взрыва
    int explosionTimer = 0;       // Таймер для отсчета времени взрыва
    int textureWidth, textureHeight;
    bool markedForDeletion = false; // Флаг для удаления снаряда
    bool hasCollided = false;
    std::vector<b2Vec2> tracerPositions;
    const size_t maxTracerCount = 120; // Максимальное количество сохраняемых позиций

};

#endif // PROJECTILE_H
