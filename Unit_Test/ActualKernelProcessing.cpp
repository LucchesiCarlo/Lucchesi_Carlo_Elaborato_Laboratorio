//
// Created by carlo on 11/07/22.
//
#include "gtest/gtest.h"
#include "../KernelProcessing.h"

class ActualKernelProcessing : public ::testing::Test {
protected:
    ActualKernelProcessing() : kernel{Three}, image(3, 2, Gray), expectedResult{image} {
        kernel.setMaskElement(1, 1, 1);
        kernel.setMaskElement(3, 3, 1);
        for (int i = 0; i < 6; i++) {
            image.setPixel(i / 3 + 1, i % 3 + 1, 1, 2);
            expectedResult.setPixel(i / 3 + 1, i % 3 + 1, 1, 6);
        }
    }

    KernelProcessing kernel;
    BitmapImage image;
    BitmapImage expectedResult;
};

TEST_F(ActualKernelProcessing, TestApplyKernelProcessing) {
    BitmapImage result = kernel.processImage(image);

    ASSERT_EQ(result, expectedResult) << "Kernel processing doesn't perform as expected.";
}