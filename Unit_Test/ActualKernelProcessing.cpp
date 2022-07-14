//
// Created by carlo on 11/07/22.
//
#include "gtest/gtest.h"
#include "../KernelProcessing.h"

class ActualKernelProcessing : public ::testing::Test {
protected:
    ActualKernelProcessing() : kernel{Three}, image(4, 3, GrayAlpha), expectedResult{image} {
        kernel.setMaskElement(0, 0, 1);
        kernel.setMaskElement(2, 2, 1);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                image.setPixel(i, j, 0, 2);
                expectedResult.setPixel(i, j, 0, 6);
            }
        }
        image.setPixel(0, 0, 1, 33);
        expectedResult.setPixel(0, 0, 1, 66);
        expectedResult.setPixel(1, 1, 1, 33);
    }

    KernelProcessing kernel;
    BitmapImage image;
    BitmapImage expectedResult;
};

TEST_F(ActualKernelProcessing, TestApplyKernelProcessing) {
    BitmapImage result = kernel.processImage(image);

    ASSERT_EQ(result, expectedResult) << "Kernel processing doesn't perform as expected.";
}