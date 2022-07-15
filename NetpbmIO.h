//
// Created by carlo on 11/07/22.
//

#ifndef LUCCHESI_CARLO_ELABORATO_LABORATORIO_NETPBMIO_H
#define LUCCHESI_CARLO_ELABORATO_LABORATORIO_NETPBMIO_H


#include "ImageIO.h"
#include <iostream>
#include <fstream>

class NetpbmIO : public ImageIO {
public:
    BitmapImage loadImage(const std::string &url) override;

    void saveImage(const BitmapImage &image, const std::string &url) override;

    void setPlain(bool plain) {
        isPlain = plain;
    }

    void setPAM(bool PAM) {
        isPAM = PAM;
    }

private:
    //They are present to avoid an increasing of parameters in private methods.
    int currentMaxValue = 255;
    bool currentIsPlain = true;

    //Used by the saving method to specify how to save the image.
    bool isPlain = true;
    //To force the using of the .pam standard, even with grayscale o RGB images.
    bool isPAM = false;

    //Methods to load the images.
    BitmapImage generatePGM(std::ifstream &file);

    BitmapImage generatePPM(std::ifstream &file);

    BitmapImage generatePAM(std::ifstream &file);

    void readMetaDataOld(std::ifstream &file);

    void readPlainPixelsOld(BitmapImage &image, std::ifstream &file);

    void readNotPlainPixels(BitmapImage &image, std::ifstream &file);

    //Methods to save the images.
    void saveGrayImage(const BitmapImage &image, std::ofstream &file);

    void saveRGBImage(const BitmapImage &image, std::ofstream &file);

    void savePAMImage(const BitmapImage &image, std::ofstream &file);

    void writeMetaDataOld(const BitmapImage &image, std::ofstream &file);

    void writePlainPixelsOld(const BitmapImage &image, std::ofstream &file);

    void writeNotPlainPixels(const BitmapImage &image, std::ofstream &file);
};


#endif //LUCCHESI_CARLO_ELABORATO_LABORATORIO_NETPBMIO_H
