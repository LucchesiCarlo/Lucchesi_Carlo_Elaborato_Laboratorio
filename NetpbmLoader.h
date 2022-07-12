//
// Created by carlo on 11/07/22.
//

#ifndef LUCCHESI_CARLO_ELABORATO_LABORATORIO_NETPBMLOADER_H
#define LUCCHESI_CARLO_ELABORATO_LABORATORIO_NETPBMLOADER_H


#include "ImageLoader.h"
#include <iostream>
#include <fstream>

class NetpbmLoader : public ImageLoader {
public:
    BitmapImage loadImage(const std::string &url) override;

private:
    int currentWidth = 1;
    int currentHeight = 1;
    int currentMaxValue = 255;
    int currentChannels = 1;
    bool currentIsPlain = true;

    BitmapImage generatePGM(std::ifstream &file);

    BitmapImage generatePPM(std::ifstream &file);

    BitmapImage generatePAM(std::ifstream &file);

    void readMetaDataOld(std::ifstream &file);

    void readPlainPixelsOld(BitmapImage &image, std::ifstream &file);

    void readNotPlainPixelsOld(BitmapImage &image, std::ifstream &file);
};


#endif //LUCCHESI_CARLO_ELABORATO_LABORATORIO_NETPBMLOADER_H
