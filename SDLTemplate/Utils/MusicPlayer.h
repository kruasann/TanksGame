#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <SDL2/SDL_mixer.h>
#include <string>

class MusicPlayer {
private:
    Mix_Music* music;
    bool musicEnabled;  // Состояние воспроизведения музыки

public:
    MusicPlayer();
    ~MusicPlayer();

    bool loadMusic(const std::string& filename);
    void playMusic();
    void stopMusic();
    void pauseMusic();
    void resumeMusic();

    void enableMusic();  // Включить музыку
    void disableMusic(); // Выключить музыку

    void setVolume(int volume);
    int currentVolume() const;
    bool isPlaying() const;
    bool isMusicEnabled() const;  // Проверка, включена ли музыка

};

#endif // MUSIC_PLAYER_H
