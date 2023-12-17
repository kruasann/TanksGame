// ������ �� ������������� ��������� ������������� �����
#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

// ���������� ������ ConfigurationManager
class ConfigurationManager {
public:
    // ����������� ����� ��� ��������� ���������� ������ (Singleton pattern)
    static ConfigurationManager& getInstance() {
        static ConfigurationManager instance; // ����������� ��������� ������
        return instance;
    }

    // ���������� ��� �������� �������� �����
    int musicVolume;  // ��������� ������
    int soundVolume;  // ��������� �������� ��������
    bool musicEnabled;  // ���� ��������� ������
    bool soundEnabled;  // ���� ��������� �������� ��������

private:
    // ��������� ����������� (����� Singleton pattern)
    ConfigurationManager()
        : musicVolume(75), soundVolume(75), musicEnabled(true), soundEnabled(true) {} // ��������� �������� �� ���������

};

// ����� ������ �� ������������� ���������
#endif // CONFIGURATIONMANAGER_H
