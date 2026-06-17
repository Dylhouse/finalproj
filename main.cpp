#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool running = true;

vector<int> flatten(const vector<vector<int>>& grid)
{
    vector<int> result;

    for(const auto& row : grid)
    {
        for(int pixel : row)
        {
            result.push_back(pixel);
        }
    }

    return result;
}

double distance(vector<int> v1, vector<int> v2) {
    double dist = 0;

    for(size_t i = 0; i < v1.size(); i++)
    {
        dist += pow(v1[i] - v2[i], 2);
    }

    dist = sqrt(dist);

    return dist;
}

vector<vector<int>> inputGrid() {
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
            // subtract ascii value to get actual num value
            grid[row][column] = (int)line[column] - (int)'0';
        }
    }

    return grid;
}

int main() {
    while (running) {
        cout << "1: placeholder" << endl;
        cout << "2: placeholder" << endl;

        int choice;
        cin >> choice;

        switch (choice) 
        {
            case 1:
                cout << "dist: " << distance(flatten(inputGrid()), flatten(inputGrid())) << endl;
            case 2:
                break;

            default:
                cout << "invalid";
        }
    }

    return 0;
}