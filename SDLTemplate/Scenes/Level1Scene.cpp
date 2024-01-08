// Level1Scene.cpp

#include "Level1Scene.h"
#include "../Utils/Utils.h"
#include "../Utils/ContactListener.h"
#include "../Objects/button.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

const float SCALE = 5.0f; // Коэффициент масштабирования между Box2D и пикселями

// Конструктор класса Level1Scene
Level1Scene::Level1Scene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer, bool& pauseEnabled)
    : renderer(renderer),
    musicPlayer(musicPlayer),
    soundPlayer(soundPlayer),
    musicStarted(false),
    pauseEnabled(pauseEnabled),
    backgroundTexture(loadTexture("Assets/Sprites/Level1_background.png", renderer)),
    pauseButton(loadTexture("Assets\\Sprites\\Buttons\\pause_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\pause_button_hover.png", renderer),
        25, 25, &soundPlayer),
    targetsHit(0),
    score(0), pointsPerTarget(100) {

    // Создание физического мира Box2D с гравитацией
    createPhysicsWorld();

    std::cout << "Was Volume: " << static_cast<int>(musicPlayer.currentVolume()) << std::endl;

    // Создание террейна, включая землю и стены
    createTerrain();

    // Инициализация начальной позиции танка
    float initialXPosition = 400.0f / SCALE;
    float initialYPosition = 600.0f / SCALE;

    // Создание танка
    tank = new Tank(renderer, physicsWorld, initialXPosition, initialYPosition);

    myContactListener = new ContactListener();
    physicsWorld->SetContactListener(myContactListener);

    createTargets();
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

    for (auto target : targets) {
        delete target;
    }

    // Освобождение ресурсов физического мира Box2D
    delete myContactListener;
    delete physicsWorld;
}

void Level1Scene::createTargets() {
    float minX = 10.0f, maxX = 180.0f; // Настройте эти значения в соответствии с размерами вашей карты
    float minY = 20.0f, maxY = 100.0f;
    float radius = 4.0f; // Установите радиус мишени

    // Получение текущего времени в миллисекундах для инициализации генератора
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);

    totalTargets = 6; // Установите общее количество мишеней
    for (int i = 0; i < totalTargets; ++i) {
        float x, y;
        do {
            std::uniform_real_distribution<> disX(minX + radius, maxX - radius);
            std::uniform_real_distribution<> disY(minY + radius, maxY - radius);

            x = disX(gen);
            y = disY(gen);
        } while (!isValidPosition(targets, x, y, radius));

        targets.push_back(new Target(physicsWorld, x, y, radius, renderer));
    }
}


void Level1Scene::renderTargets() {
    for (const auto& target : targets) {
        target->render(renderer);
    }
}

bool Level1Scene::isValidPosition(const std::vector<Target*>& targets, float x, float y, float radius) {
    for (const auto& target : targets) {
        float dx = target->getX() - x;
        float dy = target->getY() - y;
        if (sqrt(dx * dx + dy * dy) < 2 * radius) {
            return false; // Слишком близко к другой мишени
        }
    }
    // Добавьте здесь дополнительные проверки для стен и пола
    return true;
}

void Level1Scene::onTargetHit() {
    targetsHit++;
    score += 100; // или любое другое количество очков за мишень
}


// Рендеринг террейна
// Создание физического мира Box2D
void Level1Scene::createPhysicsWorld() {
    // Установка гравитации
    b2Vec2 gravity(0.0f, 12.0f * SCALE); // Создание вектора гравитации, где 10.0f - ускорение свободного падения по оси Y (x, y)
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
            pauseEnabled = true; // Только устанавливаем флаг pauseEnabled
            gameState = GameState::Pause;
        }
    }

    // Обработка нажатия клавиши ESC
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        // Если игра не на паузе, переходим в режим паузы
        pauseEnabled = true;
        gameState = GameState::Pause;
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

    // Обновление снарядов
    if (tank) {
        auto& projectiles = tank->getProjectiles();
        for (auto it = projectiles.begin(); it != projectiles.end();) {
            (*it)->update();
            if ((*it)->isMarkedForDeletion()) {
                delete* it;
                it = projectiles.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    // Обновление мишеней
    for (auto it = targets.begin(); it != targets.end();) {
        if ((*it)->isHit()) {
            delete* it; // Удаление мишени при попадании
            it = targets.erase(it);
            score += pointsPerTarget; // Увеличиваем счет
            targetsHit++; // Увеличиваем счетчик попаданий
        }
        else {
            ++it;
        }
    }

}

// Обновление состояния сцены
GameState Level1Scene::updateState() {
    if (pauseEnabled) {
        return GameState::Pause;
    }

    if (targetsHit == totalTargets) {
        // Если все цели поражены, переключаемся на сцену победы
        return GameState::Win;
    }

    // Возвращаем текущее состояние игры
    pauseEnabled = false;
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
    renderTargets();

    std::string statusText = std::to_string(targetsHit) + "/" + std::to_string(totalTargets) + " Targets Hit | Score: " + std::to_string(score);
    renderText(renderer, statusText, 620, 50, 32);

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
