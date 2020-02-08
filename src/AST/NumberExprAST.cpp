//
// Created by zzh24 on 1/18/2020.
//

#include "NumberExprAST.h"
namespace AST{
//generate IEEE float64 value as constant in context_
//value should be val_ and type is ConstantFP
   Value* NumberExprAST::codegen(){
     return ConstantFP::get(*context_, APFloat(val_));
   }
}  // AST