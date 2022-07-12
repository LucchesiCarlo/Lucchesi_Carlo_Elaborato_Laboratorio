//
// Created by carlo on 12/07/22.
//
#include <iostream>
#include <fstream>
#include "NetpbmSaver.h"

void NetpbmSaver::saveImage(const BitmapImage &image, const std::string &url) const {
    std::ofstream file(url, std::ofstream::out | std::ofstream::trunc);
    if (file.good()) {
        switch (image.getType()) {
            case Gray:
                saveGrayImage(image, file);
                break;
            case RGB:
                saveRGBImage(image, file);
                break;
            case GrayAlpha:
            case RGBAlpha:
                savePAMImage(image, file);
                break;
        }
        file << std::endl;
    } else {
        throw std::invalid_argument("Error: it's impossible to save the image.");
    }
}

void NetpbmSaver::saveGrayImage(const BitmapImage &image, std::ofstream &file) const {
    file << "P2" << std::endl;
    writeMetaDataOld(image, file);
    int width = image.getWidth();
    int height = image.getHeight();

    for (int row = 1; row <= height; row++) {
        for (int column = 1; column <= width; column++) {
            file << image.getPixel(row, column, 1) << std::endl;
        }
    }
}

void NetpbmSaver::saveRGBImage(const BitmapImage &image, std::ofstream &file) const {
    file << "P3" << std::endl;
    writeMetaDataOld(image, file);
    int width = image.getWidth();
    int height = image.getHeight();

    for (int row = 1; row <= height; row++) {
        for (int column = 1; column <= width; column++) {
            for (int channel = 1; channel <= 3; channel++) {
                file << image.getPixel(row, column, channel) << " ";
            }
            file << std::endl;
        }
    }
}

void NetpbmSaver::savePAMImage(const BitmapImage &image, std::ofstream &file) const {
    //TODO Do code that saves .pam files.
}

//It's called Old because now the .pam format can be used for every type of image
void NetpbmSaver::writeMetaDataOld(const BitmapImage &image, std::ofstream &file) const {
    file << image.getWidth() << " " << image.getHeight() << std::endl << 255 << std::endl;
}
