//
// Created by zzh24 on 2/2/2020.
//
#include "gtest/gtest.h"
#include "AST/NumberExprAST.h"
#include "AST/VariableExprAST.h"
#include "AST/BinaryExprAST.h"
#include "glog/logging.h"
using AST::NumberExprAST;
using AST::VariableExprAST;
using AST::BinaryExprAST;
using llvm::LLVMContext;
using llvm::raw_ostream;
using llvm::outs;
using llvm::ConstantExpr;
using llvm::Value;
using std::string;
using std::map;
//create a test as  1 + 0
TEST(BinaryExprASTTest, addTest){
  auto TheContext = std::make_shared<LLVMContext>();
  auto one = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 1));
  auto one_val = one->codegen();
  auto zero = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 0));
  auto zero_val = zero->codegen();
  auto addoperation = std::unique_ptr<BinaryExprAST>(new BinaryExprAST(TheContext, '+', std::move(one), std::move(zero)));
  auto add_val = addoperation->codegen();
  EXPECT_EQ(one_val, add_val);
}
//create a test as 2 * -3
TEST(BinaryExprASTTest, mulTest){
  auto TheContext = std::make_shared<LLVMContext>();
  auto two = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 2));
  auto minus_three = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, -3));
  auto minus_six = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, -6));
  auto muloperation = std::unique_ptr<BinaryExprAST>(new BinaryExprAST(TheContext, '*', std::move(two), std::move(minus_three)));
  auto mul_val = muloperation->codegen();
  EXPECT_EQ(minus_six->codegen(), mul_val);
}
//create a test as 1 - 1
TEST(BinaryExprASTTest, minusTest){
  auto TheContext = std::make_shared<LLVMContext>();
  auto one = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 1));
  auto one1 = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 1));
  auto zero = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 0));
  auto minusoperation = std::unique_ptr<BinaryExprAST>(new BinaryExprAST(TheContext, '-', std::move(one), std::move(one1)));
  auto minus_val = minusoperation->codegen();
  EXPECT_EQ(zero->codegen(), minus_val);
}
//create a test as 3/2
TEST(BinaryExprASTTest, divTest){
  auto TheContext = std::make_shared<LLVMContext>();
  auto three = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 3));
  auto two = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 2));
  auto ans = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 1.5));
  auto divoperation = std::unique_ptr<BinaryExprAST>(new BinaryExprAST(TheContext, '/', std::move(three), std::move(two)));
  auto div_val = divoperation->codegen();
  EXPECT_EQ(ans->codegen(),  div_val);
}