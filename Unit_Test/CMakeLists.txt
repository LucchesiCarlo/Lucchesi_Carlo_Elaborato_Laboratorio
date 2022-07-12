cmake_minimum_required(VERSION 3.22)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runningTests.cpp ../BitmapImage.cpp ../BitmapImage.h BitImmageSuite.cpp BitmapImageTests.cpp ../KernelProcessing.cpp ../KernelProcessing.h KernelProcessingSuite.cpp KernelProcessTests.cpp ActualKernelProcessing.cpp ../ImageSaver.h ../ImageLoader.h ../NetpbmLoader.cpp ../NetpbmLoader.h NetpbmLoaderSuite.cpp ../NetpbmSaver.cpp ../NetpbmSaver.h NetpbmSaverSuite.cpp)
add_executable(runUnitTesting ${TEST_SOURCE_FILES})
target_link_libraries(runUnitTesting gtest gtest_main)