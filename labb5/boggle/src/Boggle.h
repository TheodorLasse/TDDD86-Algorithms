// Header file of the boggle game logic.

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "grid.h"
#include "lexicon.h"
#include "set.h"

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    const Lexicon LEXICON = Lexicon(DICTIONARY_FILE);

    // Creates a new board.
    void createBoard(bool manual);

    // Searches the board for a given word.
    bool searchBoard(string& word);

    // Returns the grid
    Grid<char> getBoard() const;

    // Returns the words that the player has guessed.
    Set<string> getPlayerWords() const;

    // Returns the words that the computer has guessed.
    Set<string> getComputerWords() const;

    // Make a guess. Returns true if correct.
    bool guess(string& word);

    // Returns the players score.
    int getPlayerScore() const;

    // Returns the computers score.
    int getComputerScore() const;

private:
    // Lets the user create a board.
    void manualBoard();

    // Creates a random board.
    void randomBoard();

    // Recursive function that searches the board for a given word. Used by searchBaord.
    bool searchBoardRecursive(string& word, int row, int col);

    // Finds all the words on the board.
    void findAllWords();

    // Recursive function that finds all the words on the board. Used by findAllWords.
    void findAllWordsRecursive(string& choosenWord, int row, int col);

    int playerScore = 0;
    int computerScore = 0;
    Set<string> playerWords;
    Set<string> allWords;
    Grid<char> board;
};

#endif
