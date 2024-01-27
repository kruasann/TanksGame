#ifndef BASESCENE_H
#define BASESCENE_H

#include <SDL2/SDL.h>
#include "../game_states.h"

// Абстрактный базовый класс для всех сцен в игре.
class BaseScene {
public:
    // Конструктор класса, принимающий указатель на SDL_Renderer.
    BaseScene(SDL_Renderer* renderer) : renderer(renderer) {}

    // Виртуальный деструктор. Необходим для корректного удаления производных объектов.
    virtual ~BaseScene() {}

    // Чисто виртуальные функции, которые должны быть переопределены в производных классах.

    // Обработка событий. Каждая сцена будет иметь свою реализацию обработки событий.
    virtual void handleEvents(const SDL_Event& event, GameState& gameState) = 0;

    // Отрисовка сцены. Каждая сцена будет иметь свою реализацию отрисовки.
    virtual void render() = 0;

    // Обновление состояния сцены. Каждая сцена будет иметь свою реализацию обновления.
    virtual GameState updateState() = 0;

protected:
    SDL_Renderer* renderer; // Указатель на SDL_Renderer, используемый для отрисовки.
};

#endif // BASESCENE_H
