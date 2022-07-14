//
// Created by carlo on 11/07/22.
//
#include "gtest/gtest.h"
#include "../NetpbmIO.h"

class NetpbmLoadingSuite : public ::testing::Test {
protected:
    NetpbmLoadingSuite() : expectedResultGray(3, 2, Gray), expectedResultRGB(3, 2, RGB) {
        int value = 1;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                expectedResultGray.setPixel(i, j, 0, value++);
            }
        }

        //Setting up the RGB image
        //Setting up the Red Channel
        expectedResultRGB.setPixel(0, 0, 0, 255);
        expectedResultRGB.setPixel(1, 0, 0, 255);
        expectedResultRGB.setPixel(1, 1, 0, 255);

        //Setting up the Green Channel
        expectedResultRGB.setPixel(0, 1, 1, 255);
        expectedResultRGB.setPixel(1, 0, 1, 255);
        expectedResultRGB.setPixel(1, 1, 1, 255);

        //Setting up the Blu Channel
        expectedResultRGB.setPixel(0, 2, 2, 255);
        expectedResultRGB.setPixel(1, 1, 2, 255);
    }

    BitmapImage expectedResultGray;
    BitmapImage expectedResultRGB;
};

TEST_F(NetpbmLoadingSuite, TestPGMLoader) {
    NetpbmIO loader;
    BitmapImage image = loader.loadImage("./test.pgm");
    ASSERT_EQ(image, expectedResultGray) << "The PGM format loader doesn't work.";
}

TEST_F(NetpbmLoadingSuite, TestPPMLoader) {
    NetpbmIO loader;
    BitmapImage image = loader.loadImage("./test.ppm");
    ASSERT_EQ(image, expectedResultRGB) << "The PPM format loader doesn't work.";
}