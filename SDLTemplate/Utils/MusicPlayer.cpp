// Подключение заголовочного файла MusicPlayer.h
#include "MusicPlayer.h"

// Конструктор класса MusicPlayer
MusicPlayer::MusicPlayer() : music(nullptr), musicEnabled(true) {}

// Деструктор класса MusicPlayer
MusicPlayer::~MusicPlayer() {
    if (music) {
        Mix_FreeMusic(music); // Освобождение ресурсов музыки
    }
}

// Загрузка музыкального файла
bool MusicPlayer::loadMusic(const std::string& filename) {
    music = Mix_LoadMUS(filename.c_str()); // Загрузка музыки из файла
    return music != nullptr; // Возвращаем true, если загрузка успешна
}

// Воспроизведение музыки
void MusicPlayer::playMusic() {
    if (music && !Mix_PlayingMusic()) {
        Mix_PlayMusic(music, -1); // Воспроизведение музыки, если она не играет
    }
}

// Остановка музыки
void MusicPlayer::stopMusic() {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic(); // Остановка воспроизведения музыки
    }
}

// Пауза музыки
void MusicPlayer::pauseMusic() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic(); // Приостановка воспроизведения музыки
    }
}

// Продолжение воспроизведения музыки
void MusicPlayer::resumeMusic() {
    if (music && Mix_PausedMusic()) {
        Mix_ResumeMusic(); // Продолжение воспроизведения музыки после паузы
    }
}

// Включение музыки
void MusicPlayer::enableMusic() {
    musicEnabled = true;
}

// Выключение музыки
void MusicPlayer::disableMusic() {
    musicEnabled = false;
}

// Установка уровня громкости
void MusicPlayer::setVolume(int volume) {
    Mix_VolumeMusic(volume); // Установка уровня громкости музыки
}

// Получение текущего уровня громкости
int MusicPlayer::currentVolume() const {
    return Mix_VolumeMusic(-1); // Возвращает текущий уровень громкости музыки
}

// Проверка, воспроизводится ли музыка
bool MusicPlayer::isPlaying() const {
    return Mix_PlayingMusic(); // Возвращает true, если музыка воспроизводится
}

// Проверка, включена ли музыка
bool MusicPlayer::isMusicEnabled() const {
    return musicEnabled; // Возвращает true, если музыка включена
}