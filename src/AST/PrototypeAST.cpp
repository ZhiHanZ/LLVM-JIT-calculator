//
// Created by zzh24 on 2/3/2020.
//

#include "PrototypeAST.h"
namespace AST{
//create a function signature on current module
Function *PrototypeAST::codegen() {
  std::vector<Type *> doubleArgs(args_.size(), Type::getDoubleTy(*context_));
  FunctionType* functionType = FunctionType::get(Type::getDoubleTy(*context_), doubleArgs, false);
  Function *function = Function::Create(functionType, Function::ExternalLinkage, name_, currentModule_);
  unsigned idx = 0;
  for(auto dummy : args_){
    std::cout << dummy;
  }
  for(auto &arg: function->args()){
    arg.setName(args_[idx++]);
    outs() << arg.getName();
  }
  return function;
}
}  // AST