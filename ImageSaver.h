//
// Created by carlo on 11/07/22.
//

#ifndef LUCCHESI_CARLO_ELABORATO_LABORATORIO_IMAGESAVER_H
#define LUCCHESI_CARLO_ELABORATO_LABORATORIO_IMAGESAVER_H

#include "BitmapImage.h"

class ImageSaver {
public:
    virtual void saveImage(const BitmapImage &image, const std::string &url) = 0;
};

#endif //LUCCHESI_CARLO_ELABORATO_LABORATORIO_IMAGESAVER_H
