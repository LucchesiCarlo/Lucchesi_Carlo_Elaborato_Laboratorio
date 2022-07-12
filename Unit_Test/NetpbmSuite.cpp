//
// Created by carlo on 12/07/22.
//
#include "gtest/gtest.h"
#include "../NetpbmLoader.h"
#include "../NetpbmSaver.h"

bool equalFiles(std::string lhs, std::string rhs);

class NetpbmSuite : public ::testing::Test {
protected:
    NetpbmSuite() {
        saver.setPlain(false);
    }

    NetpbmSaver saver;
    NetpbmLoader loader;
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