//
// Created by zzh24 on 2/3/2020.
//

#include "FunctionAST.h"
namespace AST{
Function *FunctionAST::codegen() {
  // Transfer ownership of the prototype to the FunctionProtos map, but keep a
  // reference to it for use below.
  auto &signature = *proto_;
  (*function_proto_)[proto_->GetName()] = std::move(proto_);
  Function* currFunc = GetFunction(signature.GetName(), currentModule_, function_proto_);
  assert(currFunc && "func not found in ");
  LOG(INFO) << "func exists";
  if(!currFunc) return nullptr;
  BasicBlock *block = BasicBlock::Create(*context_, "entry", currFunc);
  IRBuilder<> builder(*context_);
  builder.SetInsertPoint(block);
  auto func = currentModule_->getFunction(signature.GetName());
  assert(func && "20 func not found");
  named_value_->clear();
  for(auto &arg: currFunc->args()){
    AllocaInst *alloca = CreateEntryBlockAlloca(currFunc, arg.getName(), context_.get());
    builder.CreateStore(&arg, alloca);
    (*named_value_)[arg.getName()] = alloca;
  }
  if(Value* ret = body_->codegen()){
    builder.CreateRet(ret);
    llvm::verifyFunction(*currFunc);
    fpm_->run(*currFunc);
    return currFunc;
  }
  return nullptr;
}
}  // AST