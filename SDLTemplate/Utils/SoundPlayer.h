// Защита от многократного включения заголовочного файла
#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

// Подключение необходимых библиотек
#include <SDL2/SDL_mixer.h>
#include <string>

// Объявление класса SoundPlayer
class SoundPlayer {
private:
    Mix_Chunk* soundEffect; // Указатель на звуковой эффект
    int currentVolume; // Текущий уровень громкости
    bool soundEffectsEnabled; // Флаг включения звуковых эффектов

public:
    // Конструктор и деструктор
    SoundPlayer();
    ~SoundPlayer();

    // Методы для работы со звуком
    bool loadSound(const std::string& filename); // Загрузка звукового файла
    void playSound(); // Воспроизведение звука
    void setVolume(int volume); // Установка уровня громкости
    int getCurrentVolume() const; // Получение текущего уровня громкости

    // Методы для управления звуковыми эффектами
    void enableSoundEffects(); // Включить звуковые эффекты
    void disableSoundEffects(); // Выключить звуковые эффекты
};

// Конец защиты от многократного включения
#endif // SOUND_PLAYER_H
