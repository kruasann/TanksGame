// ������ �� ������������� ��������� ������������� �����
#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

// ����������� ����������� ���������
#include <SDL2/SDL_mixer.h>
#include <string>

// ���������� ������ SoundPlayer
class SoundPlayer {
private:
    Mix_Chunk* soundEffect; // ��������� �� �������� ������
    int currentVolume; // ������� ������� ���������
    bool soundEffectsEnabled; // ���� ��������� �������� ��������

public:
    // ����������� � ����������
    SoundPlayer();
    ~SoundPlayer();

    // ������ ��� ������ �� ������
    bool loadSound(const std::string& filename); // �������� ��������� �����
    void playSound(); // ��������������� �����
    void setVolume(int volume); // ��������� ������ ���������
    int getCurrentVolume() const; // ��������� �������� ������ ���������

    // ������ ��� ���������� ��������� ���������
    void enableSoundEffects(); // �������� �������� �������
    void disableSoundEffects(); // ��������� �������� �������
};

// ����� ������ �� ������������� ���������
#endif // SOUND_PLAYER_H
