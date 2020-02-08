//
// Created by zzh24 on 2/3/2020.
//

#ifndef TESTTEST_SRC_AST_PROTOTYPEAST_H_
#define TESTTEST_SRC_AST_PROTOTYPEAST_H_
#include <string>
#include <vector>
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include <memory>
#include <iostream>
using llvm::Module;
using llvm::Function;
using llvm::Type;
using llvm::FunctionType;
using llvm::LLVMContext;

using llvm::outs;
namespace AST{
//the main goal of this AST is to represent the functional signature of a function ie double (double, double)
class PrototypeAST {
public:
  //context: the llvm context we need to store global variables,
  //nameL fucntion name
  // args: function arguments
  // module: IR module used in function build
  PrototypeAST(std::shared_ptr<LLVMContext> context, const std::string &name,
                std::vector<std::string> args, Module* module):
                context_(context), name_(name), args_(args), currentModule_(module){}
  //apppend a new function with name_ defined into Module and return the registed function
  Function* codegen();
  //return function name in current prototype, the id should be unique
  const std::string& GetName() const {return name_;}
  const std::vector<std::string>& GetArgs() const {return args_;}
private:
  std::string name_;
  std::vector<std::string> args_;
  Module* currentModule_;
  std::shared_ptr<LLVMContext> context_;
};
}  // namespace AST

#endif // TESTTEST_SRC_AST_PROTOTYPEAST_H_
