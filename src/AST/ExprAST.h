//
// Created by zzh24 on 1/18/2020.
//

#ifndef TESTTEST_SRC_AST_EXPRAST_H_
#define TESTTEST_SRC_AST_EXPRAST_H_
#include "llvm/ADT/STLExtras.h"
#include "llvm/Analysis/BasicAliasAnalysis.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include <map>
#include <string>
#include <vector>
using llvm::Value;
namespace AST {
//pure virtual class define ir code generation interface for LLVM IR code
class ExprAST {
public:
  ExprAST() {}
  virtual ~ExprAST() {}
  virtual Value *codegen() = 0;
};
} // namespace AST

#endif // TESTTEST_SRC_AST_EXPRAST_H_
