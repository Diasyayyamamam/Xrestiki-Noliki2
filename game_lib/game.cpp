#include "game.h"
#include "board.h"
#include "settings.h"
#include "history.h"

#include <iostream>
#include <limits>

using namespace std;

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const int WIN_CONDITION = 3;

bool checkWinner(char player) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j <= boardSize - WIN_CONDITION; j++) {
            bool rowWin = true, colWin = true;
            for (int k = 0; k < WIN_CONDITION; k++) {
                if (board[i][j + k] != player) rowWin = false;
                if (board[j + k][i] != player) colWin = false;
            }
            if (rowWin || colWin) return true;
        }
    }

    for (int i = 0; i <= boardSize - WIN_CONDITION; i++) {
        for (int j = 0; j <= boardSize - WIN_CONDITION; j++) {
            bool diag1 = true, diag2 = true;
            for (int k = 0; k < WIN_CONDITION; k++) {
                if (board[i + k][j + k] != player) diag1 = false;
                if (board[i + k][j + WIN_CONDITION - k - 1] != player) diag2 = false;
            }
            if (diag1 || diag2) return true;
        }
    }

    return false;
}

bool isDraw() {
    for (const auto& row : board)
        for (char cell : row)
            if (cell == EMPTY) return false;
    return true;
}

void startGame() {
    board.assign(boardSize, vector<char>(boardSize, EMPTY));

    cout << "Who will start first? (1 - " << player1 << ", 2 - " << player2 << "): ";
    int first;
    cin >> first;
    cin.ignore();

    char currentPlayer = (first == 1) ? PLAYER_X : PLAYER_O;
    string currentName = (first == 1) ? player1 : player2;

    while (true) {
        clearScreen();
        showBoard();
        cout << currentName << " (" << currentPlayer << "), enter row and column (1-" << boardSize << "): ";
        int row, col;
        cin >> row >> col;

        if (row < 1 || row > boardSize || col < 1 || col > boardSize|| board[row - 1][col - 1] != EMPTY) {
            cout << "Invalid move! Try again.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        board[row - 1][col - 1] = currentPlayer;

        if (checkWinner(currentPlayer)) {
            clearScreen();
            showBoard();
            cout << "Player " << currentName << " (" << currentPlayer << ") wins!\n";
            saveHistory(currentName);
            break;
        }

        if (isDraw()) {
            clearScreen();
            showBoard();
            cout << "It's a draw!\n";
            saveHistory("Draw");
            break;
        }

        currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
        currentName = (currentName == player1) ? player2 : player1;
    }

    cout << "\n1. Restart game\n2. Return to main menu\nChoose an option: ";
    int choice;
    cin >> choice;
    if (choice == 1) startGame();
}

void showMenu() {
    while (true) {
        clearScreen();
        cout << "Main Menu:\n";
        cout << "1. Start Game\n";
        cout << "2. Settings\n";
        cout << "3. Game History\n";
        cout << "4. Exit\n";
        cout << "Select menu item: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            if (!loadSettings()) {
                cout << "No settings found! Set player names first.\nPress Enter to return to the menu...";
                cin.ignore();
                cin.get();
                continue;
            }
            startGame();
        } else if (choice == 2) {
            cout << "Enter board size (min 3): ";
            cin >> boardSize;
            if (boardSize < 3) boardSize = 3;
            cin.ignore();

            cout << "Enter first player's name: ";
            getline(cin, player1);
            cout << "Enter second player's name: ";
            getline(cin, player2);

            saveSettings();
            cout << "Settings saved! Press Enter to return to menu...";
            cin.ignore();
            cin.get();
        } else if (choice == 3) {
            showHistory();
} else if (choice == 4) {
            cout << "Thanks for playing! Goodbye.\n";
            break;
        } else {
            cout << "Invalid choice. Press Enter to try again...";
            cin.ignore();
            cin.get();
        }
    }
}