// Tank.cpp
#include "tank.h"
#include "../Utils/Utils.h" // Assuming you have a utility file for common functions
const float SCALE = 32.0f;

Tank::Tank(SDL_Renderer* ren, b2World* world, float x, float y)
    : renderer(ren), movingLeft(false), movingRight(false), speed(5.0f) {
    // Load the tank texture
    texture = loadTexture("Assets/Sprites/Tanks_parts/tracks.png", renderer);
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody; // Убедитесь, что танк динамичен
    bodyDef.position.Set(x, y); // Позиция задается в метрах
    body = world->CreateBody(&bodyDef);

    float halfWidth = textureWidth  / SCALE; // Ширина танка в метрах
    float halfHeight = textureHeight / SCALE; // Высота танка в метрах

    b2PolygonShape shape;
    shape.SetAsBox(halfWidth, halfHeight);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f; // Плотность
    fixtureDef.friction = 0.9f; // Трение
    body->CreateFixture(&fixtureDef);
}

Tank::~Tank() {
    // Clean up resources
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    // Note: The Box2D world will destroy the body
}

void Tank::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && !event.key.repeat) {
        if (event.key.keysym.sym == SDLK_a) {
            movingLeft = true;
        }
        else if (event.key.keysym.sym == SDLK_d) {
            movingRight = true;
        }
    }
    else if (event.type == SDL_KEYUP && !event.key.repeat) {
        if (event.key.keysym.sym == SDLK_a) {
            movingLeft = false;
        }
        else if (event.key.keysym.sym == SDLK_d) {
            movingRight = false;
        }
    }
}



void Tank::update() {
    float desiredVelocity = 0.0f;

    if (movingLeft) {
        desiredVelocity -= speed;
    }
    if (movingRight) {
        desiredVelocity += speed;
    }

    // Установка скорости напрямую
    body->SetLinearVelocity(b2Vec2(desiredVelocity, body->GetLinearVelocity().y));
}




void Tank::render() {
    b2Vec2 position = body->GetPosition();
    SDL_Rect rect = {
        static_cast<int>(position.x * SCALE - textureWidth / 2),
        static_cast<int>(position.y * SCALE - textureHeight / 2),
        textureWidth,
        textureHeight
    };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}


