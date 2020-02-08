//
// Created by zzh24 on 1/18/2020.
//

#ifndef TESTTEST_SRC_AST_NUMBEREXPRAST_H_
#define TESTTEST_SRC_AST_NUMBEREXPRAST_H_
#include "ExprAST.h"
using llvm::Value;
using llvm::ConstantFP;
using llvm::APFloat;
using llvm::LLVMContext;
namespace AST {
//NumberExprAST class captures the numeric value of the literal as an instance variable.
//Allow compiler to know what the stored numeric value is.
class NumberExprAST : public ExprAST{
public:
  explicit NumberExprAST(std::shared_ptr<LLVMContext> context, double val): context_(context), val_(val) {}
  //register a
  Value *codegen() override;
private:
  double val_; //represent the number stored in NumberExprAST;
  //context_ should be injected through constructor serve as a singleton
  //serve as the owner to core LLVM data structures such as the type and constant value tables
  //here we deliver a APFloat as generated code through context
  std::shared_ptr<LLVMContext> context_;
};
}


#endif // TESTTEST_SRC_AST_NUMBEREXPRAST_H_
