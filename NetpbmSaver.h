//
// Created by carlo on 12/07/22.
//

#ifndef LUCCHESI_CARLO_ELABORATO_LABORATORIO_NETPBMSAVER_H
#define LUCCHESI_CARLO_ELABORATO_LABORATORIO_NETPBMSAVER_H


#include "ImageSaver.h"

class NetpbmSaver : public ImageSaver {
public:

    void saveImage(const BitmapImage &image, const std::string &url) override;

    void setPlain(bool plain) {
        isPlain = plain;
    }

    void setPAM(bool PAM) {
        isPAM = PAM;
    }

private:
    bool isPlain = true;
    bool isPAM = false;

    void saveGrayImage(const BitmapImage &image, std::ofstream &file);

    void saveRGBImage(const BitmapImage &image, std::ofstream &file);

    void savePAMImage(const BitmapImage &image, std::ofstream &file);

    void writeMetaDataOld(const BitmapImage &image, std::ofstream &file);

    void writePlainPixels(const BitmapImage &image, std::ofstream &file);

    void writeNotPlainPixels(const BitmapImage &image, std::ofstream &file);
};


#endif //LUCCHESI_CARLO_ELABORATO_LABORATORIO_NETPBMSAVER_H
