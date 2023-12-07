#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

// ������� ��� �������� �������� �� �����
SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* ren) {
    SDL_Texture* texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr) {
        std::cout << "LoadTexture error: " << SDL_GetError() << std::endl;
    }
    return texture;
}

// ������� ��� ��������� ��������
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

struct Button {
    SDL_Texture* normalTexture;
    SDL_Texture* hoverTexture;
    SDL_Rect position;
    bool isHovered;

    Button(SDL_Texture* normal, SDL_Texture* hover, int x, int y)
        : normalTexture(normal), hoverTexture(hover), isHovered(false) {
        position.x = x;
        position.y = y;
        SDL_QueryTexture(normal, NULL, NULL, &position.w, &position.h);
    }

    void render(SDL_Renderer* renderer) {
        SDL_Texture* tex = isHovered ? hoverTexture : normalTexture;
        SDL_RenderCopy(renderer, tex, NULL, &position);
    }
};

int main(int, char**) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Game Menu", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 1024, 1024, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture* background = loadTexture("Assets\\Sprites\\Main_menu.png", renderer);

    SDL_Texture* buttonStartNormal = loadTexture("Assets\\Sprites\\Buttons\\Play_button.png", renderer);
    SDL_Texture* buttonStartHover = loadTexture("Assets\\Sprites\\Buttons\\Play_button_hover.png", renderer);
    Button buttonStart(buttonStartNormal, buttonStartHover, 400, 100);

    SDL_Texture* buttonSettingsNormal = loadTexture("Assets\\Sprites\\Buttons\\Settings_button.png", renderer);
    SDL_Texture* buttonSettingsHover = loadTexture("Assets\\Sprites\\Buttons\\Settings_button_hover.png", renderer);
    Button buttonSettings(buttonSettingsNormal, buttonSettingsHover, 400, 200);

    SDL_Texture* buttonExitNormal = loadTexture("Assets\\Sprites\\Buttons\\Exit_button.png", renderer);
    SDL_Texture* buttonExitHover = loadTexture("Assets\\Sprites\\Buttons\\Exit_button_hover.png", renderer);
    Button buttonExit(buttonExitNormal, buttonExitHover, 400, 300);

    // �������� ����
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Point mousePoint = { x, y };

                // ��������� ��������� ����
                buttonStart.isHovered = SDL_PointInRect(&mousePoint, &buttonStart.position);
                buttonSettings.isHovered = SDL_PointInRect(&mousePoint, &buttonSettings.position);
                buttonExit.isHovered = SDL_PointInRect(&mousePoint, &buttonExit.position);
                // ���������� ��� ������ ������...

                // ��������� ������� ������
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (buttonStart.isHovered) {
                        // ������ ��� ������ ����
                    }
                    if (buttonSettings.isHovered) {
                        // ������������ �� ����� ��������
                    }
                    if (buttonExit.isHovered) {
                        running = false; // ����� �� ���������
                    }
                }
                // ���������� ��� ������ ������...
            }
        }

        SDL_RenderClear(renderer);

        renderTexture(background, renderer, 0, 0);
        buttonStart.render(renderer);
        buttonSettings.render(renderer);
        buttonExit.render(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(background);

    SDL_DestroyTexture(buttonStartNormal);
    SDL_DestroyTexture(buttonStartHover);

    SDL_DestroyTexture(buttonSettingsNormal);
    SDL_DestroyTexture(buttonSettingsHover);

    SDL_DestroyTexture(buttonExitNormal);
    SDL_DestroyTexture(buttonExitHover);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
