//
// Created by carlo on 08/07/22.
//
#include "gtest/gtest.h"

#include "../BitmapImage.h"

class BitmapImageSuite : public ::testing::Test {

protected:
    void SetUp() override {
        image1.setPixel(2, 3, 1, 10);
    }

    BitmapImage image1{3, 2, Gray};
    BitmapImage image2{3, 2, RGB};
    BitmapImage image3{image2};
};

TEST_F(BitmapImageSuite, TestEqualOperator) {
    bool isEqual = image2 == image3;
    ASSERT_EQ(isEqual, true);
    isEqual = image1 == image2;
    EXPECT_EQ(isEqual, false);
}

TEST_F(BitmapImageSuite, TestCopyConstructor) {
    ASSERT_EQ(image2, image3);
    image2.setPixel(1, 1, 1, 10);
    image3.setPixel(1, 1, 1, 5);
    //To ensure that the images should be different
    EXPECT_NE(image2.getPixel(1, 1, 1), image3.getPixel(1, 1, 1));
    //Because BitmapImage doesn't override the != operator
}

TEST_F(BitmapImageSuite, TestAssignment) {
    image1 = image1;
    ASSERT_NO_THROW(image1.getPixel(1, 1, 1));
    image1 = image2;
    ASSERT_EQ(image1, image2);
    image1.setPixel(1, 1, 1, 10);
    image2.setPixel(1, 1, 1, 5);
    EXPECT_NE(image1.getPixel(1, 1, 1), image2.getPixel(1, 1, 1));
    //Because BitmapImage doesn't override the != operator
}