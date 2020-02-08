//
// Created by zzh24 on 2/2/2020.
//

#include "BinaryExprAST.h"
#include "VariableExprAST.h"
using llvm::IRBuilder;
namespace AST{
Value *BinaryExprAST::codegen() {
  Value *leftVal = left_->codegen();
  Value *rightVal = right_->codegen();
  if(!leftVal || !rightVal) return nullptr;
  IRBuilder<> builder(*context_);
  switch(op_){
  case '+':
    return builder.CreateFAdd(leftVal, rightVal, "addtmp");
  case '-':
    return builder.CreateFSub(leftVal, rightVal, "subtmp");
  case '*':
    return builder.CreateFMul(leftVal, rightVal, "multmp");
  case '/':
    return builder.CreateFDiv(leftVal, rightVal, "div");
  default:
    LOG(ERROR) << "not implemented binary operation";
    return nullptr;
  }
}
} // AST