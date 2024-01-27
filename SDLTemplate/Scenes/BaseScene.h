#ifndef BASESCENE_H
#define BASESCENE_H

#include <SDL2/SDL.h>
#include "../game_states.h"

// ����������� ������� ����� ��� ���� ���� � ����.
class BaseScene {
public:
    // ����������� ������, ����������� ��������� �� SDL_Renderer.
    BaseScene(SDL_Renderer* renderer) : renderer(renderer) {}

    // ����������� ����������. ��������� ��� ����������� �������� ����������� ��������.
    virtual ~BaseScene() {}

    // ����� ����������� �������, ������� ������ ���� �������������� � ����������� �������.

    // ��������� �������. ������ ����� ����� ����� ���� ���������� ��������� �������.
    virtual void handleEvents(const SDL_Event& event, GameState& gameState) = 0;

    // ��������� �����. ������ ����� ����� ����� ���� ���������� ���������.
    virtual void render() = 0;

    // ���������� ��������� �����. ������ ����� ����� ����� ���� ���������� ����������.
    virtual GameState updateState() = 0;

protected:
    SDL_Renderer* renderer; // ��������� �� SDL_Renderer, ������������ ��� ���������.
};

#endif // BASESCENE_H
