// Level1Scene.cpp

#include "Level1Scene.h"
#include "../Utils/Utils.h"
#include "../Utils/ContactListener.h"
#include "../Objects/button.h"
#include <iostream>
#include <vector>

const float SCALE = 5.0f; // Коэффициент масштабирования между Box2D и пикселями

// Конструктор класса Level1Scene
Level1Scene::Level1Scene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(renderer),
    musicPlayer(musicPlayer),
    soundPlayer(soundPlayer),
    musicStarted(false),
    backgroundTexture(loadTexture("Assets/Sprites/Level1_background.png", renderer)),
    pauseButton(loadTexture("Assets\\Sprites\\Buttons\\pause_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\pause_button_hover.png", renderer),
        25, 25, &soundPlayer) {

    // Создание физического мира Box2D с гравитацией
    createPhysicsWorld();

    std::cout << "Was Volume: " << static_cast<int>(musicPlayer.currentVolume()) << std::endl;

    // Создание террейна, включая землю и стены
    createTerrain();

    // Инициализация начальной позиции танка
    float initialXPosition = 400.0f / SCALE;
    float initialYPosition = 400.0f / SCALE;

    // Создание танка
    tank = new Tank(renderer, physicsWorld, initialXPosition, initialYPosition);

    myContactListener = new ContactListener();
    physicsWorld->SetContactListener(myContactListener);
}

// Деструктор класса Level1Scene
Level1Scene::~Level1Scene() {
    // Уничтожение фона
    SDL_DestroyTexture(backgroundTexture);

    // Удаление танка
    if (tank) {
        delete tank;
        tank = nullptr;
    }

    // Освобождение ресурсов физического мира Box2D
    delete myContactListener;
    delete physicsWorld;
}

// Рендеринг террейна
// Создание физического мира Box2D
void Level1Scene::createPhysicsWorld() {
    // Установка гравитации
    b2Vec2 gravity(0.0f, 10.0f * SCALE); // Создание вектора гравитации, где 10.0f - ускорение свободного падения по оси Y (x, y)
    physicsWorld = new b2World(gravity); // Инициализация физического мира с заданной гравитацией
}

// Создание террейна
void Level1Scene::createTerrain() {
    // Определение и создание земли
    b2BodyDef groundBodyDef;
    // Позиция земли в нижней части экрана
    float groundHeight = 256.0f; // Высота поверхности
    groundBodyDef.position.Set(1024 / 2.0f / SCALE, (1024 - groundHeight / 2) / SCALE);

    b2Body* groundBody = physicsWorld->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    // Установка размера земли (ширина, высота)
    groundBox.SetAsBox(1024 / 2.0f / SCALE, groundHeight / 2 / SCALE);
    groundBody->CreateFixture(&groundBox, 0.0f);

    terrainBodies.push_back(groundBody);

    // Создание стен
    // Левая стена
    b2BodyDef leftWallBodyDef;
    leftWallBodyDef.position.Set(10.0f / SCALE / 2, 1024 / 2.0f / SCALE); // Установка позиции для левой стены
    b2Body* leftWallBody = physicsWorld->CreateBody(&leftWallBodyDef); // Создание тела для левой стены
    b2PolygonShape leftWallBox;
    leftWallBox.SetAsBox(10.0f / SCALE / 2, 1024 / SCALE); // Определение формы левой стены
    leftWallBody->CreateFixture(&leftWallBox, 0.0f); // Присоединение формы к телу левой стены

    // Правая стена
    b2BodyDef rightWallBodyDef;
    rightWallBodyDef.position.Set((1024 - 10.0f / 2) / SCALE, 1024 / 2.0f / SCALE); // Установка позиции для правой стены
    b2Body* rightWallBody = physicsWorld->CreateBody(&rightWallBodyDef); // Создание тела для правой стены
    b2PolygonShape rightWallBox;
    rightWallBox.SetAsBox(10.0f / SCALE / 2, 1024 / 2.0f / SCALE); // Определение формы правой стены
    rightWallBody->CreateFixture(&rightWallBox, 0.0f); // Присоединение формы к телу правой стены

    terrainBodies.push_back(leftWallBody); // Добавление левой стены в список террейнов
    terrainBodies.push_back(rightWallBody); // Добавление правой стены в список террейнов
}

// Рендеринг террейна
void Level1Scene::renderTerrain() {
    // Рендеринг всех физических тел в террейне
    for (b2Body* body : terrainBodies) {
        b2PolygonShape* shape = dynamic_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape()); // Получение формы тела
        if (shape) {
            b2Vec2 pos = body->GetPosition(); // Получение позиции тела
            float angle = body->GetAngle(); // Получение угла наклона тела

            bool isWall = (shape->m_vertices[1].x * 2 * SCALE < 1024 / 2); // Определение, является ли тело стеной

            // Установка цвета для рендеринга
            if (isWall) {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // Установка серого цвета для стен
            }
            else {
                SDL_SetRenderDrawColor(renderer, 45, 158, 230, 255); // Установка голубого цвета для земли
            }

            SDL_Rect rect;
            rect.x = (pos.x * SCALE) - (shape->m_vertices[1].x * SCALE); // Установка координаты X для рендеринга
            rect.y = (pos.y * SCALE) - (shape->m_vertices[1].y * SCALE);  // Установка координаты Y для рендеринга
            rect.w = shape->m_vertices[1].x * 2 * SCALE; // Установка ширины прямоугольника для рендеринга
            rect.h = shape->m_vertices[1].y * 2 * SCALE; // Установка высоты прямоугольника для рендеринга

            SDL_RenderFillRect(renderer, &rect); // Отрисовка прямоугольника
        }
    }
}




// Обработка событий
void Level1Scene::handleEvents(const SDL_Event& event, GameState& gameState) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mousePoint = { x, y };

    if (tank) {
        tank->handleEvent(event);
    }

    pauseButton.isHovered = SDL_PointInRect(&mousePoint, &pauseButton.position);

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (pauseButton.isHovered) {
            pauseButton.isClicked = true;
            gameState = GameState::Pause;
        }
    }

    // Обработка нажатия клавиши ESC
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        if (gameState == GameState::Pause) {
            // Если игра уже на паузе, возвращаемся к игровой сцене
            gameState = GameState::Level1;
        }
        else {
            // Если игра не на паузе, переходим в режим паузы
            gameState = GameState::Pause;
        }
    }
}

void Level1Scene::update() {
    // Обновление состояния физического мира и танка

    // Установка временного шага для физической симуляции
    const float timeStep = 1.0f / 60.0f;
    // Установка количества итераций для расчета скорости тел в физическом мире
    const int32 velocityIterations = 100;
    // Установка количества итераций для расчета позиций тел в физическом мире
    const int32 positionIterations = 100;
    // Обновление состояния физического мира на один временной шаг
    physicsWorld->Step(timeStep, velocityIterations, positionIterations);


    if (tank) {
        tank->update();
    }

    if (tank) {
        auto& projectiles = tank->getProjectiles();
        for (auto it = projectiles.begin(); it != projectiles.end();) {
            (*it)->update(); // Убедитесь, что этот вызов присутствует
            if ((*it)->isMarkedForDeletion()) {
                delete* it;
                it = projectiles.erase(it);
            }
            else {
                ++it;
            }
        }
    }

}

// Обновление состояния сцены
GameState Level1Scene::updateState() {
    if (pauseEnabled) {
        pauseEnabled = true;
        return GameState::Pause;
    }

    // Возвращаем текущее состояние игры
    return GameState::Level1;
}

// Рендеринг сцены
void Level1Scene::render() {
    // Очищаем экран
    SDL_RenderClear(renderer);
    // Рендерим фон
    renderTexture(backgroundTexture, renderer, 0, 0);
    pauseButton.render(renderer);
    // Вызываем функцию рендеринга террейна
    renderTerrain();
    if (tank) {
        tank->render();
    }
    // Показываем отрендеренное на экране
    SDL_RenderPresent(renderer);
}

// Начало воспроизведения музыки
void Level1Scene::startMusic() {
    musicPlayer.stopMusic();
    if (musicPlayer.isMusicEnabled()) {
        musicPlayer.loadMusic("Assets\\Sounds\\Level1_music.mp3");
        musicPlayer.playMusic();
        musicStarted = true;
    }
}

// Проверка, началась ли музыка
bool Level1Scene::isMusicStarted() const {
    return musicStarted;
}
