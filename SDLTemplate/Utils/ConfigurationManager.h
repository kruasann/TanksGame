// Защита от многократного включения заголовочного файла
#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

// Объявление класса ConfigurationManager
class ConfigurationManager {
public:
    // Статический метод для получения экземпляра класса (Singleton pattern)
    static ConfigurationManager& getInstance() {
        static ConfigurationManager instance; // Статический экземпляр класса
        return instance;
    }

    // Переменные для хранения настроек звука
    int musicVolume;  // Громкость музыки
    int soundVolume;  // Громкость звуковых эффектов
    bool musicEnabled;  // Флаг включения музыки
    bool soundEnabled;  // Флаг включения звуковых эффектов

private:
    // Приватный конструктор (часть Singleton pattern)
    ConfigurationManager()
        : musicVolume(75), soundVolume(75), musicEnabled(true), soundEnabled(true) {} // Установка значений по умолчанию

};

// Конец защиты от многократного включения
#endif // CONFIGURATIONMANAGER_H
