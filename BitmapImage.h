//
// Created by carlo on 08/07/22.
//

#ifndef LUCCHESI_CARLO_ELABORATO_LABORATORIO_BITMAPIMAGE_H
#define LUCCHESI_CARLO_ELABORATO_LABORATORIO_BITMAPIMAGE_H

#include <stdexcept>
#include <cstring>

enum ImageType {
    Gray, GrayAlpha, RGB, RGBAlpha
};

class BitmapImage {
public:
    BitmapImage(int width, int height, ImageType type);

    BitmapImage(const BitmapImage &image) {
        copyImage(image);
    }

    BitmapImage &operator=(const BitmapImage &rhs) {
        if (this != &rhs) {
            delete[] buffer;
            copyImage(rhs);
        }
        return *this;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    int getChannels() const {
        return channels;
    }

    ImageType getType() const {
        return type;
    }

    //Due to the fact that this method could be called many times it's fair to define it inline.
    inline int getPixel(int row, int column, int channel) const;

    void setPixel(int row, int column, int channel, int value);

    bool operator==(const BitmapImage &rhs) const;

    ~BitmapImage() {
        delete[] buffer;
    }

private:
    int width;
    int height;
    int channels;
    ImageType type;
    int *buffer;
    //In the chunk of memory referred by buffer, the width * height adjacent are one channel.
    //For instance: an image 2 x 3 with 2 channels, the first 6 slot of memory encode the first channel.

    void copyImage(const BitmapImage &image);

    bool itsValidPosition(int row, int column, int channel) const;
};

//The definition should be here to avoid compiling errors.
inline int BitmapImage::getPixel(int row, int column, int channel) const {
    if (!itsValidPosition(row, column, channel)) {
        throw std::invalid_argument("Error: the given position to pick a pixel is wrong.");
    }

    return buffer[channel * width * height + row * width + column];
}

#endif //LUCCHESI_CARLO_ELABORATO_LABORATORIO_BITMAPIMAGE_H
