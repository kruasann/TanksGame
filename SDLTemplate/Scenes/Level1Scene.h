// Заголовочный файл для класса Level1Scene
#ifndef LEVEL1_SCENE_H
#define LEVEL1_SCENE_H

#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <vector>
#include "../game_states.h"
#include "../Assets/tank.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"
#include "../Utils/ContactListener.h"
#include "../Objects/button.h"
#include "../Objects/Physics/PhysicalEntity.h"
#include "../Objects/Physics/Target.h"

class Level1Scene {
public:
    // Конструктор класса, инициализирующий сцену уровня 1
    Level1Scene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);

    // Деструктор класса, освобождающий ресурсы
    ~Level1Scene();

    // Обработка событий ввода (например, мыши и клавиатуры)
    void handleEvents(const SDL_Event& event, GameState& gameState);

    // Обновление состояния сцены
    void update();
    ContactListener* myContactListener;

    // Получение текущего состояния игры
    GameState updateState();

    // Отрисовка сцены
    void render();

    void createTargets();   // Метод для создания мишеней
    void renderTargets();   // Метод для рендеринга мишеней
    bool isValidPosition(const std::vector<Target*>& targets, float x, float y, float radius);
    void onTargetHit();

    // Запуск музыки на сцене
    void startMusic();

    // Проверка, началась ли музыка
    bool isMusicStarted() const;

private:
    bool musicStarted = false; // Флаг, указывающий, началась ли музыка
    bool pauseEnabled = false; // Флаг, указывающий, включена ли пауза
    int targetsHit;   // Количество пораженных мишеней
    int score;
    int pointsPerTarget; // Очки за одну мишень
    SDL_Renderer* renderer;    // Рендерер SDL
    SDL_Texture* backgroundTexture; // Текстура фона
    std::vector<Target*> targets; // Вектор для хранения мишеней
    Button pauseButton;             // Кнопка паузы
    MusicPlayer& musicPlayer;       // Плеер музыки
    SoundPlayer& soundPlayer;       // Плеер звуков
    b2World* physicsWorld;          // Физический мир Box2D
    std::vector<b2Body*> terrainBodies; // Тела террейна
    Tank* tank; // Указатель на объект танка

    // Методы класса:
    void createPhysicsWorld(); // Создание физического мира Box2D
    void createTerrain();      // Создание террейна
    void renderTerrain();      // Рендеринг террейна
};

#endif // LEVEL1_SCENE_H