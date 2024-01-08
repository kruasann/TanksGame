#include "WinScene.h"
#include "../Utils/Utils.h"
#include <iostream>

// ����������� ������ WinScene.
WinScene::WinScene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(renderer),
    returnToMenuButton(loadTexture("Assets/Sprites/Buttons/Menu_button.png", renderer),
        loadTexture("Assets/Sprites/Buttons/Menu_button_hover.png", renderer),
        400, 600, &soundPlayer),
    backgroundTexture(loadTexture("Assets/Sprites/Win_Menu.png", renderer)) {
}

// ���������� ������ WinScene.
WinScene::~WinScene() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture); // ������������ �������� ������� ��������
    }
}

// ��������� ������� � ����� ������.
void WinScene::handleEvents(const SDL_Event& event, GameState& gameState) {
    int x, y;
    SDL_GetMouseState(&x, &y); // ��������� ��������� ����
    SDL_Point mousePoint = { x, y }; // ����� ��������� �������

    // ��������, ��������� �� ������ �� ������ "��������� � ����".
    returnToMenuButton.isHovered = SDL_PointInRect(&mousePoint, &returnToMenuButton.position);

    // ��������� ����� ����
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (returnToMenuButton.isHovered) {
            returnToMenuButton.isClicked = true; // ��������� ����� ����� �� ������
        }
    }
}

// ��������� ����� ������.
void WinScene::render() {
    renderTexture(backgroundTexture, renderer, 0, 0); // ��������� ����
    returnToMenuButton.render(renderer); // ��������� ������ "��������� � ����"
    SDL_RenderPresent(renderer); // ���������� ������
}

// ���������� ��������� ����� ������.
GameState WinScene::updateState() {
    if (returnToMenuButton.isClicked) {
        returnToMenuButton.isClicked = false;
        return GameState::MainMenu; // ������� � ������� ����
    }
    return GameState::Win; // ���������� � ����� ������
}
