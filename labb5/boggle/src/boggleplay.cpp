#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include "set.h"
#include <algorithm>

void showBoard(Boggle& boggle) {
    auto board = boggle.getBoard();
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            cout << board.get(i, j);
        }
        cout << endl;
    }
}

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    bool isManual = yesOrNo("Manual entry? (y/n) ");
    boggle.createBoard(isManual);

    bool isGuessing = true;

    clearConsole();

    while(isGuessing) {
        showBoard(boggle);

        cout << endl;
        cout << "Your words: " << boggle.getPlayerWords() << endl;
        cout << "Your score: " << boggle.getPlayerScore() << endl;

        cout << "Type a word (or press Enter to end your turn): ";
        string guess;
        getline(cin, guess);
        guess = trim(toUpperCase(guess));

        clearConsole();

        if (guess == "") {
            isGuessing = false;
        }
        else {
            if (boggle.guess(guess)) {
                cout << "You found a new word! " << guess << endl;
            } else {
                cout << "Bad guess!" << endl;
            }
        }
    }

    showBoard(boggle);

    Set<string> playerWords = boggle.getPlayerWords();
    Set<string> computerWords = boggle.getComputerWords();

    cout << endl;
    cout << "Your words: (" << playerWords.size() << "): " << playerWords << endl;
    cout << "Your score: " << boggle.getPlayerScore() << endl;
    cout << endl;
    cout << "It's my turn!" << endl;
    cout << "My words (" << computerWords.size() << "): " << computerWords << endl;
    cout << "My score: " << boggle.getComputerScore() << endl;

    if (boggle.getComputerScore() > boggle.getPlayerScore()) {
        cout << "I WON!" << endl;
    } else {
        cout << "YOU WON :(" << endl;
    }
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
