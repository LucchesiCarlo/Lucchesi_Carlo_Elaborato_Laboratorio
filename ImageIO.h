//
// Created by carlo on 11/07/22.
//

#ifndef LUCCHESI_CARLO_ELABORATO_LABORATORIO_IMAGEIO_H
#define LUCCHESI_CARLO_ELABORATO_LABORATORIO_IMAGEIO_H

#include "BitmapImage.h"

class ImageIO {
public:
    virtual BitmapImage loadImage(const std::string &url) = 0;

    virtual void saveImage(const BitmapImage &image, const std::string &url) = 0;

    virtual ~ImageIO() = default;

protected:
    //They are present because during the loading of an image these values are used many times.
    //So, to avoid an excessive use of getter method or numbers of reference parameters of the method it's possible to use this attributes.
    int currentWidth = 1;
    int currentHeight = 1;
    int currentChannels = 1;
};

#endif //LUCCHESI_CARLO_ELABORATO_LABORATORIO_IMAGEIO_H
