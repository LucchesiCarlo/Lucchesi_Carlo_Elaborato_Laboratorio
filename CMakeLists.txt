cmake_minimum_required(VERSION 3.22)
project(Lucchesi_Carlo_Elaborato_Laboratorio)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(Unit_Test)

add_executable(Lucchesi_Carlo_Elaborato_Laboratorio main.cpp BitmapImage.cpp BitmapImage.h KernelProcessing.cpp KernelProcessing.h ImageIO.h NetpbmIO.cpp NetpbmIO.h)
