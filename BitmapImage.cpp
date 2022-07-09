//
// Created by carlo on 08/07/22.
//

#include "BitmapImage.h"

BitmapImage::BitmapImage(int width, int height, ImageType type) : width(width), height(height), type(type) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Error: you can't define a image with negative dimensions");
    }
    switch (type) {
        case Gray:
            channels = 1;
            break;
        case GrayAlpha:
            channels = 2;
            break;
        case RGB:
            channels = 3;
            break;
        case RGBAlpha:
            channels = 4;
            break;
    }
    buffer = new int[width * height * channels];
}

bool BitmapImage::operator==(const BitmapImage &rhs) const {
    if (this == &rhs) {
        return true;
    }
    if (width == rhs.width && height == rhs.height && channels == rhs.channels && type == rhs.type) {
        //Since memcmp returns 0 if the 2 chunks are equal there is ! on top
        if (!std::memcmp(buffer, rhs.buffer, width * height * channels)) {
            return true;
        }
    }
    return false;
}

void BitmapImage::setPixel(int row, int column, int channel, int value) {
    if (!itsValidPosition(row, column, channel)) {
        throw std::invalid_argument("Error: the given position to pick a pixel is wrong.");
    }
    row--;
    column--;
    channel--;
    //Decrementing row, column and channel is necessary due to the (1,1) pixel of the channel 1 is the top left pixel
    // of the first channel
    if (value < 0) {
        value = 0;
    } else if (value > 255) {
        value = 255;
    }

    buffer[channel * width * height + row * width + column] = value;
}

void BitmapImage::copyImage(const BitmapImage &image) {
    width = image.width;
    height = image.height;
    type = image.type;
    channels = image.channels;
    buffer = new int[width * height * channels];
    std::memcpy(buffer, image.buffer, width * height * channels);
}

bool BitmapImage::itsValidPosition(int row, int column, int channel) const {
    if (row <= 0 || row > height || column <= 0 || column > width || channel <= 0 || channel > channels) {
        return false;
    }
    return true;
}