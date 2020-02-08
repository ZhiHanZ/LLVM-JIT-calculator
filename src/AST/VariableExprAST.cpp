//
// Created by zzh24 on 1/18/2020.
//

#include "VariableExprAST.h"
namespace AST{
Value* VariableExprAST::codegen() {
  Value *V = (*namedVal_)[name_];
  if(!V){
    LOG(ERROR) << "Unknown variable name";
  }
  return builder_->CreateLoad(V, name_.c_str());
}
}