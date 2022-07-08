//
// Created by carlo on 08/07/22.
//

#include <stdexcept>
#include "KernelProcessing.h"

KernelProcessing::KernelProcessing(KernelDimension type) {
    if (type == Three) {
        dimension = 3;
    } else {
        dimension = 5;
    }
    int totalNumbers = dimension * dimension;
    mask = new float[totalNumbers];
    for (int i = 0; i < totalNumbers; i++) {
        mask[i] = 0;
    }
    mask[dimension / 2 * dimension + dimension / 2] = 0;
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
}

int KernelProcessing::calculateValue(const BitmapImage &image, int row, int column, int channel) const {
    float result = 0;
    int offset = 1;
    if (dimension == 5) {
        offset = 2;
    }

    for (int i = row - offset; i <= row + offset; i++) {
        for (int j = column - offset; j <= column + offset; j++) {
            //I suppose to use the extend Hedge technique to handle external pixels
            //Reference: https://en.wikipedia.org/wiki/Kernel_(image_processing)#Edge_Handling
            extendHedge(image, i, j);
        }
    }
    result =
}


void KernelProcessing::extendHedge(const BitmapImage &image, int &row, int &column) const {
    if (row < 0) {
        row = 0;
    } else if (row > image.getHeight()) {
        row = image.getHeight();
    }
    if (column < 0) {
        column = 0;
    } else if (column > image.getWidth()) {
        column = image.getWidth();
    }
}