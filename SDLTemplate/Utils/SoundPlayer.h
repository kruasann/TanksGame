#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include <SDL2/SDL_mixer.h>
#include <string>

class SoundPlayer {
private:
    Mix_Chunk* soundEffect;
    int currentVolume;
    bool soundEffectsEnabled;  // Добавляем новую переменную

public:
    SoundPlayer();
    ~SoundPlayer();

    bool loadSound(const std::string& filename);
    void playSound();
    void setVolume(int volume);
    int getCurrentVolume() const;

    void enableSoundEffects();  // Новый метод для включения звуковых эффектов
    void disableSoundEffects();  // Новый метод для выключения звуковых эффектов
};

#endif // SOUND_PLAYER_H
