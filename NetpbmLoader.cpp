//
// Created by carlo on 11/07/22.
//
#include <cstring>
#include <memory>
#include "NetpbmLoader.h"

BitmapImage NetpbmLoader::loadImage(const std::string &url) const {
    std::ifstream imageFile(url);
    if (imageFile.is_open()) {
        //It's actually called Magic Number in the wikipedia page https://en.wikipedia.org/wiki/Netpbm#Description
        std::unique_ptr<char> magicNumber(new char[3]);
        imageFile.getline(magicNumber.get(), 3);
        if (!std::strcmp(magicNumber.get(), "P2")) {
            return generatePGM(imageFile);
        } else if (!std::strcmp(magicNumber.get(), "P3")) {
            return generatePPM(imageFile);
        } else if (!std::strcmp(magicNumber.get(), "P7")) {
            return generatePAM(imageFile);
        } else {
            throw std::invalid_argument("Error: the file has an unknown format.");
        }
        //TODO Read from the file and create the image
    } else {
        throw std::invalid_argument("Error: it's impossible to open the file given as the url.");
    }
}

BitmapImage NetpbmLoader::generatePGM(std::ifstream &file) const {
    int width = 1;
    int height = 1;
    int maxValue = 255;
    readMetaDataOld(width, height, maxValue, file);
    BitmapImage image(width, height, Gray);
    std::string pixelData;
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            file >> pixelData;
            int pixelValue = std::stoi(pixelData);
            image.setPixel(i, j, 1, 255 / maxValue * pixelValue);
        }
    }
    return image;
}

BitmapImage NetpbmLoader::generatePPM(std::ifstream &file) const {
    int width = 1;
    int height = 1;
    int maxValue = 255;
    readMetaDataOld(width, height, maxValue, file);
    BitmapImage image(width, height, RGB);
    std::string pixelData;
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            for (int c = 1; c <= 3; c++) {
                file >> pixelData;
                int pixelValue = std::stoi(pixelData);
                image.setPixel(i, j, c, 255 / maxValue * pixelValue);
            }
        }
    }
    return image;
}

BitmapImage NetpbmLoader::generatePAM(std::ifstream &file) const {
    //TODO Implement the code which read the .pam files.
    //They are not .pgm neither .ppm, but .pam are the only ones that implements the alpha channel.
    return BitmapImage(0, 0, RGBAlpha);
}

void NetpbmLoader::readMetaDataOld(int &width, int &height, int &maxValue, std::ifstream &file) const {
    std::string data;
    file >> data;
    width = std::stoi(data);
    file >> data;
    height = std::stoi(data);
    file >> data;
    maxValue = std::stoi(data);
}
