// button.h
#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

struct Button {
    SDL_Texture* normalTexture;
    SDL_Texture* hoverTexture;
    SDL_Rect position;
    bool isHovered;
    bool isClicked;

    Button(SDL_Texture* normal, SDL_Texture* hover, int x, int y)
        : normalTexture(normal), hoverTexture(hover), isHovered(false), isClicked(false) {
        position.x = x;
        position.y = y;
        SDL_QueryTexture(normal, NULL, NULL, &position.w, &position.h);
    }

    void render(SDL_Renderer* renderer) {
        SDL_Texture* tex = isHovered ? hoverTexture : normalTexture;
        SDL_RenderCopy(renderer, tex, NULL, &position);
    }
};

#endif // BUTTON_H
