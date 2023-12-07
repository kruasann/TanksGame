// slider.h
#ifndef SLIDER_H
#define SLIDER_H

#include <SDL2/SDL.h>

struct Slider {
    SDL_Rect track; // Прямоугольник дорожки ползунка
    SDL_Rect thumb; // Прямоугольник "бегунка" ползунка
    int minValue;
    int maxValue;
    int currentValue;

    Slider(int x, int y, int width, int height, int minVal, int maxVal)
        : minValue(minVal), maxValue(maxVal), currentValue(minVal) {
        track.x = x;
        track.y = y;
        track.w = width;
        track.h = height;

        thumb.w = height; // Делаем ширину бегунка равной высоте дорожки для квадратной формы
        thumb.h = height;
        thumb.x = x; // Начальное положение бегунка
        thumb.y = y;
    }

    // Функция для отрисовки ползунка
    void render(SDL_Renderer* renderer) {
        // Отрисовка дорожки
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Белый цвет
        SDL_RenderFillRect(renderer, &track);

        // Отрисовка бегунка
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Синий цвет
        SDL_RenderFillRect(renderer, &thumb);
    }

    // Функция для обновления положения бегунка
    void update(int mouseX) {
        // Обновление положения бегунка в зависимости от позиции мыши
        thumb.x = mouseX - thumb.w / 2;
        if (thumb.x < track.x) {
            thumb.x = track.x;
        }
        if (thumb.x > track.x + track.w - thumb.w) {
            thumb.x = track.x + track.w - thumb.w;
        }

        // Обновление текущего значения
        float percent = (float)(thumb.x - track.x) / (track.w - thumb.w);
        currentValue = minValue + percent * (maxValue - minValue);
    }

    // Получение текущего значения
    int getValue() const {
        return currentValue;
    }
};

#endif // SLIDER_H
