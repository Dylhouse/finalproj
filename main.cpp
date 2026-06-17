#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "Classifier.h"

using namespace std;

bool running = true;

vector<vector<int>> inputGrid()
{
    int rows;
    int columns;

    cout << "Input number of rows:" << endl;
    cin >> rows;

    cout << "Input number of columns:" << endl;
    cin >> columns;

    vector<vector<int>> grid(rows, vector<int>(columns));

    cout << "Input grid (press enter after each row): " << endl;

    for(int row = 0; row < rows; row++)
    {
        string line;

        while(true)
        {
            cin >> line;

            if (line.length() != columns)
            {
                cout << "Row must contain exactly "
                     << columns << " digits.\n";
                continue;
            }

            bool valid = true;

            for (char chara : line)
            {
                if(chara != '0' && chara != '1')
                {
                    valid = false;
                    break;
                }
            }

            if (valid)
            {
                break;
            }

            cout << "Only 0 and 1 are allowed.\n";
        }

        for(int column = 0; column < columns; column++)
        {
            grid[row][column] = line[column] - '0';
        }
    }

    return grid;
}

// Uses nearest-neighbor to resize
vector<vector<int>> resize(const vector<vector<int>>& grid, int targetWidth, int targetHeight) {
    int originalHeight = grid.size();
    int originalWidth = grid[0].size();

    vector<vector<int>> resized(targetHeight, vector<int>(targetWidth));

    for (int y = 0; y < targetHeight; y++)
    {
        for (int x = 0; x < targetWidth; x++)
        {
            int srcY = (double)y * (double)originalHeight / (double)targetHeight;
            int srcX = (double)x * (double)originalWidth / (double)targetWidth;

            resized[y][x] = grid[srcY][srcX];
        }
    }

    return resized;
}

vector<vector<int>> isolateTargetSymbol(const vector<vector<int>>& grid) {
    int minX = INT_MAX;
    int maxX = -1;
    int minY = INT_MAX;
    int maxY = -1;

    for(int y = 0; y < grid.size(); y++) 
    {
        const auto& row = grid[y];
        for (int x = 0; x < row.size(); x++) 
        {
            if (row[x] != 1) 
            {
                continue;
            }

            if (x < minX) minX = x;
            if (x > maxX) maxX = x;
            if (y < minY) minY = y;
            if (y > maxY) maxY =y;
        }
    }

    // Check if grid is empty
    if (maxX == -1) {
        return {{0}};
    }

    vector<vector<int>> isolated;

    // Copy the non-whitespace parts pack into a new grid
    for (int y = minY; y <= maxY; y++)
    {
        vector<int> row;

        for (int x = minX; x <= maxX; x++)
        {
            row.push_back(grid[y][x]);
        }

        isolated.push_back(row);
    }

    return isolated;
}

void printGrid(const vector<vector<int>>& grid)
{
    for(const auto& row : grid)
    {
        for(int pixel : row)
        {
            cout << pixel;
        }
        cout << endl;
    }
}

void runClassifier(const vector<vector<int>>& grid)
{
    cout << endl;
    cout << "Input Pattern:" << endl;
    printGrid(grid);

    cout << endl;
    cout << "Detected Pattern: " << Classifier::classify(grid) << endl;
    cout << "Confidence: " << Classifier::confidence(grid) << "%" << endl;
}

int main()
{
    while (running)
    {
        cout << endl;
        cout << "Pixel Pattern Classifier" << endl;
        cout << "1: Classify custom pattern" << endl;
        cout << "2: Test X template" << endl;
        cout << "3: Test O template" << endl;
        cout << "4: Test T template" << endl;
        cout << "0: Exit" << endl;
        cout << "Choose: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                vector<vector<int>> grid = resize(isolateTargetSymbol(inputGrid()), Classifier::canonicalWidth, Classifier::canonicalHeight);

                runClassifier(grid);
                break;
            }

            case 2:
                runClassifier(Classifier::getTemplateX());
                break;

            case 3:
                runClassifier(Classifier::getTemplateO());
                break;

            case 4:
                runClassifier(Classifier::getTemplateT());
                break;

            case 0:
                running = false;
                cout << "Program ended." << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
