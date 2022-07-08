//
// Created by carlo on 08/07/22.
//
#include "gtest/gtest.h"
#include "../BitmapImage.h"

TEST(BitmapImageTests, TestSetGet) {
    BitmapImage image(3, 2, Gray);
    image.setPixel(1, 2, 1, 10);
    EXPECT_EQ(image.getPixel(1, 2, 1), 10);
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