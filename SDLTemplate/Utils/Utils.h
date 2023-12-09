// Utils.h
#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <string>

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y);
SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* ren);

#endif // UTILS_H
