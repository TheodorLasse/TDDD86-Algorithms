// Implementation of header file

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "random.h"
#include <string>

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = { // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
static const string BOARD_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

Set<string> Boggle::getPlayerWords() const {
    return this->playerWords;
}

Set<string> Boggle::getComputerWords() const {
    Set<string> newSet;

    for (string word : this->allWords) {
        if (!this->playerWords.contains(word)) {
            newSet.add(word);
        }
    }

    return newSet;
}

bool Boggle::guess(string& guess) {
    bool isCorrect = !this->playerWords.contains(guess) && guess.length() >= this->MIN_WORD_LENGTH && this->LEXICON.contains(guess) && this->searchBoard(guess);

    if (!isCorrect) {
        return false;
    }

    this->playerWords.add(guess);
    this->playerScore += guess.length() - this->MIN_WORD_LENGTH + 1;

    return isCorrect;
}

int Boggle::getPlayerScore() const {
    return this->playerScore;
}

int Boggle::getComputerScore() const {
    return this->computerScore - this->playerScore;
}

void Boggle::manualBoard() {
    cout << "Enter board characters: ";
    string answer;
    getline(cin, answer);
    answer = trim(toUpperCase(answer));

    if (answer.length() != NUM_CUBES) {
        manualBoard();
        return;
    }

    for(unsigned long int i = 0; i< answer.length(); i++) {
        string tempStr (1, answer[i]);
        if (tempStr.find_first_of(BOARD_CHARS) == -1) {
            manualBoard();
            return;
        }
    }

    for(long unsigned int i = 0; i < answer.length(); i++) {
        this->board.set(i / BOARD_SIZE, i % BOARD_SIZE, answer[i]);
    }
}

void Boggle::randomBoard() {
    int counter = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            char c = CUBES[counter][randomInteger(0, CUBES[counter].length() - 1)];
            this->board.set(i, j, c);
            counter++;
        }
    }
    shuffle(this->board);
}

void Boggle::createBoard(bool manual) {
    this->playerWords.clear();
    this->playerScore = 0;
    this->allWords.clear();
    this->computerScore = 0;

    this->board = Grid<char>(BOARD_SIZE, BOARD_SIZE);

    if (manual) {
        manualBoard();
    } else{
        randomBoard();
    }

    this->findAllWords();

    for (string word : this->allWords) {
        this->computerScore += word.length() - this->MIN_WORD_LENGTH + 1;
    }
}

Grid<char> Boggle::getBoard() const {
    return this->board;
}

bool Boggle::searchBoardRecursive(string& word, int row, int col) {
    if (word.length() == 0) {
        return true;
    }

    if (this->board.get(row, col) != word[0]) {
        return false;
    }

    // Choose
    char choosen = word[0];
    word.erase(0, 1);
    this->board.set(row, col, ' ');

    bool isValid = false;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            // If outside board
            if (i < 0 || j < 0 || i >= this->BOARD_SIZE || j >= this->BOARD_SIZE) {
                continue;
            }

            isValid = isValid || searchBoardRecursive(word, i, j);
        }
    }
    // Unchoose
    this->board.set(row, col, choosen);
    word.insert(0, 1, choosen);

    return isValid;
}

bool Boggle::searchBoard(string& word) {
    char first = word[0];
    bool isValid = false;

    for (int row = 0; row < this->board.numRows(); row++) {
        for (int col = 0; col < this->board.numCols(); col++) {
            if (this->board.get(row, col) == first && searchBoardRecursive(word, row, col)) {
                isValid = true;
            }
        }
    }

    return isValid;
}

void Boggle::findAllWordsRecursive(string& choosenWord, int row, int col) {
    char current = this->board.get(row, col);

    choosenWord += current;

    if (!this->LEXICON.containsPrefix(choosenWord)) {
        choosenWord.erase(choosenWord.length() - 1, 1);
        return;
    }

    if (this->LEXICON.contains(choosenWord) && !this->allWords.contains(choosenWord) && choosenWord.length() >= this->MIN_WORD_LENGTH) {
        this->allWords.add(choosenWord);
    }

    // Choose
    this->board.set(row, col, ' ');

    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            // If outside board
            if (i < 0 || j < 0 || i >= this->BOARD_SIZE || j >= this->BOARD_SIZE) {
                continue;
            }
            if (this->board.get(i, j) != ' ') {
                findAllWordsRecursive(choosenWord, i, j);
            }
        }
    }
    // Unchoose
    this->board.set(row, col, current);
    choosenWord.erase(choosenWord.length() - 1, 1);
}

void Boggle::findAllWords() {
    string emptyWord = "";
    for (int row = 0; row < this->board.numRows(); row++) {
        for (int col = 0; col < this->board.numCols(); col++) {
            findAllWordsRecursive(emptyWord, row, col);
        }
    }
}
