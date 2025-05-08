#include "board.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int boardSize = 3;
vector<vector<char>> board;

void clearScreen() {
    system("cls");
}

void showBoard() {
    cout << "  ";
    for (int i = 1; i <= boardSize; i++) cout << i << "   ";
    cout << endl;

    for (int i = 0; i < boardSize; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < boardSize; j++) {
            cout << board[i][j];
            if (j < boardSize - 1) cout << " | ";
        }
        cout << "\n";
        if (i < boardSize - 1) {
            cout << "  ";
            for (int j = 0; j < boardSize; j++) cout << "--- ";
            cout << "\n";
        }
    }
    cout << endl;
}