#include "Target.h"
#include "../../Utils/Utils.h"

const float SCALE = 5.0f;

Target::Target(b2World* world, float x, float y, float radius, SDL_Renderer* renderer)
    : radius(radius), hit(false) {

    targetTexture = loadTexture("Assets/Sprites/Target.png", renderer); // Загрузка текстуры мишени

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);
    body = world->CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    body->CreateFixture(&fixtureDef);
}

Target::~Target() {
    if (body) {
        body->GetWorld()->DestroyBody(body);
    }

    if (targetTexture) {
        SDL_DestroyTexture(targetTexture);
    }
}

void Target::render(SDL_Renderer* renderer) {
    if (targetTexture && !hit) { // Проверка, что текстура загружена и мишень не поражена
        SDL_Rect targetRect;
        targetRect.x = body->GetPosition().x * SCALE - radius * SCALE; // Позиционирование мишени
        targetRect.y = body->GetPosition().y * SCALE - radius * SCALE;
        targetRect.w = radius * 2 * SCALE; // Установка размера мишени
        targetRect.h = radius * 2 * SCALE;

        SDL_RenderCopy(renderer, targetTexture, NULL, &targetRect);
    }
}


bool Target::isHit() const {
    return hit;
}

void Target::markAsHit() {
    hit = true;
}

float Target::getX() const {
    return body->GetPosition().x;
}

float Target::getY() const {
    return body->GetPosition().y;
}
