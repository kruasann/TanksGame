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

    Slider(int x, int y, int width, int height, int minVal, int maxVal)
        : minValue(minVal), maxValue(maxVal), currentValue(minVal) {
        track.x = x;
        track.y = y;
        track.w = width;
        track.h = height;

        thumb.w = height; // ������ ������ ������� ������ ������ ������� ��� ���������� �����
        thumb.h = height;
        thumb.x = x; // ��������� ��������� �������
        thumb.y = y;
    }

    // ������� ��� ��������� ��������
    void render(SDL_Renderer* renderer) {
        // ��������� �������
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // ����� ����
        SDL_RenderFillRect(renderer, &track);

        // ��������� �������
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // ����� ����
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
