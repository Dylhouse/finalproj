#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Classifier.h"

using namespace std;

bool running = true;

vector<vector<int>> getGridFromImage(string& path) {
    int width, height, channels;

    unsigned char* imageBin = stbi_load(
        path.c_str(),
        &width,
        &height,
        &channels,
        3
    );

    if (!imageBin) {
        return {{-1}};
    }

    vector<vector<int>> grid(height, vector<int>(width));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * 3;

            int r = imageBin[index];
            int g = imageBin[index + 1];
            int b = imageBin[index + 2];

            grid[y][x] = (r == 0 && g == 0 && b == 0) ? 1 : 0;
        }
    }

    stbi_image_free(imageBin);

    return grid;
}

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

vector<vector<int>> noiseRemove(const vector<vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) return {{0}};

    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<int>> noiseRemoved(rows, vector<int>(cols));

    // 8 directions (including diagonals)
    const int offsetsY[8] = {-1, -1, -1,  0, 0, 1, 1, 1};
    const int offsetsX[8] = {-1,  0,  1, -1, 1,-1, 0, 1};

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            bool isNoise = true;

            if (grid[y][x] == 0) {
                noiseRemoved[y][x] = 0;
                continue;
            }

            for (int direction = 0; direction < 8; direction++) {
                int offsetX = x + offsetsY[direction];
                int offsetY = y + offsetsX[direction];

                if (offsetX < 0 || offsetX >= rows ||
                    offsetY < 0 || offsetY >= cols)
                    continue;

                if (grid[offsetY][offsetX] == 1) {
                    isNoise = false;
                    break;
                }
            }

            if (isNoise) noiseRemoved[y][x] = 0;
            else noiseRemoved[y][x] = 1;
        }
    }

    return noiseRemoved;
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
        cout << "5: Classify from image" << endl;
        cout << "0: Exit" << endl;
        cout << "Choose: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                vector<vector<int>> grid = inputGrid();
                grid = noiseRemove(grid);
                grid = isolateTargetSymbol(grid);
                grid = resize(grid, Classifier::canonicalWidth, Classifier::canonicalHeight);

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

            case 5:
            {
                string filepath;
                cout << "Enter filepath of image: " << endl;
                cin >> filepath;

                vector<vector<int>> imgGrid = getGridFromImage(filepath);

                if (imgGrid[0][0] == -1) {
                    cout << "Image failed to load.";
                    break;
                }

                imgGrid = noiseRemove(imgGrid);
                imgGrid = isolateTargetSymbol(imgGrid);
                imgGrid = resize(imgGrid, Classifier::canonicalWidth, Classifier::canonicalHeight);

                runClassifier(imgGrid);
                break;
            }

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
