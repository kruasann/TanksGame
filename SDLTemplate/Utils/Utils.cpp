// ����������� ������������� ����� Utils.h
#include "Utils.h"
#include "../src/include/SDL2/SDL.h"
#include "../src/include/SDL2/SDL_image.h"
#include <iostream>

// ������� ��� ��������� �������� �� ������
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y) {
    SDL_Rect dst; // �������� �������������� ��� ���������
    dst.x = x; // ��������� ���������� X
    dst.y = y; // ��������� ���������� Y
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h); // ��������� �������� ��������
    SDL_RenderCopy(ren, tex, NULL, &dst); // ����������� �������� � ��������
}

// ������� ��� �������� �������� �� �����
SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* ren) {
    SDL_Texture* texture = IMG_LoadTexture(ren, file.c_str()); // �������� ��������
    if (texture == nullptr) {
        std::cout << "LoadTexture error: " << SDL_GetError() << std::endl; // ����� ������, ���� �������� �� �������
    }
    return texture; // ����������� ����������� ��������
}

// ������� ��� ��������� ������
void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, int fontSize) {
    TTF_Font* font = TTF_OpenFont("Assets/Fonts/Raleway-Italic.ttf", fontSize);
    if (font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color color = { 0, 0, 0, 255 }; // ����� ����
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (surface == nullptr) {
        TTF_CloseFont(font);
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) {
        TTF_CloseFont(font);
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect renderQuad = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);

    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}