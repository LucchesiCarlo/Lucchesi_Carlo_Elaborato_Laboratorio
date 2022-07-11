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
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << kernel.getMaskElement(i + 1, j + 1) << "-";
        }
        std::cout << std::endl;
    }
    std::cout << image.getPixel(1, 1, 1) * kernel.getMaskElement(3, 3) << std::endl;
    std::cout << image.getPixel(1, 1, 1) * kernel.getMaskElement(2, 2) << std::endl;
    std::cout << image.getPixel(1, 1, 1) * kernel.getMaskElement(1, 1) << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << image.getPixel(i / 3 + 1, i % 3 + 1, 1) << "-";
        std::cout << result.getPixel(i / 3 + 1, i % 3 + 1, 1) << "-";
        std::cout << expectedResult.getPixel(i / 3 + 1, i % 3 + 1, 1) << std::endl;
    }
    ASSERT_EQ(result, expectedResult) << "Kernel processing doesn't perform as expected.";
}