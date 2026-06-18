#include "Classifier.h"
#include <cmath>
#include <limits>
#include <algorithm>

vector<vector<int>> Classifier::getTemplateX()
{
    return
    {
        {1,0,0,0,0,0,0,1},
        {0,1,0,0,0,0,1,0},
        {0,0,1,0,0,1,0,0},
        {0,0,0,1,1,0,0,0},
        {0,0,0,1,1,0,0,0},
        {0,0,1,0,0,1,0,0},
        {0,1,0,0,0,0,1,0},
        {1,0,0,0,0,0,0,1}
    };
}

vector<vector<int>> Classifier::getTemplateO()
{
    return
    {
        {0,0,1,1,1,1,0,0},
        {0,1,0,0,0,0,1,0},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {0,1,0,0,0,0,1,0},
        {0,0,1,1,1,1,0,0}
    };
}

vector<vector<int>> Classifier::getTemplateT()
{
    return
    {
        {1,1,1,1,1,1,1,1},
        {0,0,0,1,1,0,0,0},
        {0,0,0,1,1,0,0,0},
        {0,0,0,1,1,0,0,0},
        {0,0,0,1,1,0,0,0},
        {0,0,0,1,1,0,0,0},
        {0,0,0,1,1,0,0,0},
        {0,0,0,1,1,0,0,0}
    };
}

vector<int> Classifier::flatten(const vector<vector<int>>& grid)
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

double Classifier::distance(vector<int> v1, vector<int> v2)
{
    double dist = 0;

    for(size_t i = 0; i < v1.size(); i++)
    {
        dist += pow(v1[i] - v2[i], 2);
    }

    return sqrt(dist);
}

string Classifier::classify(const vector<vector<int>>& grid)
{
    vector<int> input = flatten(grid);

    double xDist = distance(input, flatten(getTemplateX()));
    double oDist = distance(input, flatten(getTemplateO()));
    double tDist = distance(input, flatten(getTemplateT()));

    if (xDist <= oDist && xDist <= tDist)
    {
        return "X";
    }

    if (oDist <= xDist && oDist <= tDist)
    {
        return "O";
    }

    return "T";
}

double Classifier::confidence(const vector<vector<int>>& grid)
{
    vector<int> input = flatten(grid);

    double xDist = distance(input, flatten(getTemplateX()));
    double oDist = distance(input, flatten(getTemplateO()));
    double tDist = distance(input, flatten(getTemplateT()));

    double best = min(xDist, min(oDist, tDist));
    double worst = sqrt(canonicalWidth*canonicalHeight);

     double confidence =
        100.0 * (1.0 - best / worst);

    //double confidence = 100.0 / (1.0 + best);

    return confidence;
}
