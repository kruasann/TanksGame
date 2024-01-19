// Защита от многократного включения заголовочного файла
#ifndef UTILS_H
#define UTILS_H

// Подключение необходимых библиотек
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

// Объявление функций вспомогательного модуля
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y); // Отрисовка текстуры
SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* ren); // Загрузка текстуры из файла
void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, int fontSize, SDL_Color color); // Функция для отрисовки текста
void appendToLeaderboard(const std::string& filename, const std::string& timeStr, int score);

// Конец защиты от многократного включения
#endif // UTILS_H
