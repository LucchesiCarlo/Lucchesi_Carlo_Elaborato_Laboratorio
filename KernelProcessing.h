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

    KernelProcessing(const KernelProcessing &kernel) {
        copyValues(kernel);
    }

    KernelProcessing &operator=(const KernelProcessing &rhs);

    bool operator==(const KernelProcessing &rhs) const;

    BitmapImage processImage(const BitmapImage &image) const;

    void setMaskElement(int row, int column, float value);

    float getMaskElement(int row, int column) const;

    int getDimension() const {
        return dimension;
    }

    ~KernelProcessing() {
        delete[] mask;
    }

private:
    int dimension;
    float *mask;

    void copyValues(const KernelProcessing &kernel);

    int calculateValue(const BitmapImage &image, int row, int column, int channel) const;

    void extendHedge(const BitmapImage &image, int &row, int &column) const;

    bool itsValidPosition(int row, int column) const;
};


#endif //LUCCHESI_CARLO_ELABORATO_LABORATORIO_KERNELPROCESSING_H
