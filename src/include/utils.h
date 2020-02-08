//
// Created by zzh24 on 2/3/2020.
//

#ifndef TESTTEST_SRC_INCLUDE_UTILS_H_
#define TESTTEST_SRC_INCLUDE_UTILS_H_
#include "AST/FunctionAST.h"
#include "AST/PrototypeAST.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "Engine/NaiveJIT.h"
#include "AST/FunctionAST.h"
#include "llvm/IR/LegacyPassManager.h"
#include <map>
#include <memory>
#include <string>

using AST::PrototypeAST;
using llvm::Function;
using llvm::Module;
using llvm::LLVMContext;
using llvm::AllocaInst;
using llvm::IRBuilder;
using llvm::orc::KaleidoscopeJIT;
namespace utils{
//get function from module
inline Function* GetFunction(std::string name, Module* module, std::shared_ptr<std::map<std::string, std::unique_ptr<PrototypeAST>>> function_proto){
  //check whether the module has the function name
  if(auto *func = module->getFunction(name)){
    return func;
  }
  // if not check whether we can codegen the function
  auto sign = function_proto->find(name);
  if(sign != function_proto->end()){
    return sign->second->codegen();
  }
  return nullptr;
}
//context: the context in global
//var: variable name
//function: created
inline AllocaInst* CreateEntryBlockAlloca(Function* function, const std::string &var, LLVMContext* context){
  IRBuilder<> tmp(&function->getEntryBlock(), function->getEntryBlock().begin());
  return tmp.CreateAlloca(Type::getDoubleTy(*context), nullptr, var);
}
//dummy method to test RAII
inline std::unique_ptr<int> test(){
  auto test = std::make_unique<int>(7);
  return std::move(test);
}
inline std::pair<std::unique_ptr<Module>,std::unique_ptr<llvm::legacy::FunctionPassManager>>  InitModuleAndPassManager(LLVMContext* context, KaleidoscopeJIT* jit){
  auto module = std::make_unique<Module>("TODO module self name", *context);
  module->setDataLayout(jit->getTargetMachine().createDataLayout());
  auto TheFPM = std::make_unique<llvm::legacy::FunctionPassManager>(module.get());
//  // Promote allocas to registers.
//  TheFPM->add(llvm::createPromoteMemoryToRegisterPass());
//  // Do simple "peephole" optimizations and bit-twiddling optzns.
//  TheFPM->add(llvm::createInstructionCombiningPass());
//  // Reassociate expressions.
//  TheFPM->add(llvm::createReassociatePass());
//  // Eliminate Common SubExpressions.
//  TheFPM->add(llvm::createGVNPass());
//  // Simplify the control flow graph (deleting unreachable blocks, etc).
//  TheFPM->add(llvm::createCFGSimplificationPass());
  TheFPM->doInitialization();
  return std::make_pair(std::move(module), std::move(TheFPM));
}
} //  utils

#endif // TESTTEST_SRC_INCLUDE_UTILS_H_
