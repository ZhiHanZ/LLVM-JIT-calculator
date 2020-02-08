//
// Created by zzh24 on 1/18/2020.
//

#ifndef TESTTEST_SRC_AST_VARIABLEEXPRAST_H_
#define TESTTEST_SRC_AST_VARIABLEEXPRAST_H_
#include "ExprAST.h"
#include <glog/logging.h>

using llvm::Value;
using llvm::AllocaInst;
using llvm::IRBuilder;
using std::string;
namespace AST {
/// VariableExprAST - Expression class for referencing a variable, like "a".
  class VariableExprAST :public ExprAST{
  public:
    //
    //
    VariableExprAST(std::shared_ptr<std::map<std::string, AllocaInst*>> namedVal, IRBuilder<>* builder, std::string name) : namedVal_(namedVal), builder_(builder), name_(std::move(name)) {}
    const std::string &getName() const {return name_;}
    Value* codegen() override;

  private:
    std::string name_; //define the name for a var
    //mapped value from global map
    IRBuilder<>* builder_;
    std::shared_ptr<std::map<std::string, AllocaInst*>> namedVal_;
  };
}  // AST


#endif // TESTTEST_SRC_AST_VARIABLEEXPRAST_H_
