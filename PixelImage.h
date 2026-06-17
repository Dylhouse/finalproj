#ifndef PIXELIMAGE_H
#define PIXELIMAGE_H

#include <vector>

using namespace std;

class PixelImage
{
public:
    vector<vector<int>> pixels;

    int rows;
    int cols;

    PixelImage();

    PixelImage(vector<vector<int>> data);
};

#endif
