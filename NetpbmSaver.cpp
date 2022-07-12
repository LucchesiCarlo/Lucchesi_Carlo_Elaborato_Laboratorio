//
// Created by carlo on 12/07/22.
//
#include <iostream>
#include <fstream>
#include "NetpbmSaver.h"

void NetpbmSaver::saveImage(const BitmapImage &image, const std::string &url) {
    std::ofstream file;
    if (isPlain) {
        file = std::ofstream(url, std::ofstream::trunc);
    } else {
        file = std::ofstream(url, std::ofstream::trunc | std::ofstream::binary);
    }
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
        file.close();
    } else {
        throw std::invalid_argument("Error: it's impossible to save the image.");
    }
}

void NetpbmSaver::saveGrayImage(const BitmapImage &image, std::ofstream &file) {
    if (isPlain) {
        file << "P2" << std::endl;
        writeMetaDataOld(image, file);
        writePlainPixels(image, file);
    } else {
        file << "P5" << std::endl;
        writeMetaDataOld(image, file);
        writeNotPlainPixels(image, file);
    }
}

void NetpbmSaver::saveRGBImage(const BitmapImage &image, std::ofstream &file) {
    if (isPlain) {
        file << "P3" << std::endl;
        writeMetaDataOld(image, file);
        writePlainPixels(image, file);
    } else {
        file << "P6" << std::endl;
        writeMetaDataOld(image, file);
        writeNotPlainPixels(image, file);
    }
}

void NetpbmSaver::savePAMImage(const BitmapImage &image, std::ofstream &file) {
    if (isPlain) {
        throw std::invalid_argument("Error: it's impossible to save a .pam file with the ASCII code.");
    }

    file << "P7" << std::endl;
    file << "WIDTH " << image.getWidth() << std::endl;
    file << "HEIGHT " << image.getHeight() << std::endl;
    file << "DEPTH " << image.getChannels() << std::endl;
    file << "MAXVAL " << 255 << std::endl;
    file << "TUPLTYPE ";
    switch (image.getType()) {
        case Gray:
            file << "GRAYSCALE";
            break;
        case GrayAlpha:
            file << "GRAYSCALE_APLHA";
            break;
        case RGB:
            file << "RGB";
            break;
        case RGBAlpha:
            file << "RGB_APLHA";
            break;
    }
    file << std::endl;

    writeNotPlainPixels(image, file);

    file << "ENDHDR" << std::endl;
}

//It's called Old because now the .pam format can be used for every type of image
void NetpbmSaver::writeMetaDataOld(const BitmapImage &image, std::ofstream &file) {
    file << image.getWidth() << " " << image.getHeight() << std::endl << 255 << std::endl;
}

void NetpbmSaver::writePlainPixels(const BitmapImage &image, std::ofstream &file) {
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();

    for (int row = 1; row <= height; row++) {
        for (int column = 1; column <= width; column++) {
            for (int c = 1; c <= channels; c++) {
                file << image.getPixel(row, column, c) << " ";
            }
            file << std::endl;
        }
    }
}

void NetpbmSaver::writeNotPlainPixels(const BitmapImage &image, std::ofstream &file) {
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();

    for (int row = 1; row <= height; row++) {
        for (int column = 1; column <= width; column++) {
            for (int c = 1; c <= channels; c++) {
                file.put(static_cast<uint8_t> (image.getPixel(row, column, c)));
            }
        }
    }
}
