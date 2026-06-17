#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include <string>

using namespace std;

class Classifier
{
public:
    static constexpr int canonicalWidth = 5;
    static constexpr int canonicalHeight = 5;


    static vector<vector<int>> getTemplateX();

    static vector<vector<int>> getTemplateO();

    static vector<vector<int>> getTemplateT();

    static double distance(vector<int> v1, vector<int> v2);

    static vector<int> flatten(const vector<vector<int>>& grid);

    static string classify(const vector<vector<int>>& grid);

    static double confidence(const vector<vector<int>>& grid);
};

#endif
