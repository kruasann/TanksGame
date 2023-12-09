// slider.h
#ifndef SLIDER_H
#define SLIDER_H

#include <SDL2/SDL.h>

struct Slider {
    SDL_Rect track; // ������������� ������� ��������
    SDL_Rect thumb; // ������������� "�������" ��������
    int minValue;
    int maxValue;
    int currentValue;
    bool isDragging;

    Slider(int x, int y, int width, int height, int minVal, int maxVal, int currentValue)
        : minValue(minVal), maxValue(maxVal), currentValue(minVal), isDragging(false) {
        track.x = x;
        track.y = y;
        track.w = width;
        track.h = height;

        thumb.w = height; // ������ ������ ������� ������ ������ ������� ��� ���������� �����
        thumb.h = height;
        thumb.x = x + (width - height) * (currentValue - minVal) / (maxVal - minVal); // ��������� ��������� ���������
        thumb.y = y;
    }

    // ������� ��� ��������� ��������
    void render(SDL_Renderer* renderer) {
        // ��������� �������
        SDL_SetRenderDrawColor(renderer, 206, 182, 140, 255); // ����� ����
        SDL_RenderFillRect(renderer, &track);

        // ��������� �������
        SDL_SetRenderDrawColor(renderer, 119, 84, 84, 255); // ����� ����
        SDL_RenderFillRect(renderer, &thumb);
    }

    // ������� ��� ���������� ��������� �������
    void update(int mouseX) {
        // ���������� ��������� ������� � ����������� �� ������� ����
        thumb.x = mouseX - thumb.w / 2;
        if (thumb.x < track.x) {
            thumb.x = track.x;
        }
        if (thumb.x > track.x + track.w - thumb.w) {
            thumb.x = track.x + track.w - thumb.w;
        }

        // ���������� �������� ��������
        float percent = (float)(thumb.x - track.x) / (track.w - thumb.w);
        currentValue = minValue + percent * (maxValue - minValue);
    }

    // ��������� �������� ��������
    int getValue() const {
        return currentValue;
    }
};

#endif // SLIDER_H
