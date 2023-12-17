// Подключение заголовочного файла Utils.h
#include "Utils.h"
#include "../src/include/SDL2/SDL.h"
#include "../src/include/SDL2/SDL_image.h"
#include <iostream>

// Функция для отрисовки текстуры на экране
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y) {
    SDL_Rect dst; // Создание прямоугольника для отрисовки
    dst.x = x; // Установка координаты X
    dst.y = y; // Установка координаты Y
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h); // Получение размеров текстуры
    SDL_RenderCopy(ren, tex, NULL, &dst); // Копирование текстуры в рендерер
}

// Функция для загрузки текстуры из файла
SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* ren) {
    SDL_Texture* texture = IMG_LoadTexture(ren, file.c_str()); // Загрузка текстуры
    if (texture == nullptr) {
        std::cout << "LoadTexture error: " << SDL_GetError() << std::endl; // Вывод ошибки, если загрузка не удалась
    }
    return texture; // Возвращение загруженной текстуры
}
