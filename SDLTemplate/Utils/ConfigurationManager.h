// ConfigurationManager.h
#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

class ConfigurationManager {
public:
    static ConfigurationManager& getInstance() {
        static ConfigurationManager instance;
        return instance;
    }

    int musicVolume;  // Music volume
    int soundVolume;  // Sound effects volume
    bool musicEnabled;  // Is music enabled?
    bool soundEnabled;  // Are sound effects enabled?

private:
    ConfigurationManager()
        : musicVolume(75), soundVolume(75), musicEnabled(true), soundEnabled(true) {} // Default values
};

#endif // CONFIGURATIONMANAGER_H
