#include <iostream>
#include "NetpbmIO.h"
#include "KernelProcessing.h"
#include "CommonKernelFactory.h"

int main() {
    //Demo of the functionality.
    NetpbmIO netpbmIO;
    //The images are named with progressive number to sort in the file system. So you can slide them in sequence.
    BitmapImage image = netpbmIO.loadImage("./0Linux_Logo.ppm");

    KernelProcessing identity = CommonKernelFactory::identityKernel(Three);
    KernelProcessing ridgeDetection = CommonKernelFactory::ridgeDetection();
    KernelProcessing ridgeDetectionS = CommonKernelFactory::ridgeDetection(true);
    KernelProcessing sharpen = CommonKernelFactory::sharpen();
    KernelProcessing boxBlur = CommonKernelFactory::boxBlur();
    KernelProcessing gaussianBlur3 = CommonKernelFactory::gaussianBlur(Three);
    KernelProcessing gaussianBlur5 = CommonKernelFactory::gaussianBlur(Five);
    std::cout << "Convolution Kernels created!" << std::endl;

    BitmapImage identityResult = identity.processImage(image);
    std::cout << "Identity Performed!" << std::endl;
    netpbmIO.saveImage(identityResult, "./1Identity.ppm");
    std::cout << "Identity Saved!" << std::endl;

    BitmapImage ridgeDetectionResult = ridgeDetection.processImage(image);
    std::cout << "Ridge Detection Performed!" << std::endl;
    netpbmIO.saveImage(ridgeDetectionResult, "./2Ridge_Detection.ppm");
    std::cout << "Ridge Detection Saved!" << std::endl;

    BitmapImage ridgeDetectionSResult = ridgeDetectionS.processImage(image);
    std::cout << "Ridge Detection Strong Performed!" << std::endl;
    netpbmIO.saveImage(ridgeDetectionSResult, "./3Ridge_DetectionS.ppm");
    std::cout << "Ridge Detection Strong Saved!" << std::endl;

    BitmapImage sharpenResult = sharpen.processImage(image);
    std::cout << "Sharpen Performed!" << std::endl;
    netpbmIO.saveImage(sharpenResult, "./4Sharpen.ppm");
    std::cout << "Sharpen Saved!" << std::endl;

    BitmapImage boxBlurResult = boxBlur.processImage(image);
    std::cout << "Box Blur Performed!" << std::endl;
    netpbmIO.saveImage(boxBlurResult, "./5Box_Blur.ppm");
    std::cout << "Box Blur Saved!" << std::endl;

    BitmapImage gaussianBlur3Result = gaussianBlur3.processImage(image);
    std::cout << "Gaussian Blur 3x3 Performed!" << std::endl;
    netpbmIO.saveImage(gaussianBlur3Result, "./6Gaussian_Blur3.ppm");
    std::cout << "Gaussian Blur 3x3 Saved!" << std::endl;

    BitmapImage gaussianBlur5Result = gaussianBlur5.processImage(image);
    std::cout << "Gaussian Blur 5x5 Performed!" << std::endl;
    netpbmIO.saveImage(gaussianBlur5Result, "./7Gaussian_Blur5.ppm");
    std::cout << "Gaussian Blur 5x5 Saved!" << std::endl;

    return 0;
}
