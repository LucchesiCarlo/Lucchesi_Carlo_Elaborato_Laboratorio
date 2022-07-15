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

        if (!magicNumber.compare("P5") || !magicNumber.compare("P6") || !magicNumber.compare("P7")) {
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
        readNotPlainPixels(image, file);
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
        readNotPlainPixels(image, file);
    }
    file.close();
    return image;
}

BitmapImage NetpbmIO::generatePAM(std::ifstream &file) {
    //TODO Implement the code which read the .pam files.
    //They are not .pgm neither .ppm, but .pam are the only ones that implements the alpha channel.
    ImageType imageType;
    for (int i = 0; i < 6; i++) {
        std::string attribute;
        file >> attribute;
        if (!attribute.compare("WIDTH")) {
            file >> currentWidth;
        } else if (!attribute.compare("HEIGHT")) {
            file >> currentHeight;
        } else if (!attribute.compare("DEPTH")) {
            file >> currentChannels;
        } else if (!attribute.compare("MAXVAL")) {
            file >> currentMaxValue;
        } else if (!attribute.compare("TUPLTYPE")) {
            std::string type;
            file >> type;
            if (!type.compare("GRAYSCALE")) {
                imageType = Gray;
            } else if (!type.compare("GRAYSCALE_ALPHA")) {
                imageType = GrayAlpha;
            } else if (!type.compare("RGB")) {
                imageType = RGB;
            } else if (!type.compare("RGB_ALPHA")) {
                imageType = RGBAlpha;
            } else {
                throw std::invalid_argument("Error: this image has a bad heading.");
            }
        } else if (!attribute.compare("ENDHDR")) {
            break;
        }
    }
    if ((imageType == Gray && currentChannels != 1) || (imageType == GrayAlpha && currentChannels != 2) ||
        (imageType == RGB && currentChannels != 3) || (imageType == RGBAlpha && currentChannels != 4)) {
        throw std::invalid_argument("Error: the given file has the wrong attributes.");
    }

    BitmapImage image(currentWidth, currentHeight, imageType);
    if (imageType == Gray || imageType == RGB) {
        readNotPlainPixels(image, file);
    } else {
        readNotPlainPixels(image, file);
    }
    file.close();
    return image;
}

//Old it's referred to the fact that now only the PAM format is used for every type of images.
void NetpbmIO::readMetaDataOld(std::ifstream &file) {
    file >> currentWidth;
    file >> currentHeight;
    file >> currentMaxValue;
}

void NetpbmIO::readPlainPixelsOld(BitmapImage &image, std::ifstream &file) {
    int pixelValue;
    for (int row = 0; row < currentHeight; row++) {
        for (int column = 0; column < currentWidth; column++) {
            for (int channel = 0; channel < currentChannels; channel++) {
                file >> pixelValue;
                image.setPixel(row, column, channel, 255 / currentMaxValue * pixelValue);
            }
        }
    }
}

void NetpbmIO::readNotPlainPixels(BitmapImage &image, std::ifstream &file) {
    file.ignore();
    int pixelValue = 0;
    for (int row = 0; row < currentHeight; row++) {
        for (int column = 0; column < currentWidth; column++) {
            for (int channel = 0; channel < currentChannels; channel++) {
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
        if (isPAM) {
            savePAMImage(image, file);
        } else {
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
        writePlainPixelsOld(image, file);
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
        writePlainPixelsOld(image, file);
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
            file << "GRAYSCALE_ALPHA";
            break;
        case RGB:
            file << "RGB";
            break;
        case RGBAlpha:
            file << "RGB_ALPHA";
            break;
    }
    file << std::endl << "ENDHDR" << std::endl;

    writeNotPlainPixels(image, file);
}

//It's called Old because now the .pam format can be used for every type of image
void NetpbmIO::writeMetaDataOld(const BitmapImage &image, std::ofstream &file) {
    file << image.getWidth() << " " << image.getHeight() << std::endl << 255 << std::endl;
}

void NetpbmIO::writePlainPixelsOld(const BitmapImage &image, std::ofstream &file) {
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            for (int channel = 0; channel < channels; channel++) {
                file << image.getPixel(row, column, channel) << " ";
            }
            file << std::endl;
        }
    }
}

void NetpbmIO::writeNotPlainPixels(const BitmapImage &image, std::ofstream &file) {
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            for (int channel = 0; channel < channels; channel++) {
                file.put((image.getPixel(row, column, channel)));
            }
        }
    }
}

