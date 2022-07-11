//
// Created by carlo on 08/07/22.
//

#include <cstring>
#include <stdexcept>
#include <algorithm>
#include "KernelProcessing.h"

KernelProcessing::KernelProcessing(KernelDimension type) {
    if (type == Three) {
        dimension = 3;
    } else {
        dimension = 5;
    }
    int totalNumbers = dimension * dimension;
    mask = new float[totalNumbers];

    std::fill(mask, mask + totalNumbers, 0);
    mask[dimension / 2 * dimension + dimension / 2] = 1;
}

KernelProcessing &KernelProcessing::operator=(const KernelProcessing &rhs) {
    if (this != &rhs) {
        delete[] mask;
        copyValues(rhs);
    }
    return *this;
}

bool KernelProcessing::operator==(const KernelProcessing &rhs) const {
    if (this == &rhs) {
        return true;
    }
    if (dimension == rhs.dimension) {
        //Since memcmp returns 0 if the 2 chunks are equal there is ! on top
        if (!std::memcmp(mask, rhs.mask, dimension * dimension)) {
            return true;
        }
    }
    return false;
}

BitmapImage KernelProcessing::processImage(const BitmapImage &image) const {
    int width = image.getWidth();
    int height = image.getHeight();
    ImageType type = image.getType();

    BitmapImage result(width, height, type);
    int channels = result.getChannels();

    for (int c = 1; c <= channels; c++) {
        for (int i = 1; i <= height; i++) {
            for (int j = 1; j <= width; j++) {
                result.setPixel(i, j, c, calculateValue(image, i, j, c));
            }
        }
    }
    return result;
}

void KernelProcessing::setMaskElement(int row, int column, float value) {
    if (!itsValidPosition(row, column)) {
        throw std::invalid_argument("Error: given position is not valid.");
    }

    //The intent is to consider in the external interface that the top left element is in the row and column 1.
    row--;
    column--;
    mask[row * dimension + column] = value;
}

int KernelProcessing::getMaskElement(int row, int column) const {
    if (!itsValidPosition(row, column)) {
        throw std::invalid_argument("Error: given position is not valid.");
    }

    //The intent is to consider in the external interface that the top left element is in the row and column 1.
    row--;
    column--;
    return mask[row * dimension + column];
}

void KernelProcessing::copyValues(const KernelProcessing &kernel) {
    dimension = kernel.dimension;
    mask = new float[dimension * dimension];
    std::memcpy(mask, kernel.mask, dimension * dimension);
}

int KernelProcessing::calculateValue(const BitmapImage &image, int row, int column, int channel) const {
    float result = 0;
    int offset = 1;
    if (dimension == 5) {
        offset = 2;
    }

    for (int i = row - offset; i <= row + offset; i++) {
        for (int j = column - offset; j <= column + offset; j++) {
            //XXX According to the Wikipedia page the element of the mask is the opposite position to the relative pixel
            //in the image.
            int imageRow = i;
            int imageColumn = j;
            int maskRow = row + offset * 2 - i - 1;
            int maskColumn = column + offset * 2 - j - 1;
            //he minus 1 are essential due to the fact that externally the first element is at index (1,1)

            //I suppose to use the Extend Hedge technique to handle external pixels
            //Reference: https://en.wikipedia.org/wiki/Kernel_(image_processing)#Edge_Handling
            extendHedge(image, imageRow, imageColumn);

            result += image.getPixel(imageRow, imageColumn, channel) * mask[maskRow * dimension + maskColumn];
            //FIXME Maybe it's possible to do with arrays. Valuate to introduce into the BitmapImage the possibility to
            // get a given square of the image linearized into an array.
        }
    }
    return static_cast<int> (result);
}


void KernelProcessing::extendHedge(const BitmapImage &image, int &row, int &column) const {
    if (row < 1) {
        row = 1;
    } else if (row > image.getHeight()) {
        row = image.getHeight();
    }
    if (column < 1) {
        column = 1;
    } else if (column > image.getWidth()) {
        column = image.getWidth();
    }
}


bool KernelProcessing::itsValidPosition(int row, int column) const {
    if (row < 1 || row > dimension || column < 1 || column > dimension) {
        return false;
    }
    return true;
}
