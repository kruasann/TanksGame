// ������ ����������� ������ MusicPlayer � ������������ �����
#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

// ����������� ���������� SDL2 ��� ������ �� ������
#include <SDL2/SDL_mixer.h>
#include <string>

// ���������� ������ MusicPlayer
class MusicPlayer {
private:
    Mix_Music* music; // ��������� �� ����������� ����
    bool musicEnabled;  // ���� ��������� ��������������� ������

public:
    // ����������� � ����������
    MusicPlayer();
    ~MusicPlayer();

    // ������ ��� ���������� �������
    bool loadMusic(const std::string& filename);
    void playMusic();
    void stopMusic();
    void pauseMusic();
    void resumeMusic();

    // ������ ��� ���������� ���������� ���������������
    void enableMusic();  // �������� ������
    void disableMusic(); // ��������� ������

    // ������ ��� ���������� ����������
    void setVolume(int volume);
    int currentVolume() const;
    bool isPlaying() const;
    bool isMusicEnabled() const;  // ��������, �������� �� ������

};

// ����� ����������� ������ MusicPlayer
#endif // MUSIC_PLAYER_H