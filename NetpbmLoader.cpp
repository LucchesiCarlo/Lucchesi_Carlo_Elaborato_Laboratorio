//
// Created by carlo on 11/07/22.
//
#include <cstring>
#include <memory>
#include "NetpbmLoader.h"

BitmapImage NetpbmLoader::loadImage(const std::string &url) {
    std::ifstream readType(url);
    if (readType.is_open()) {
        //It's actually called Magic Number in the wikipedia page https://en.wikipedia.org/wiki/Netpbm#Description
        std::string magicNumber;
        readType >> magicNumber;
        readType.close();

        std::ifstream imageFile;
        //The Morgan's Law : not a or not b = not (a and b)
        if (!(magicNumber.compare("P5") && magicNumber.compare("P6"))) {
            currentIsPlain = false;
            imageFile = std::ifstream(url, std::ifstream::binary);
        } else {
            currentIsPlain = true;
            imageFile = std::ifstream(url);
        }
        imageFile.ignore(3);
        if (!(magicNumber.compare("P2") && magicNumber.compare("P5"))) {
            currentChannels = 1;
            return generatePGM(imageFile);
        } else if (!(magicNumber.compare("P3") && magicNumber.compare("P6"))) {
            currentChannels = 3;
            return generatePPM(imageFile);
        } else if (!magicNumber.compare("P7")) {
            return generatePAM(imageFile);
        } else {
            throw std::invalid_argument("Error: the file has an unknown format.");
        }
    } else {
        throw std::invalid_argument("Error: it's impossible to open the file given as the url.");
    }
}

BitmapImage NetpbmLoader::generatePGM(std::ifstream &file) {
    readMetaDataOld(file);
    BitmapImage image(currentWidth, currentHeight, Gray);
    if (currentIsPlain) {
        readPlainPixelsOld(image, file);
    } else {
        readNotPlainPixelsOld(image, file);
    }
    file.close();
    return image;
}

BitmapImage NetpbmLoader::generatePPM(std::ifstream &file) {
    readMetaDataOld(file);
    BitmapImage image(currentWidth, currentHeight, RGB);
    if (currentIsPlain) {
        readPlainPixelsOld(image, file);
    } else {
        readNotPlainPixelsOld(image, file);
    }
    file.close();
    return image;
}

BitmapImage NetpbmLoader::generatePAM(std::ifstream &file) {
    //TODO Implement the code which read the .pam files.
    //They are not .pgm neither .ppm, but .pam are the only ones that implements the alpha channel.
    file.close();
    return BitmapImage(0, 0, RGBAlpha);
}

//Old it's referred to the fact that now only the PAM format is used for every type of images.
void NetpbmLoader::readMetaDataOld(std::ifstream &file) {
    file >> currentWidth;
    file >> currentHeight;
    file >> currentMaxValue;
}

void NetpbmLoader::readPlainPixelsOld(BitmapImage &image, std::ifstream &file) {
    int pixelValue;
    for (int row = 1; row <= currentHeight; row++) {
        for (int column = 1; column <= currentWidth; column++) {
            for (int channel = 1; channel <= currentChannels; channel++) {
                file >> pixelValue;
                image.setPixel(row, column, channel, 255 / currentMaxValue * pixelValue);
            }
        }
    }
}

void
NetpbmLoader::readNotPlainPixelsOld(BitmapImage &image, std::ifstream &file) {
    file.ignore();
    int pixelValue;
    for (int row = 1; row <= currentHeight; row++) {
        for (int column = 1; column <= currentWidth; column++) {
            for (int channel = 1; channel <= currentChannels; channel++) {
                pixelValue = file.get();
                image.setPixel(row, column, channel, 255 / currentMaxValue * pixelValue);
            }
        }
    }
}
