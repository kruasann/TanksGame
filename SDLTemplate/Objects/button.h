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
            tex = activeTexture; // Переключение на активную текстуру, если кнопка активна
        }
        else if (!isTogglable && isHovered) {
            tex = hoverTexture; // Переключение на hover текстуру, если курсор находится над кнопкой
        }

        SDL_RenderCopy(renderer, tex, NULL, &position);

        // Обработка hover звука
        if (isHovered && !wasHovered && soundPlayer) {
            soundPlayer->playSound();
        }

        wasHovered = isHovered; // Обновление предыдущего состояния hover
    }

    void toggle() {
        if (isTogglable) {
            isActive = !isActive;
        }
    }
};

#endif // BUTTON_H