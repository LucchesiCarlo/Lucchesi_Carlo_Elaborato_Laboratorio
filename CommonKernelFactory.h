//
// Created by carlo on 15/07/22.
//
#include <cmath>
#include "KernelProcessing.h"

class CommonKernelFactory {
public:
    static KernelProcessing identityKernel(KernelDimension dimension) {
        return KernelProcessing(dimension);
    }

    static KernelProcessing ridgeDetection(bool strong = false) {
        KernelProcessing kernel(Three);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                kernel.setMaskElement(i, j, -1);
            }
        }
        kernel.setMaskElement(1, 1, (strong) ? 8 : 4);
        return kernel;
    }

    static KernelProcessing sharpen() {
        KernelProcessing kernel(Three);

        kernel.setMaskElement(0, 1, -1);
        kernel.setMaskElement(1, 0, -1);
        kernel.setMaskElement(1, 2, -1);
        kernel.setMaskElement(2, 1, -1);

        kernel.setMaskElement(1, 1, 5);

        return kernel;
    }

    static KernelProcessing boxBlur() {
        KernelProcessing kernel(Three);

        float fraction = 1. / 9.;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                kernel.setMaskElement(i, j, fraction);
            }
        }

        return kernel;
    }

    static KernelProcessing gaussianBlur(KernelDimension dimension, float deviation = 0.84089642) {
        KernelProcessing kernel(dimension);
        float base = 2 * pow(deviation, 2);
        int radius = (kernel.getDimension() - 1) / 2;

        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                float exponent = -(pow(i, 2) + pow(j, 2)) / base;
                float value = (1. / (M_PI * base)) * pow(M_E, exponent);
                kernel.setMaskElement(i + radius, j + radius, value);
            }
        }

        return kernel;
    }
};