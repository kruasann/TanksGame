// button.h
#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include "../Utils/SoundPlayer.h"

// Структура Button для создания и управления кнопками в пользовательском интерфейсе
struct Button {
    // Текстуры для разных состояний кнопки: обычное, при наведении и активное
    SDL_Texture* normalTexture;
    SDL_Texture* hoverTexture;
    SDL_Texture* activeTexture;

    // Прямоугольник, определяющий позицию и размер кнопки
    SDL_Rect position;

    // Переменные для отслеживания состояний кнопки
    bool isHovered;  // Курсор наведен на кнопку
    bool isClicked;  // Кнопка нажата
    bool isTogglable; // Можно ли переключать кнопку
    bool isActive;   // Кнопка активна (только если isTogglable true)

    // Указатель на SoundPlayer для воспроизведения звуков при определенных действиях
    SoundPlayer* soundPlayer;

    // Предыдущее состояние hover для обработки звука
    bool wasHovered;

    // Конструктор для создания кнопки
    Button(SDL_Texture* normal, SDL_Texture* hover, int x, int y, SoundPlayer* soundPlayer = nullptr, SDL_Texture* active = nullptr, bool togglable = false)
        : normalTexture(normal), hoverTexture(hover), activeTexture(active),
        isHovered(false), isTogglable(togglable), isActive(false), isClicked(false),
        soundPlayer(soundPlayer), wasHovered(false) {
        position.x = x;
        position.y = y;
        // Определение размеров кнопки на основе её обычной текстуры
        SDL_QueryTexture(normal, NULL, NULL, &position.w, &position.h);
    }

    // Функция для отрисовки кнопки
    void render(SDL_Renderer* renderer) {
        SDL_Texture* tex = normalTexture;

        // Определение, какую текстуру использовать в зависимости от состояния кнопки
        if (isTogglable && isActive && activeTexture) {
            tex = activeTexture; // Переключение на активную текстуру, если кнопка активна
        }
        else if (!isTogglable && isHovered) {
            tex = hoverTexture; // Переключение на текстуру при наведении, если курсор на кнопке
        }

        // Отрисовка кнопки с выбранной текстурой
        SDL_RenderCopy(renderer, tex, NULL, &position);

        // Воспроизведение звука при наведении на кнопку
        if (isHovered && !wasHovered && soundPlayer) {
            soundPlayer->playSound();
        }

        wasHovered = isHovered; // Обновление предыдущего состояния hover
    }

    // Функция для переключения состояния активности кнопки
    void toggle() {
        if (isTogglable) {
            isActive = !isActive;
        }
    }
};

#endif // BUTTON_H
