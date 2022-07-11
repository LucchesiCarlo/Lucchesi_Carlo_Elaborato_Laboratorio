//
// Created by carlo on 11/07/22.
//
#include <memory>
#include "NetpbmLoader.h"

BitmapImage NetpbmLoader::loadImage(const std::string &url) const {
    std::unique_ptr<BitmapImage> image;
    std::ifstream imageFile(url);
    if (imageFile.is_open()) {
        /*
        char * type = new char[2];
        imageFile.read(type, 2);
        */image = std::make_unique<BitmapImage>(0, 0, Gray);
        //TODO Read from the file and create the image
    } else {
        throw std::invalid_argument("Error: it's impossible to open the file given as the url.");
    }
    return BitmapImage(0, 0, RGB);
}
