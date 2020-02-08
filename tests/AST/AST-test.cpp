//
// Created by zzh24 on 1/18/2020.
//
//
// Created by zzh24 on 1/18/2020.
//
#include "gtest/gtest.h"
#include "AST/AST.h"

TEST(ASTTest, test1) {
  //arrange
  //act
  //assert
  AST ast("1024");
  EXPECT_EQ (ast.getName(),  "1024");
}