//
// Created by carlo on 08/07/22.
//
#include "gtest/gtest.h"
#include "../BitmapImage.h"

TEST(BitmapImageTests, TestSetGet) {
    BitmapImage image(3, 2, Gray);
    image.setPixel(1, 2, 0, 10);
    ASSERT_EQ(image.getPixel(1, 2, 0), 10) << "Or the setPixel or the getPixel doesn't work. ";
}

TEST(BitmapImageTests, TestGoodData) {
    BitmapImage image(3, 2, GrayAlpha);
    ASSERT_NO_THROW(image.getPixel(1, 2, 1));
    ASSERT_NO_THROW(image.getPixel(1, 0, 0));

    ASSERT_NO_THROW(image.setPixel(0, 2, 1, 33));
    ASSERT_NO_THROW(image.setPixel(0, 0, 0, 0));
}

TEST(BitmapImageTests, TestLimitData) {
    BitmapImage image(3, 2, RGB);
    image.setPixel(0, 0, 0, 999);
    ASSERT_EQ(image.getPixel(0, 0, 0), 255);

    image.setPixel(1, 0, 2, -999);
    ASSERT_EQ(image.getPixel(1, 0, 2), 0);
}

TEST(BitmapImageTests, TestWrongData) {
    ASSERT_THROW(BitmapImage(-1, 2, RGB), std::invalid_argument);
    ASSERT_THROW(BitmapImage(1, -2, RGB), std::invalid_argument);

    BitmapImage image(3, 3, RGBAlpha);
    ASSERT_THROW(image.setPixel(-1, 1, 1, 10), std::invalid_argument);
    ASSERT_THROW(image.setPixel(1, -1, 1, 10), std::invalid_argument);
    ASSERT_THROW(image.setPixel(1, 1, -1, 10), std::invalid_argument);


    ASSERT_THROW(image.setPixel(5, 1, 1, 10), std::invalid_argument);
    ASSERT_THROW(image.setPixel(1, 33, 1, 10), std::invalid_argument);
    ASSERT_THROW(image.setPixel(1, 1, 5, 10), std::invalid_argument);
}