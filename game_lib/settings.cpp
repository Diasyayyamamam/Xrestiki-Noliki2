#include "settings.h"
#include "board.h"
#include <fstream>

std::string player1, player2;

void saveSettings() {
    std::ofstream settings("settings.txt");
    settings << boardSize << std::endl << player1 << std::endl << player2 << std::endl;
    settings.close();
}

bool loadSettings() {
    std::ifstream settings("settings.txt");
    if (!settings) return false;
    settings >> boardSize;
    settings.ignore();
    std::getline(settings, player1);
    std::getline(settings, player2);
    return true;
}