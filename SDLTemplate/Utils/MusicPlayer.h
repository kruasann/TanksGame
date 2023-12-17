// Начало определения класса MusicPlayer в заголовочном файле
#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

// Подключение библиотеки SDL2 для работы со звуком
#include <SDL2/SDL_mixer.h>
#include <string>

// Объявление класса MusicPlayer
class MusicPlayer {
private:
    Mix_Music* music; // Указатель на музыкальный трек
    bool musicEnabled;  // Флаг состояния воспроизведения музыки

public:
    // Конструктор и деструктор
    MusicPlayer();
    ~MusicPlayer();

    // Методы для управления музыкой
    bool loadMusic(const std::string& filename);
    void playMusic();
    void stopMusic();
    void pauseMusic();
    void resumeMusic();

    // Методы для управления состоянием воспроизведения
    void enableMusic();  // Включить музыку
    void disableMusic(); // Выключить музыку

    // Методы для управления громкостью
    void setVolume(int volume);
    int currentVolume() const;
    bool isPlaying() const;
    bool isMusicEnabled() const;  // Проверка, включена ли музыка

};

// Конец определения класса MusicPlayer
#endif // MUSIC_PLAYER_H