// slider.h
#ifndef SLIDER_H
#define SLIDER_H

#include <SDL2/SDL.h>

// Класс для создания и управления ползунком.
struct Slider {
    SDL_Rect track; // Прямоугольник дорожки ползунка.
    SDL_Rect thumb; // Прямоугольник "бегунка" ползунка.
    int minValue;   // Минимальное значение.
    int maxValue;   // Максимальное значение.
    int currentValue; // Текущее значение.
    bool isDragging;  // Флаг, указывающий, что ползунок перетаскивается.

    // Конструктор.
    Slider(int x, int y, int width, int height, int minVal, int maxVal, int currentValue)
        : minValue(minVal), maxValue(maxVal), currentValue(minVal), isDragging(false) {
        track.x = x; // Координаты и размеры дорожки.
        track.y = y;
        track.w = width;
        track.h = height;

        thumb.w = height; // Ширина бегунка равна высоте дорожки для квадратной формы.
        thumb.h = height;
        // Вычисление начального положения бегунка.
        thumb.x = x + (width - height) * (currentValue - minVal) / (maxVal - minVal);
        thumb.y = y;
    }

    // Функция для отрисовки ползунка.
    void render(SDL_Renderer* renderer) {
        // Отрисовка дорожки.
        SDL_SetRenderDrawColor(renderer, 206, 182, 140, 255); // Цвет дорожки.
        SDL_RenderFillRect(renderer, &track);

        // Отрисовка бегунка.
        SDL_SetRenderDrawColor(renderer, 119, 84, 84, 255); // Цвет бегунка.
        SDL_RenderFillRect(renderer, &thumb);
    }

    // Функция для обновления положения бегунка.
    void update(int mouseX) {
        // Обновление положения бегунка в зависимости от позиции мыши.
        thumb.x = mouseX - thumb.w / 2;
        // Ограничение перемещения бегунка в пределах дорожки.
        if (thumb.x < track.x) {
            thumb.x = track.x;
        }
        if (thumb.x > track.x + track.w - thumb.w) {
            thumb.x = track.x + track.w - thumb.w;
        }

        // Обновление текущего значения.
        float percent = (float)(thumb.x - track.x) / (track.w - thumb.w);
        currentValue = minValue + percent * (maxValue - minValue);
    }

    // Получение текущего значения.
    int getValue() const {
        return currentValue;
    }
};

#endif // SLIDER_H