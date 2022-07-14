//
// Created by carlo on 08/07/22.
//
#include "gtest/gtest.h"

#include "../BitmapImage.h"

class BitmapImageSuite : public ::testing::Test {

protected:
    BitmapImageSuite() : image1{3, 2, Gray}, image2{3, 2, RGB}, image3{image2} {};

    void SetUp() override {
        image1.setPixel(2, 3, 1, 10);
    }

    BitmapImage image1;
    BitmapImage image2;
    BitmapImage image3;
};

TEST_F(BitmapImageSuite, TestEqualOperator) {
    ASSERT_TRUE(image2 == image3) << "image2 and image3 should be equal.";
    ASSERT_FALSE(image1 == image2) << "image1 and image3 should be different.";
}

TEST_F(BitmapImageSuite, TestCopyConstructor) {
    ASSERT_EQ(image2, image3) << "The copy constructor doesn't work.";
    image2.setPixel(1, 1, 1, 10);
    image3.setPixel(1, 1, 1, 5);
    //To ensure that the images should be different
    ASSERT_NE(image2.getPixel(1, 1, 1), image3.getPixel(1, 1, 1))
                                << "The images remain equals after different setPixels.";
    //Because BitmapImage doesn't override the != operator
}

TEST_F(BitmapImageSuite, TestAssignment) {
    image1 = image1;
    ASSERT_NO_THROW(image1.getPixel(1, 1, 1)) << "The auto-assigment may destroy the image.";
    image1 = image2;
    ASSERT_EQ(image1, image2) << "The assigment operator doesn't work.";
    image1.setPixel(1, 1, 1, 10);
    image2.setPixel(1, 1, 1, 5);
    ASSERT_NE(image1.getPixel(1, 1, 1), image2.getPixel(1, 1, 1)) << "The deep copy does'nt work properly.";
    //Because BitmapImage doesn't override the != operator
}