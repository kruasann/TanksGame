// Подключение заголовочного файла Utils.h
#include "Utils.h"
#include "../src/include/SDL2/SDL.h"
#include "../src/include/SDL2/SDL_image.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

// Функция для отрисовки текстуры на экране
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y) {
    SDL_Rect dst; // Создание прямоугольника для отрисовки
    dst.x = x;    // Установка координаты X
    dst.y = y;    // Установка координаты Y
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

// Функция для отрисовки текста
void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, int fontSize, SDL_Color color) {
    TTF_Font* font = TTF_OpenFont("Assets/Fonts/ofont.ru_Mister Brush.ttf", fontSize); // Загрузка шрифта
    if (font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);  // Создание поверхности с текстом
    if (surface == nullptr) {
        TTF_CloseFont(font);
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); // Создание текстуры из поверхности
    SDL_FreeSurface(surface); // Освобождение памяти, занятой поверхностью
    if (texture == nullptr) {
        TTF_CloseFont(font);
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect renderQuad = { x, y, surface->w, surface->h }; // Определение области для рендеринга текстуры
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad); // Копирование текстуры в рендерер

    SDL_DestroyTexture(texture); // Уничтожение текстуры
    TTF_CloseFont(font);         // Закрытие шрифта
}

void appendToLeaderboard(const std::string& filename, const std::string& timeStr, int score) {
    std::ofstream file;
    file.open(filename, std::ios::app); // Открываем файл в режиме добавления

    // Получаем текущее время
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    // Записываем данные в файл
    file << std::put_time(&tm, "%d-%m-%Y %H:%M:%S") << " Time: " << timeStr << " Score: " << score << std::endl;
    
    file.close();
}