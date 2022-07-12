//
// Created by carlo on 12/07/22.
//

#ifndef LUCCHESI_CARLO_ELABORATO_LABORATORIO_NETPBMSAVER_H
#define LUCCHESI_CARLO_ELABORATO_LABORATORIO_NETPBMSAVER_H


#include "ImageSaver.h"

class NetpbmSaver : public ImageSaver {
public:
    void saveImage(const BitmapImage &image, const std::string &url) const override;

private:
    void saveGrayImage(const BitmapImage &image, std::ofstream &file) const;

    void saveRGBImage(const BitmapImage &image, std::ofstream &file) const;

    void savePAMImage(const BitmapImage &image, std::ofstream &file) const;

    void writeMetaDataOld(const BitmapImage &image, std::ofstream &file) const;
};


#endif //LUCCHESI_CARLO_ELABORATO_LABORATORIO_NETPBMSAVER_H
