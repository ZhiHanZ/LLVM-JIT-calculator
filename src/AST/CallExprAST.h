//
// Created by zzh24 on 2/3/2020.
//

#ifndef TESTTEST_SRC_AST_CALLEXPRAST_H_
#define TESTTEST_SRC_AST_CALLEXPRAST_H_
#include "ExprAST.h"
#include <memory>
namespace AST{
/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
public:
  CallExprAST(const std::string &callee,
              std::vector<std::unique_ptr<ExprAST>> args)
      : callee_(callee), args_(std::move(args)) {}
  Value *codegen() override;
private:
  std::string callee_;
  std::vector<std::unique_ptr<ExprAST>> args_;
};
} //  AST
#endif // TESTTEST_SRC_AST_CALLEXPRAST_H_
