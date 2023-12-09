// MusicPlayer.cpp
#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() : music(nullptr), musicEnabled(true) {}

MusicPlayer::~MusicPlayer() {
    if (music) {
        Mix_FreeMusic(music);
    }
}

bool MusicPlayer::loadMusic(const std::string& filename) {
    music = Mix_LoadMUS(filename.c_str());
    return music != nullptr;
}

void MusicPlayer::playMusic() {
    if (music && !Mix_PlayingMusic()) {
        Mix_PlayMusic(music, -1); // ≈сли музыка не играет, начинаем воспроизведение
    }
}

void MusicPlayer::stopMusic() {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic(); // ќстанавливаем воспроизведение музыки
    }
}

void MusicPlayer::pauseMusic() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic(); // ѕриостанавливаем воспроизведение музыки
    }
}

void MusicPlayer::resumeMusic() {
    if (music && Mix_PausedMusic()) {
        Mix_ResumeMusic(); // ≈сли музыка приостановлена, продолжаем воспроизведение
    }
}

void MusicPlayer::enableMusic() {
    musicEnabled = true;
}

void MusicPlayer::disableMusic() {
    musicEnabled = false;
}

void MusicPlayer::setVolume(int volume) {
    Mix_VolumeMusic(volume);
}

int MusicPlayer::currentVolume() const {
    return Mix_VolumeMusic(-1); // -1 возвращает текущий уровень громкости
}

bool MusicPlayer::isPlaying() const {
    return Mix_PlayingMusic();
}


bool MusicPlayer::isMusicEnabled() const {
    return musicEnabled;
}