//
// Created by carlo on 11/07/22.
//

#ifndef LUCCHESI_CARLO_ELABORATO_LABORATORIO_IMAGELOADER_H
#define LUCCHESI_CARLO_ELABORATO_LABORATORIO_IMAGELOADER_H

#include "BitmapImage.h"

class ImageLoader {
public:
    virtual BitmapImage loadImage(const std::string &url) const = 0;
};

#endif //LUCCHESI_CARLO_ELABORATO_LABORATORIO_IMAGELOADER_H
