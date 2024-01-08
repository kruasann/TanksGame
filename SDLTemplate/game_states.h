// game_states.h
#ifndef GAME_STATES_H
#define GAME_STATES_H

// ����������� ������������ GameState, ��������������� ��������� ��������� ����.
enum class GameState {
    MainMenu, // ��������� �������� ����
    Settings, // ��������� ��������
    Pause,    // ��������� �����
    Level1,   // ��������� ������� ������
    Level2,   // ��������� ������� ������
    Level3,   // ��������� �������� ������
    Death,    // ��������� ��������� (������ ������)
    Win,      // ��������� ������
    Defeat,   // ��������� ���������
    Exit      // ��������� ������ �� ����
};

#endif // GAME_STATES_H