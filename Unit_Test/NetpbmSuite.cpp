//
// Created by carlo on 12/07/22.
//
#include "gtest/gtest.h"
#include "../NetpbmIO.h"

bool equalFiles(std::string lhs, std::string rhs);

class NetpbmSuite : public ::testing::Test {
protected:
    NetpbmSuite() {
        saver.setPlain(false);
    }

    NetpbmIO saver;
    NetpbmIO loader;
};

TEST_F(NetpbmSuite, TestLoadANDSavePGM) {
    BitmapImage image = loader.loadImage("./Logo.pgm");
    saver.saveImage(image, "./MYLogo.pgm");
    ASSERT_TRUE(equalFiles("./Logo.pgm", "./MYLogo.pgm")) << "The PGM format with binary encoding doesn't work";
}

TEST_F(NetpbmSuite, TestLoadANDSavePPM) {
    BitmapImage image = loader.loadImage("./Rainbow.ppm");
    saver.saveImage(image, "./MYRainbow.ppm");
    ASSERT_TRUE(equalFiles("./Rainbow.ppm", "./MYRainbow.ppm")) << "The PPM format with binary encoding doesn't work";
}

//Unfortunately, the .pam format is not supported by the major part of image shower, in fact without a dedicated software
// it's impossible to see if the images are equal.
//On the other hand the file are the same according to the equalFiles function, and even for Unix's cmp command.
TEST_F(NetpbmSuite, TestLoadANDSavePAM) {
    BitmapImage image = loader.loadImage("./Mint_Logo.pam");
    saver.saveImage(image, "./MYMint_Logo.pam");
    ASSERT_TRUE(equalFiles("./Mint_Logo.pam", "./MYMint_Logo.pam"));
}

bool equalFiles(std::string lhs, std::string rhs) {
    std::ifstream lhsFile(lhs, std::ifstream::binary);
    std::ifstream rhsFile(rhs, std::ifstream::binary);
    char lhsChar = lhsFile.get();
    char rhsChar = rhsFile.get();
    while (!lhsFile.eof()) {
        if (lhsFile.eof() != rhsFile.eof() || lhsChar != rhsChar) {
            return false;
        }
        lhsChar = lhsFile.get();
        rhsChar = rhsFile.get();
    }
    if (lhsFile.eof() != rhsFile.eof()) {
        return false;
    }
    return true;
}