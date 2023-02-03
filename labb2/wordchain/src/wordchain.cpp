#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

/**
 * Searches the set of previously used words to ensure it's not a duplicate and checks whether the word
 * is an actual word in the english dictionary. If both are true, it's an eligible word.
 */
bool eligibleWord(const unordered_set<string> &usedWords, const unordered_set<string> &dictionary, const string &newWord){
    return usedWords.find(newWord) == usedWords.end() && dictionary.find(newWord) != dictionary.end();
}

/**
 * Prints the word chain of the transition from one word (w1) to another (w2)
 */
void wordChain(const string &w1, const string &w2, const unordered_set<string> &dictionary)
{
    unordered_set<string> usedWords;
    queue<stack<string>> wChain;

    //use w1 as a "seed" for the function
    stack<string> w1Stack;
    w1Stack.push(w1);
    wChain.push(w1Stack);

    while (!wChain.empty())
    {
        stack<string> partialChain = wChain.front();
        wChain.pop();
        if (partialChain.top() == w2)
        {
            while (!partialChain.empty())
            {
                cout << partialChain.top() << endl;
                partialChain.pop();
            }
        }

        else
        {
            string partialChainTop = partialChain.top();
            for (int i = 0; i < partialChainTop.size(); i++)
            {
                for (int j = 0; j < ALPHABET.size(); j++)
                {
                    string newWord = partialChainTop;
                    newWord[i] = ALPHABET[j];

                    if (eligibleWord(usedWords, dictionary, newWord))
                    {
                        usedWords.insert(newWord);

                        stack<string> newPartialChain = partialChain;
                        newPartialChain.push(newWord);
                        wChain.push(newPartialChain);
                    }
                }
            }
        }
    }
}

/**
 * Reads the dictionary and adds the words to an unordered_set.
 */
void readDictionary(unordered_set<string> &dictionary)
{
    const string path = "res/dictionary.txt";
    ifstream file;
    file.open(path);

    string line;

    while (getline(file, line))
    {
        dictionary.insert(line);
    }
}

int main()
{
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";

    string startWord;
    string endWord;
    cin >> startWord;
    cin >> endWord;

    unordered_set<string> dict;
    readDictionary(dict);

    wordChain(startWord, endWord, dict);

    return 0;
}

