#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include "lifeutil.cpp"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

/**
 * Creates a new grid.
 */
void createGrid(const vector<string> &lines, Grid<bool> &myGrid)
{
    int width = stoi(lines[1]);
    int height = stoi(lines[0]);
    myGrid.resize(height, width);

    int offset = 2;

    for (int loopHeight = offset; loopHeight < lines.size(); loopHeight++)
    {
        string line = lines[loopHeight];

        if (!(line[0] == 'X' || line[0] == '-'))
        {
            continue;
        }

        for (int loopWidth = 0; loopWidth < lines[2].size(); loopWidth++)
        {
            if (lines[loopHeight][loopWidth] == 'X')
            {
                myGrid[loopHeight - offset][loopWidth] = true;
            }
            else
            {
                myGrid[loopHeight - offset][loopWidth] = false;
            }
        }
    }
}

/**
 * Promts the user for a file name and returns the realative path.
 */
string getFilePath()
{
    cout << "Enter file name: ";
    string input;
    cin >> input;
    return "res/" + input + ".txt";
}

/**
 * Reads a file and fills a vector with the lines.
 */
void readFile(const string &path, vector<string> &lines)
{
    ifstream ifs(path, ifstream::in);
    for (std::string line; getline(ifs, line);)
    {
        lines.push_back(line);
    }
    ifs.close();
}

/**
 * Prints a given grid to the console.
 */
void showGrid(const Grid<bool> &grid)
{
    int width = grid.numCols();
    int height = grid.numRows();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            char c = grid[i][j] ? '#' : '-';
            cout << c;
        }
        cout << endl;
    }
}

/**
 * Counts all neighbours around a given coordinate.
 */
int countNeighbours(const Grid<bool> &grid, int width, int height)
{
    int neighbours = 0;

    // Loop through surrounding tiles.
    for (int x = width - 1; x <= width + 1; x++)
    {
        for (int y = height - 1; y <= height + 1; y++)
        {
            // Skip if outside grid
            if (x < 0 || x >= grid.numCols() || y < 0 || y >= grid.numRows() || (x == width && y == height))
            {
                continue;
            }

            if (grid[y][x])
            {
                neighbours++;
            }
        }
    }

    return neighbours;
}

/**
 * Advances the simulation one step, and swaps current and next grid.
 */
void progressGrid(Grid<bool> &currentGrid, Grid<bool> &nextGenGrid)
{
    int width = currentGrid.numCols();
    int height = currentGrid.numRows();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int neighbourCount = countNeighbours(currentGrid, j, i);

            if (neighbourCount <= 1)
            {
                nextGenGrid.set(i, j, false);
            }
            else if (neighbourCount == 3)
            {
                nextGenGrid.set(i, j, true);
            }
            else if (neighbourCount >= 4)
            {
                nextGenGrid.set(i, j, false);
            }
        }
    }

    // Swap current and next grid
    auto &temp = currentGrid;
    currentGrid = nextGenGrid;
    nextGenGrid = temp;
}

/**
 * Updates the grid and draws it in the terminal.
 */
void stepSimulation(Grid<bool> &grid, Grid<bool> &gridNextGen)
{
    progressGrid(grid, gridNextGen);
    clearConsole();
    showGrid(grid);
}

int main()
{
    // Init
    auto lines = vector<string>();
    readFile(getFilePath(), lines);

    auto grid = Grid<bool>();
    createGrid(lines, grid);

    auto gridNextGen = grid;

    clearConsole();
    showGrid(grid);

    // Run simulation
    while (true)
    {
        cout << "Animate: (a), Tick: (t), Quit: (q)" << endl;
        string input;
        cin >> input;

        // Animate
        if (input == "a")
        {
            for (int i = 0; i < 50; i++)
            {
                stepSimulation(grid, gridNextGen);
                pause(100);
            }
        }
        // Quit
        else if (input == "q")
        {
            break;
        }
        // Tick
        else if (input == "t")
        {
            stepSimulation(grid, gridNextGen);
        }
    }

    return 0;
}