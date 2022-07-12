//
// Created by carlo on 12/07/22.
//
#include "gtest/gtest.h"
#include "../NetpbmLoader.h"
#include "../NetpbmSaver.h"

class NetpbmSaverSuite : public ::testing::Test {
protected:

    NetpbmSaverSuite() : imageGray(3, 2, Gray), imageRGB(3, 2, RGB) {
        for (int row = 1; row <= 2; row++) {
            for (int column = 1; column <= 3; column++) {
                imageGray.setPixel(row, column, 1, 3);
            }
        }

        //Setting up the RGB image
        //Setting up the Red Channel
        imageRGB.setPixel(1, 1, 1, 255);
        imageRGB.setPixel(2, 1, 1, 122);
        imageRGB.setPixel(2, 2, 1, 33);

        //Setting up the Green Channel
        imageRGB.setPixel(1, 2, 2, 199);
        imageRGB.setPixel(2, 1, 2, 22);
        imageRGB.setPixel(2, 2, 2, 77);

        //Setting up the Blu Channel
        imageRGB.setPixel(1, 3, 3, 47);
        imageRGB.setPixel(2, 2, 3, 22);
        imageRGB.setPixel(2, 3, 3, 255);
    }

    BitmapImage imageGray;
    BitmapImage imageRGB;
};

TEST_F(NetpbmSaverSuite, TestGraySaving) {
    NetpbmSaver saver;
    NetpbmLoader loader;
    saver.saveImage(imageGray, "./saveTest.pgm");

    BitmapImage result = loader.loadImage("./saveTest.pgm");
    ASSERT_EQ(imageGray, result) << "Something during the file saving does wrong (Gray Images).";
}

TEST_F(NetpbmSaverSuite, TestRGBSaving) {
    NetpbmSaver saver;
    NetpbmLoader loader;
    saver.saveImage(imageRGB, "./saveTest.ppm");

    BitmapImage result = loader.loadImage("./saveTest.ppm");
    ASSERT_EQ(imageRGB, result) << "Something during the file saving does wrong (RGB images).";
}