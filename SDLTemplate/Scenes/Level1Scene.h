// Level1Scene.h

#ifndef LEVEL1_SCENE_H
#define LEVEL1_SCENE_H

#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <vector>
#include "../game_states.h"
#include "../Assets/tank.h"
#include "../Utils/MusicPlayer.h"
#include "../Utils/SoundPlayer.h"
#include "../Objects/button.h"

class Level1Scene {
public:
    Level1Scene(SDL_Renderer* renderer, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);
    ~Level1Scene();
    void handleEvents(const SDL_Event& event, GameState& gameState);
    void update();
    GameState updateState();
    void render();
    Tank* tank;
    void startMusic();
    void renderTerrain();
    bool isMusicStarted() const;
    void createPhysicsWorld(); // Создание физического мира Box2D
    void createTerrain();      // Создание террейна

private:
    bool musicStarted = false;
    bool pauseEnabled = false;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    Button pauseButton;
    MusicPlayer& musicPlayer;
    SoundPlayer& soundPlayer;
    b2World* physicsWorld; // Указатель на физический мир Box2D
    std::vector<b2Body*> terrainBodies;
};

#endif // LEVEL1_SCENE_H