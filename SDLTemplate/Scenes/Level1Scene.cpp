// Level1Scene.cpp

// Подключаем заголовочные файлы
#include "Level1Scene.h"
#include "../Utils/Utils.h"
#include "../Objects/button.h"
#include <iostream>
#include <vector>

// Определяем масштаб преобразования из метров в пиксели для Box2D
const float SCALE = 32.0f;

// Конструктор класса Level1Scene
Level1Scene::Level1Scene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
    : renderer(renderer), 
    musicPlayer(musicPlayer), 
    soundPlayer(soundPlayer), 
    musicStarted(false),
    backgroundTexture(loadTexture("Assets/Sprites/Level1_background.png", renderer)),
    pauseButton(loadTexture("Assets\\Sprites\\Buttons\\pause_button.png", renderer),
        loadTexture("Assets\\Sprites\\Buttons\\pause_button_hover.png", renderer),
        25, 25, &soundPlayer)
{
    // Создаем физический мир Box2D
    createPhysicsWorld();
    std::cout << "Was Volume: " << static_cast<int>(musicPlayer.currentVolume()) << std::endl;
    // Создаем террейн (поверхность земли и препятствия)
    createTerrain();
    float initialXPosition = 300.0f / SCALE; // Примерное значение, может быть изменено
    float initialYPosition = 400.0f / SCALE; // Примерное значение, может быть изменено

    tank = new Tank(renderer, physicsWorld, initialXPosition, initialYPosition);

}

// Деструктор класса Level1Scene
Level1Scene::~Level1Scene() {
    // Уничтожаем текстуру фона
    SDL_DestroyTexture(backgroundTexture);
    if (tank) {
        delete tank;
        tank = nullptr;
    }

    // Освобождаем ресурсы, занятые физическим миром Box2D
    delete physicsWorld;
}

// Создаем физический мир Box2D
void Level1Scene::createPhysicsWorld() {
    // Устанавливаем гравитацию (0 по X и -10 по Y)
    b2Vec2 gravity(0.0f, -10.0f); // Например, гравитация вниз
    physicsWorld = new b2World(gravity);

}

// Создаем террейн
void Level1Scene::createTerrain() {
    // Определяем статическое тело для земли
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f / SCALE); // Позиция в мире Box2D, переведенная в метры

    // Создаем тело в физическом мире
    b2Body* groundBody = physicsWorld->CreateBody(&groundBodyDef);

    // Определяем форму для земли (прямоугольник)
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f); // 50 метров ширины и 10 метров высоты

    // Добавляем фиксированную форму к телу
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Сохраняем тело для рендеринга
    terrainBodies.push_back(groundBody);

}

// Функция для рендеринга террейна
void Level1Scene::renderTerrain() {
    // Устанавливаем цвет для рендеринга тел Box2D (голубой для земли)
    SDL_SetRenderDrawColor(renderer, 45, 158, 230, 255);

    // Рендерим тела Box2D
    for (b2Body* body : terrainBodies) {
        b2PolygonShape* shape = dynamic_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape());
        if (shape) {
            // Получаем позицию и угол тела
            b2Vec2 pos = body->GetPosition();
            float angle = body->GetAngle();

            // Создаем прямоугольник для рендеринга
            SDL_Rect rect;
            rect.x = (pos.x * SCALE);
            rect.y = (1024 - (pos.y * SCALE)) - (shape->m_vertices[1].y * SCALE);
            rect.w = shape->m_vertices[1].x * 2 * SCALE;
            rect.h = shape->m_vertices[1].y * 2 * SCALE;

            // Рендерим прямоугольник
            SDL_RenderFillRect(renderer, &rect);
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

    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;
    physicsWorld->Step(timeStep, velocityIterations, positionIterations);

    if (tank) {
        tank->update();
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
