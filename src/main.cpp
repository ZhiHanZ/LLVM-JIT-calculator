//
// Created by zzh24 on 1/18/2020.
//
#include "AST/NumberExprAST.h"
#include "AST/FunctionAST.h"
#include "AST/CallExprAST.h"
#include <assert.h>
#include "AST/PrototypeAST.h"
#include "AST/BinaryExprAST.h"
#include "AST/VariableExprAST.h"
#include "Engine/NaiveJIT.h" // the demo engine used in Kaleidoscope JIT
#include "glog/logging.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/AsmParser/Parser.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetRegistry.h"
#include "gflags/gflags.h"
#include "include/operators.h"
#include <unordered_map>
#include <iostream>
using AST::NumberExprAST;
using AST::VariableExprAST;
using AST::BinaryExprAST;
using AST::PrototypeAST;
using AST::FunctionAST;
using AST::ExprAST;
using utils::BinaryOperators ;
using llvm::LLVMContext;
using llvm::raw_ostream;
using llvm::outs;
using llvm::ConstantExpr;
using llvm::Value;
using llvm::errs;
using llvm::AllocaInst;
using llvm::orc::KaleidoscopeJIT;
extern int yyparse();
DEFINE_bool(interactive_mode, true, "Include 'advanced' options in the menu listing");
//auto NamedValue = std::make_shared<std::map<std::string, Value*>>();
//auto FunctionProto = std::make_shared<std::map<std::string, std::unique_ptr<PrototypeAST>>>();
auto NamedValueDummy = std::unordered_map<std::string, double>();
std::unordered_map<std::string, BinaryOperators > symbolMap;
static const std::string addName {"_Z3addRKdS0_"};
static const std::string minusName {"_Z5minusRKdS0_"};
static const std::string mulName{"_Z3mulRKdS0_"};
static const std::string divName {"_Z3divRKdS0_"};



int main(int argc, char *argv[]) {
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();
  google::ParseCommandLineFlags(&argc, &argv, true);
  LLVMContext C;
  llvm::SMDiagnostic Err;
  auto TheJIT = std::make_shared<KaleidoscopeJIT>();
  const std::string fileName {"../../cache/BasicOperators.ll"};
  std::unique_ptr<Module> M = llvm::parseAssemblyFile(fileName, Err, C);
  auto handler = TheJIT->addModule(std::move(M));
  auto addExprSymbol = TheJIT->findSymbol(addName);
  double (*add)(const double&, const double&) = (double (*)(const double&, const double&))(intptr_t)cantFail(addExprSymbol.getAddress());
  auto minusExprSymbol = TheJIT->findSymbol(minusName);
  double (*minus)(const double&, const double&) = (double (*)(const double&, const double&))(intptr_t)cantFail(minusExprSymbol.getAddress());
  auto mulExprSymbol = TheJIT->findSymbol(mulName);
  double (*mul)(const double&, const double&) = (double (*)(const double&, const double&))(intptr_t)cantFail(mulExprSymbol.getAddress());
  auto divExprSymbol = TheJIT->findSymbol(divName);
  double (*__div__)(const double&, const double&) = (double (*)(const double&, const double&))(intptr_t)cantFail(divExprSymbol.getAddress());
  symbolMap.emplace(addName, add);
  symbolMap.emplace(minusName, minus);
  symbolMap.emplace(mulName, mul);
  symbolMap.emplace(divName, __div__);
  if(FLAGS_interactive_mode){
    LOG(INFO) << "file";
    LOG(INFO) << symbolMap[addName](1,2);
  }
  std::cout << "[IN] <-";
  yyparse();
  return 0;
}