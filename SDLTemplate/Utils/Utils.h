// ������ �� ������������� ��������� ������������� �����
#ifndef UTILS_H
#define UTILS_H

// ����������� ����������� ���������
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

// ���������� ������� ���������������� ������
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y); // ��������� ��������
SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* ren); // �������� �������� �� �����
void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, int fontSize, SDL_Color color); // ������� ��� ��������� ������
void appendToLeaderboard(const std::string& filename, const std::string& timeStr, int score);

// ����� ������ �� ������������� ���������
#endif // UTILS_H
