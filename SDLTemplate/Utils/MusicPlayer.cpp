// ����������� ������������� ����� MusicPlayer.h
#include "MusicPlayer.h"

// ����������� ������ MusicPlayer
MusicPlayer::MusicPlayer() : music(nullptr), musicEnabled(true) {}

// ���������� ������ MusicPlayer
MusicPlayer::~MusicPlayer() {
    if (music) {
        Mix_FreeMusic(music); // ������������ �������� ������
    }
}

// �������� ������������ �����
bool MusicPlayer::loadMusic(const std::string& filename) {
    music = Mix_LoadMUS(filename.c_str()); // �������� ������ �� �����
    return music != nullptr; // ���������� true, ���� �������� �������
}

// ��������������� ������
void MusicPlayer::playMusic() {
    if (music && !Mix_PlayingMusic()) {
        Mix_PlayMusic(music, -1); // ��������������� ������, ���� ��� �� ������
    }
}

// ��������� ������
void MusicPlayer::stopMusic() {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic(); // ��������� ��������������� ������
    }
}

// ����� ������
void MusicPlayer::pauseMusic() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic(); // ������������ ��������������� ������
    }
}

// ����������� ��������������� ������
void MusicPlayer::resumeMusic() {
    if (music && Mix_PausedMusic()) {
        Mix_ResumeMusic(); // ����������� ��������������� ������ ����� �����
    }
}

// ��������� ������
void MusicPlayer::enableMusic() {
    musicEnabled = true;
}

// ���������� ������
void MusicPlayer::disableMusic() {
    musicEnabled = false;
}

// ��������� ������ ���������
void MusicPlayer::setVolume(int volume) {
    Mix_VolumeMusic(volume); // ��������� ������ ��������� ������
}

// ��������� �������� ������ ���������
int MusicPlayer::currentVolume() const {
    return Mix_VolumeMusic(-1); // ���������� ������� ������� ��������� ������
}

// ��������, ��������������� �� ������
bool MusicPlayer::isPlaying() const {
    return Mix_PlayingMusic(); // ���������� true, ���� ������ ���������������
}

// ��������, �������� �� ������
bool MusicPlayer::isMusicEnabled() const {
    return musicEnabled; // ���������� true, ���� ������ ��������
}