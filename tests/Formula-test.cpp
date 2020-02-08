//
// Created by zzh24 on 1/18/2020.
//
#include "gtest/gtest.h"
#include "Formula.h"

TEST(blaTest, test1) {
  //arrange
  //act
  //assert
  EXPECT_EQ (Formula::bla (0),  0);
  EXPECT_EQ (Formula::bla (10), 20);
  EXPECT_EQ (Formula::bla (50), 100);
}