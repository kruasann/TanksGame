// Utils.cpp
#include "Utils.h"

// Функция для отрисовки текстуры
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
}