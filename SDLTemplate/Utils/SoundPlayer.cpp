// Подключение заголовочного файла SoundPlayer.h
#include "SoundPlayer.h"

// Конструктор класса SoundPlayer
SoundPlayer::SoundPlayer() : soundEffect(nullptr), currentVolume(75), soundEffectsEnabled(true) {}

// Деструктор класса SoundPlayer
SoundPlayer::~SoundPlayer() {
    if (soundEffect) {
        Mix_FreeChunk(soundEffect); // Освобождение ресурсов звукового эффекта
    }
}

// Загрузка звукового файла
bool SoundPlayer::loadSound(const std::string& filename) {
    soundEffect = Mix_LoadWAV(filename.c_str()); // Загрузка звукового файла
    return soundEffect != nullptr; // Возвращает true, если загрузка успешна
}

// Воспроизведение звука
void SoundPlayer::playSound() {
    if (soundEffect && soundEffectsEnabled) {
        Mix_PlayChannel(-1, soundEffect, 0); // Воспроизведение звука, если он включен
    }
}

// Установка уровня громкости
void SoundPlayer::setVolume(int volume) {
    if (soundEffect) {
        Mix_VolumeChunk(soundEffect, volume); // Установка уровня громкости звука
    }
    currentVolume = volume;
}

// Получение текущего уровня громкости
int SoundPlayer::getCurrentVolume() const {
    return currentVolume; // Возвращает текущий уровень громкости
}

// Включение звуковых эффектов
void SoundPlayer::enableSoundEffects() {
    soundEffectsEnabled = true;
}

// Выключение звуковых эффектов
void SoundPlayer::disableSoundEffects() {
    soundEffectsEnabled = false;
}
