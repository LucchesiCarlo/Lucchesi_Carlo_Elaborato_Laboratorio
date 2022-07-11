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
    BitmapImage loadImage(const std::string &url) const override;
};


#endif //LUCCHESI_CARLO_ELABORATO_LABORATORIO_NETPBMLOADER_H
