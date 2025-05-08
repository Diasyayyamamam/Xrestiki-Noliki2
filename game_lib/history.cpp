#include "history.h"
#include "board.h"
#include "settings.h"
#include <fstream>
#include <iostream>
#include <conio.h>

void saveHistory(std::string winner) {
    std::ofstream history("history.txt", std::ios::app);
    history << player1 << " vs " << player2 << " | Size: " << boardSize << " | Winner: " << winner << std::endl;
    for (const auto& row : board) {
        for (char cell : row) {
            history << cell;
        }
        history << std::endl;
    }
    history << "---" << std::endl;
    history.close();
}

void showHistory() {
    std::ifstream history("history.txt");
    if (!history) {
        std::cout << "No game history found.\n";
        return;
    }

    std::string line;
    while (std::getline(history, line)) {
        if (line == "---") {
            std::cout << std::endl;
            continue;
        }
        std::cout << line << std::endl;
    }
    history.close();

    std::cout << "\nPress any key to return to the menu...";
    _getch();
}