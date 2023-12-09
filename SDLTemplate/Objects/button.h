// button.h
#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include "../Utils/SoundPlayer.h"

struct Button {
    SDL_Texture* normalTexture;
    SDL_Texture* hoverTexture;
    SDL_Texture* activeTexture;
    SDL_Rect position;
    bool isHovered;
    bool isClicked;
    bool isTogglable;
    bool isActive;
    SoundPlayer* soundPlayer;
    bool wasHovered;

    Button(SDL_Texture* normal, SDL_Texture* hover, int x, int y, SoundPlayer* soundPlayer = nullptr, SDL_Texture* active = nullptr, bool togglable = false)
        : normalTexture(normal), hoverTexture(hover), activeTexture(active),
        isHovered(false), isTogglable(togglable), isActive(false), isClicked(false),
        soundPlayer(soundPlayer), wasHovered(false) {
        position.x = x;
        position.y = y;
        SDL_QueryTexture(normal, NULL, NULL, &position.w, &position.h);
    }

    void render(SDL_Renderer* renderer) {
        SDL_Texture* tex = normalTexture;

        if (isTogglable && isActive && activeTexture) {
            tex = activeTexture; // ������������ �� �������� ��������, ���� ������ �������
        }
        else if (!isTogglable && isHovered) {
            tex = hoverTexture; // ������������ �� hover ��������, ���� ������ ��������� ��� �������
        }

        SDL_RenderCopy(renderer, tex, NULL, &position);

        // ��������� hover �����
        if (isHovered && !wasHovered && soundPlayer) {
            soundPlayer->playSound();
        }

        wasHovered = isHovered; // ���������� ����������� ��������� hover
    }

    void toggle() {
        if (isTogglable) {
            isActive = !isActive;
        }
    }
};

#endif // BUTTON_H