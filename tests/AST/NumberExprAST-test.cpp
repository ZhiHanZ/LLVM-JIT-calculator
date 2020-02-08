//
// Created by zzh24 on 1/18/2020.
//reference to llvm/unittests/IR/ConstantsTest.cpp
//
#include "gtest/gtest.h"
#include "AST/NumberExprAST.h"
#include "AST/VariableExprAST.h"
#include "glog/logging.h"
using AST::NumberExprAST;
using AST::VariableExprAST;
using llvm::LLVMContext;
using llvm::raw_ostream;
using llvm::outs;
using llvm::ConstantExpr;
using llvm::Value;
using std::string;
using llvm::AllocaInst;
using llvm::IRBuilder;
using llvm::Type;
using std::map;
//using three value 0, 1, -1 and test their sum, sub, mul and div
TEST(NumberExprASTTest, ConstantTests) {
//arrange
//act
//assert
  auto TheContext = std::make_shared<LLVMContext>();
  auto builder = std::make_unique<IRBuilder<>>(*TheContext);
  auto one = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 1));
  auto one_val = one->codegen();
  auto zero = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 0));
  auto zero_val = zero->codegen();
  auto minus_one = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, -1.0));
  auto minus_one_val = minus_one->codegen();
//  EXPECT_EQ(zero_val, ConstantExpr::getAdd(minus_one_val, one_val));
  outs() << *minus_one_val << "\n";
  outs() << *minus_one_val->getType() << "\n";
  auto NamedValue = std::make_shared<std::map<std::string, AllocaInst*>>();
  std::string varName {"a"};
  LOG(INFO) << "???";
  auto a_var = std::unique_ptr<VariableExprAST>(new VariableExprAST(NamedValue, builder.get(), varName));
  LOG(INFO) << "???";
//  auto a_var_val = a_var->codegen();
//  EXPECT_EQ(nullptr, a_var_val);
//  (*NamedValue)["a"] = one_val;
//  a_var_val = a_var->codegen();  // this operation may be unsafe!
//  EXPECT_EQ(one_val, a_var_val);
}