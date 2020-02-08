//
// Created by zzh24 on 2/2/2020.
//

#ifndef TESTTEST_SRC_AST_BINARYEXPRAST_H_
#define TESTTEST_SRC_AST_BINARYEXPRAST_H_
#include "ExprAST.h"
#include <memory>
using llvm::LLVMContext;
using llvm::Value;
using llvm::IRBuilder;

namespace AST{
class BinaryExprAST : public ExprAST {
public:
  BinaryExprAST(std::shared_ptr<LLVMContext> context, char op, std::unique_ptr<ExprAST> left,
                std::unique_ptr<ExprAST> right): context_(context), op_(op), left_(std::move(left)), right_(std::move(right)) {}
  Value* codegen() override;
private:
  char op_; //operator
  std::unique_ptr<ExprAST> left_, right_;
  std::shared_ptr<LLVMContext> context_;
};
}  // AST


#endif // TESTTEST_SRC_AST_BINARYEXPRAST_H_
