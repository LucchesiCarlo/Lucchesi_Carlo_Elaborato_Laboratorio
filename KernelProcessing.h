//
// Created by carlo on 08/07/22.
//

#ifndef LUCCHESI_CARLO_ELABORATO_LABORATORIO_KERNELPROCESSING_H
#define LUCCHESI_CARLO_ELABORATO_LABORATORIO_KERNELPROCESSING_H

#include "BitmapImage.h"

enum KernelDimension {
    Three, Five
};

class KernelProcessing {
public:
    explicit KernelProcessing(KernelDimension type);

    BitmapImage processImage(const BitmapImage &image) const;

    void setMaskElement(int row, int column, float value);

private:
    int dimension;
    float *mask;

    int calculateValue(const BitmapImage &image, int row, int column, int channel) const;

    void extendHedge(const BitmapImage &image, int &row, int &column) const;
};


#endif //LUCCHESI_CARLO_ELABORATO_LABORATORIO_KERNELPROCESSING_H
