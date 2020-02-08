//
// Created by zzh24 on 2/3/2020.
//

#ifndef TESTTEST_SRC_AST_FUNCTIONAST_H_
#define TESTTEST_SRC_AST_FUNCTIONAST_H_
#include "PrototypeAST.h"
#include "ExprAST.h"
#include "include/utils.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include <assert.h>
#include "glog/logging.h"
#include<map>
using utils::GetFunction;
using utils::CreateEntryBlockAlloca;
using llvm::AllocaInst;
using llvm::BasicBlock;
using llvm::IRBuilder;
namespace AST{
/// FunctionAST - This class represents a function definition itself.
class FunctionAST {
public:
  FunctionAST(std::shared_ptr<LLVMContext> context, Module* module, llvm::legacy::FunctionPassManager* fpm,
              std::shared_ptr<std::map<std::string, AllocaInst *>> named_value,
              std::shared_ptr<std::map<std::string, std::unique_ptr<PrototypeAST>>> function_proto,
              std::unique_ptr<PrototypeAST> proto,
              std::unique_ptr<ExprAST> body): context_(context) , currentModule_(module), fpm_(fpm),
              named_value_(named_value), function_proto_(function_proto), proto_(std::move(proto)), body_(std::move(body)){}
  Function* codegen();
private:
  std::unique_ptr<PrototypeAST> proto_; //contains functional signature of a given function
  std::unique_ptr<ExprAST> body_; // contains function bodies;
  std::shared_ptr<std::map<std::string, std::unique_ptr<PrototypeAST>>> function_proto_;
  Module* currentModule_;
  llvm::legacy::FunctionPassManager* fpm_;
  std::shared_ptr<LLVMContext> context_;
  std::shared_ptr<std::map<std::string, AllocaInst *>> named_value_;

};
}


#endif // TESTTEST_SRC_AST_FUNCTIONAST_H_
