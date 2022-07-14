//
// Created by carlo on 09/07/22.
//
#include "gtest/gtest.h"
#include "../KernelProcessing.h"

TEST(KernelProcessingTests, TestGetSet) {
    KernelProcessing kernel(Three);
    kernel.setMaskElement(1, 1, 10);

    ASSERT_EQ(kernel.getMaskElement(1, 1), 10);
}

TEST(KernelProcessingTests, TestContructor) {
    KernelProcessing three(Three);
    KernelProcessing five(Five);

    ASSERT_EQ(three.getMaskElement(1, 1), 1) << "3x3 Kernel constructor failed (check middle element).";
    ASSERT_EQ(three.getMaskElement(2, 2), 0) << "3x3 Kernel constructor failed";

    ASSERT_EQ(five.getMaskElement(2, 2), 1) << "5x5 Kernel constructor failed (check middle element).";
    ASSERT_EQ(five.getMaskElement(2, 1), 0) << "5x5 Kernel constructor failed";
}

TEST(KernelProcessingTests, TestWrongData) {
    KernelProcessing three(Three);
    KernelProcessing five(Five);

    EXPECT_THROW(three.getMaskElement(-1, 1), std::invalid_argument);
    EXPECT_THROW(three.getMaskElement(1, -1), std::invalid_argument);
    EXPECT_THROW(three.getMaskElement(4, 1), std::invalid_argument);
    EXPECT_THROW(three.getMaskElement(1, 4), std::invalid_argument);

    EXPECT_NO_THROW(three.getMaskElement(1, 2));
    EXPECT_NO_THROW(three.setMaskElement(2, 1, 10));


    EXPECT_THROW(five.getMaskElement(-1, 1), std::invalid_argument);
    EXPECT_THROW(five.getMaskElement(1, -1), std::invalid_argument);
    EXPECT_THROW(five.getMaskElement(6, 1), std::invalid_argument);
    EXPECT_THROW(five.getMaskElement(1, 6), std::invalid_argument);

    EXPECT_NO_THROW(five.getMaskElement(1, 4));
    EXPECT_NO_THROW(five.setMaskElement(3, 2, 10));
}

TEST(KernelProcessingTests, TestIdentityMask) {
    KernelProcessing identity(Three);
    BitmapImage image(2, 3, RGB);

    image.setPixel(0, 0, 1, 4);
    image.setPixel(0, 1, 1, 6);

    image.setPixel(1, 0, 2, 4);
    image.setPixel(0, 0, 2, 33);

    BitmapImage result = identity.processImage(image);
    ASSERT_EQ(result, image) << "Identity Kernel Processing doesn't perform correctly.";
}
