//
// Created by carlo on 09/07/22.
//
#include "gtest/gtest.h"
#include "../KernelProcessing.h"

class KernelProcessingSuite : public ::testing::Test {

protected:
    KernelProcessingSuite() : kernel1{Three}, kernel2{kernel1}, kernel3{Five} {};

    KernelProcessing kernel1;
    KernelProcessing kernel2;
    KernelProcessing kernel3;
};


TEST_F(KernelProcessingSuite, TestEqualOperator) {
    ASSERT_TRUE(kernel1 == kernel2) << "kernel1 and kernel2 are different.";
    ASSERT_FALSE(kernel1 == kernel3) << "kernel1 and kernel3 are equal.";
    ASSERT_TRUE(kernel1 == kernel1) << "Auto comparison failed.";
}

TEST_F(KernelProcessingSuite, TestCopyConstructor) {
    ASSERT_EQ(kernel1, kernel2);
    kernel1.setMaskElement(2, 2, 2);
    ASSERT_NE(kernel1.getMaskElement(2, 2), kernel2.getMaskElement(2, 2));
    //Because KernelProcess doesn't have the != operator
}

TEST_F(KernelProcessingSuite, TestAssigment) {
    kernel3 = kernel1;
    ASSERT_EQ(kernel1, kernel3);
    kernel1.setMaskElement(1, 1, 4);
    ASSERT_NE(kernel1.getMaskElement(1, 1), kernel3.getMaskElement(1, 1));
    //Because KernelProcess doesn't have the != operator
    kernel1 = kernel1;
    ASSERT_NO_THROW(kernel1.getMaskElement(1, 1)) << "Auto assigment failed.";
}
