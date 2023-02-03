#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

/**
 * Reads the dictionary and adds the words to a container.
 */
void readDictionary(set<string> &dictionary)
{
    const string path = "res/dictionary.txt";
    //const string path = "res/di.txt";
    ifstream file;
    file.open(path);

    string line;

    while (getline(file, line))
    {
        dictionary.insert(line);
    }
}

/**
 * Adds all words with a specified length from one set to another.
 */
void filterDictionary(int length, const set<string> &dictionary, set<string> &filtered)
{
    for (auto word : dictionary)
    {
        if (word.length() == length)
        {
            filtered.insert(word);
        }
    }
}

/**
 * Prompts the user to choose a word length.
 */
int promptWordLength(const set<string> &dictionary, set<string> &filteredDict)
{
    while (true)
    {
        cout << "Word length: ";
        string input;
        cin >> input;
        int intInput = stoi(input);
        filterDictionary(intInput, dictionary, filteredDict);

        if (filteredDict.size() > 0)
            return intInput;
    }
}

/**
 * Prompts the user to choose their number of guesses.
 */
int promptGuesses()
{
    while (true)
    {
        cout << "Amount of guesses: ";
        string input;
        cin >> input;
        int intInput = stoi(input);

        if (intInput > 0)
        {
            return intInput;
        }
    }
}

/**
 * Prompts the user to choose if they want to see the possible words to guess on.
 */
bool promptSeeRest()
{
    while (true)
    {
        cout << "Do you want to see remaining words? (y) / (n): ";
        string input;
        cin >> input;
        if (input == "y" || input == "yes")
        {
            return true;
        }
        else if (input == "n" || input == "no")
        {
            return false;
        }
    }
}

/**
 * Prompts the user to guess on a character. Adds the guessed character to "guessed".
 */
char promptGuessChar(string &guessed)
{
    while (true)
    {
        cout << "Guess a new character in the word: ";
        string inputStr;
        cin >> inputStr;
        char input = inputStr[0];

        if (guessed.find(input) == string::npos && ALPHABET.find(input) != string::npos)
        {
            guessed.push_back(input);
            return input;
        }
    }
}

/**
 * Loops through a dictionary of words and creates partitions of 
 * possible words and adds them to their corresponding partition.
 */
void createPartitions(const set<string> &filteredDict, map<string, set<string>> &partitions, const string &prevGuesses)
{
    partitions.clear();
    for (auto word : filteredDict)
    {
        string partitionKey = word;
        for (int i = 0; i < word.size(); i++)
        {
            if (prevGuesses.find(word[i]) == string::npos)
            {
                partitionKey[i] = '-';
            }
        }

        partitions[partitionKey].insert(word);
    }
}

/**
 * Updates the partitions and currentString according to which partition was largest.
 * Retruns true if the latest guess was correct.
 */
bool processGuess(string &currentString, const string &prevGuesses, const set<string> &filteredDict, map<string, set<string>> &partitions)
{
    // Loop through words in dict. Add them to set in map.
    createPartitions(filteredDict, partitions, prevGuesses);

    // Find largest amount of future words from map
    int largest = 0;
    string largestKey = currentString;
    for (auto pair : partitions)
    {
        int length = pair.second.size();
        if (length > largest)
        {
            largest = length;
            largestKey = pair.first;
        }
    }

    bool correctGuess = largestKey != currentString;

    currentString = largestKey;

    return correctGuess;
}

/**
 * Runs the game.
 */
void hangman(const set<string> &dictionary)
{
    set<string> filteredDict;
    string guessed;

    int length = promptWordLength(dictionary, filteredDict);
    string currentString = string(length, '-');

    int remainingGuesses = promptGuesses();
    bool showRest = promptSeeRest();

    while (remainingGuesses > 0)
    {
        if (currentString.find('-') == string::npos)
        {
            cout << currentString << endl
                 << "YOU WON!" << endl;
            hangman(dictionary);
        }

        cout << "Remaining guesses: " << remainingGuesses << endl;
        cout << "Previously guessed: " << guessed << endl;
        cout << "Word: " << currentString << endl;
        char currentGuess = promptGuessChar(guessed);

        map<string, set<string>> partitions;
        bool correctGuess = processGuess(currentString, guessed, filteredDict, partitions);

        if (!correctGuess)
            remainingGuesses--;

        filteredDict = partitions[currentString];

        if (showRest)
        {
            for (auto word : filteredDict)
            {
                cout << word << ", ";
            }
            cout << endl
                 << endl;
        }
    }

    cout << endl
         << "YOU LOSE!" << endl
         << "the correct word was: " << *filteredDict.begin() << endl;
    hangman(dictionary);
}

int main()
{
    cout << "Welcome to Hangman." << endl;

    set<string> dictionary;
    readDictionary(dictionary);

    hangman(dictionary);

    return 0;
}
