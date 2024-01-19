// board.h

#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

struct LeaderboardEntry {
    std::string date;
    std::string time;
    std::string gameDuration;
    int score;

    LeaderboardEntry(std::string date, std::string time, std::string gameDuration, int score)
        : date(std::move(date)), time(std::move(time)), gameDuration(std::move(gameDuration)), score(score) {}

    bool operator<(const LeaderboardEntry& other) const {
        return score > other.score;
    }
};

inline std::vector<LeaderboardEntry> readLeaderboard() {
    std::vector<LeaderboardEntry> leaderboard;
    std::ifstream file("leaderboard.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date, time, duration, temp;
        int score;

        std::getline(iss, date, ' ');     // ������ ����
        std::getline(iss, time, ' ');     // ������ �����
        std::getline(iss, temp, ' ');     // ���������� Time: 
        std::getline(iss, duration, ' '); // ������ ����� ��������
        std::getline(iss, temp, ' ');     // ���������� Score:
        iss >> score;                     // ������ ����

        leaderboard.emplace_back(date, time, duration, score);
    }

    // ���������� � ���������� ������ ���� ������ �������
    std::sort(leaderboard.begin(), leaderboard.end());
    if (leaderboard.size() > 5) {
        leaderboard.erase(leaderboard.begin() + 5, leaderboard.end());
    }

    return leaderboard;
}
