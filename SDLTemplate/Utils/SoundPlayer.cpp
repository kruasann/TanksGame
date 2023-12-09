#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() : soundEffect(nullptr), currentVolume(75), soundEffectsEnabled(true) {}

SoundPlayer::~SoundPlayer() {
    if (soundEffect) {
        Mix_FreeChunk(soundEffect);
    }
}

bool SoundPlayer::loadSound(const std::string& filename) {
    soundEffect = Mix_LoadWAV(filename.c_str());
    return soundEffect != nullptr;
}

void SoundPlayer::playSound() {
    if (soundEffect && soundEffectsEnabled) {
        Mix_PlayChannel(-1, soundEffect, 0);
    }
}

void SoundPlayer::setVolume(int volume) {
    if (soundEffect) {
        Mix_VolumeChunk(soundEffect, volume);
    }
    currentVolume = volume;
}

int SoundPlayer::getCurrentVolume() const {
    return currentVolume;
}

void SoundPlayer::enableSoundEffects() {
    soundEffectsEnabled = true;
}

void SoundPlayer::disableSoundEffects() {
    soundEffectsEnabled = false;
}
