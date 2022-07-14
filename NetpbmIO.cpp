//
// Created by carlo on 11/07/22.
//
#include <cstring>
#include <memory>
#include "NetpbmIO.h"

BitmapImage NetpbmIO::loadImage(const std::string &url) {
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

BitmapImage NetpbmIO::generatePGM(std::ifstream &file) {
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

BitmapImage NetpbmIO::generatePPM(std::ifstream &file) {
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

BitmapImage NetpbmIO::generatePAM(std::ifstream &file) {
    //TODO Implement the code which read the .pam files.
    //They are not .pgm neither .ppm, but .pam are the only ones that implements the alpha channel.
    file.close();
    return BitmapImage(0, 0, RGBAlpha);
}

//Old it's referred to the fact that now only the PAM format is used for every type of images.
void NetpbmIO::readMetaDataOld(std::ifstream &file) {
    file >> currentWidth;
    file >> currentHeight;
    file >> currentMaxValue;
}

void NetpbmIO::readPlainPixelsOld(BitmapImage &image, std::ifstream &file) {
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
NetpbmIO::readNotPlainPixelsOld(BitmapImage &image, std::ifstream &file) {
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

void NetpbmIO::saveImage(const BitmapImage &image, const std::string &url) {
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

void NetpbmIO::saveGrayImage(const BitmapImage &image, std::ofstream &file) {
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

void NetpbmIO::saveRGBImage(const BitmapImage &image, std::ofstream &file) {
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

void NetpbmIO::savePAMImage(const BitmapImage &image, std::ofstream &file) {
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
void NetpbmIO::writeMetaDataOld(const BitmapImage &image, std::ofstream &file) {
    file << image.getWidth() << " " << image.getHeight() << std::endl << 255 << std::endl;
}

void NetpbmIO::writePlainPixels(const BitmapImage &image, std::ofstream &file) {
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

void NetpbmIO::writeNotPlainPixels(const BitmapImage &image, std::ofstream &file) {
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

