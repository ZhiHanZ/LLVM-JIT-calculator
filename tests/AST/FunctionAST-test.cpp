//
// Created by zzh24 on 2/2/2020.
//
#include "gtest/gtest.h"
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
using AST::NumberExprAST;
using AST::VariableExprAST;
using AST::BinaryExprAST;
using AST::PrototypeAST;
using AST::FunctionAST;
using AST::ExprAST;
using llvm::LLVMContext;
using llvm::raw_ostream;
using llvm::outs;
using llvm::ConstantExpr;
using llvm::Value;
using llvm::errs;
using llvm::AllocaInst;
using llvm::orc::KaleidoscopeJIT;

//create a new function __anon_expr() return 1 + 1;
TEST(FunctionAST, pipelineTest) {
  //parse proto
  //parse expression
  //make_unique function AST
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();
  auto TheContext = std::make_shared<LLVMContext>();
  auto TheJIT = std::make_unique<KaleidoscopeJIT>(); // i
  auto pairedModule =utils::InitModuleAndPassManager(TheContext.get(), TheJIT.get());
  auto TheModule = std::move(pairedModule.first);
  auto TheFPM = std::move(pairedModule.second);
  auto named_value = std::make_shared<std::map<std::string, AllocaInst *>>();
  auto function_proto = std::make_shared<std::map<std::string, std::unique_ptr<PrototypeAST>>>();
  ASSERT_NE(TheModule, nullptr);
  std::string functionName = std::string(" __anon_expr");
  auto proto = std::unique_ptr<PrototypeAST>(new PrototypeAST(TheContext, functionName, std::vector<std::string>(), TheModule.get()));
 //create body
  auto one = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 1));
  auto one1 = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 1));
  std::unique_ptr<ExprAST> expression = std::unique_ptr<BinaryExprAST>(new BinaryExprAST(TheContext, '+', std::move(one), std::move(one1)));
  ASSERT_EQ(proto->GetName(), " __anon_expr");
  auto funcAST = std::make_unique<FunctionAST>(TheContext, TheModule.get(), TheFPM.get(), named_value, function_proto, std::move(proto), std::move(expression));
  llvm::verifyFunction(*funcAST->codegen());
  ASSERT_NE(funcAST, nullptr);
  Function* curr = TheModule->getFunction(functionName);
  ASSERT_NE(curr, nullptr);
  auto handler = TheJIT->addModule(std::move(TheModule));
  // Search the JIT for the __anon_expr symbol.
  auto ExprSymbol = TheJIT->findSymbol(functionName);
  assert(ExprSymbol && "Function not found");
  double (*FP)() = (double (*)())(intptr_t)cantFail(ExprSymbol.getAddress());
  ASSERT_EQ(FP(), 2.0);
}
//using LLVM IR generated from clang++ -S -emit-llvm as Module String then add it to llvm jit
//test function double add(double x) x = x + 2; return x;

TEST(FunctionAST, DummyfuncTest){
  //resource https://github.com/llvm-mirror/llvm/blob/master/unittests/IR/ValueTest.cpp UsedIn Basic Test
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();
  LLVMContext C;
  auto TheJIT = std::make_shared<KaleidoscopeJIT>(); // i
  //generated from LLVM IR add(x) x = x + 2; return x;
  const char* ModuleString = "define dso_local double @add(double) #0 {\n"
                             "  %2 = alloca double, align 8\n"
                             "  store double %0, double* %2, align 8\n"
                             "  %3 = load double, double* %2, align 8\n"
                             "  %4 = fadd double %3, 2.000000e+00\n"
                             "  store double %4, double* %2, align 8\n"
                             "  %5 = load double, double* %2, align 8\n"
                             "  ret double %5\n"
                             "}\n";
  llvm::SMDiagnostic Err;
  std::unique_ptr<Module> M = llvm::parseAssemblyString(ModuleString, Err, C);
  Function* add2 = M->getFunction("add");
  ASSERT_NE(add2, nullptr);
  std::string funcName {"add"};
  auto handler = TheJIT->addModule(std::move(M));
  auto ExprSymbol = TheJIT->findSymbol(funcName);
  assert(ExprSymbol && "Function not found");
  double (*FP)(double) = (double (*)(double))(intptr_t)cantFail(ExprSymbol.getAddress());
  ASSERT_EQ(FP(2.8), 4.8);
  ASSERT_EQ(FP(1.7), 3.7);
  ASSERT_EQ(FP(-3), -1);
}

//using LLVM IR generated from clang++ -S -emit-llvm as Module String then add it to llvm jit
TEST(FunctionAST, addfuncTest){
  //resource https://github.com/llvm-mirror/llvm/blob/master/unittests/IR/ValueTest.cpp UsedIn Basic Test
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();
  LLVMContext C;
  auto TheJIT = std::make_shared<KaleidoscopeJIT>(); // i
  //generated from LLVM IR
  // double add(const double& x, dconst double& y) return x + y;
  const char* ModuleString = "define dso_local double @_Z3addRKdS0_(double* dereferenceable(8), double* dereferenceable(8)) #0 {\n"
      "  %3 = alloca double*, align 8\n"
      "  %4 = alloca double*, align 8\n"
      "  store double* %0, double** %3, align 8\n"
      "  store double* %1, double** %4, align 8\n"
      "  %5 = load double*, double** %3, align 8\n"
      "  %6 = load double, double* %5, align 8\n"
      "  %7 = load double*, double** %4, align 8\n"
      "  %8 = load double, double* %7, align 8\n"
      "  %9 = fadd double %6, %8\n"
      "  ret double %9\n"
      "}\n";
  std::string funcName {"_Z3addRKdS0_"};
  llvm::SMDiagnostic Err;
  std::unique_ptr<Module> M = llvm::parseAssemblyString(ModuleString, Err, C);
  Function* add = M->getFunction(funcName);
  ASSERT_NE(add, nullptr);
  auto handler = TheJIT->addModule(std::move(M));
  auto ExprSymbol = TheJIT->findSymbol(funcName);
  assert(ExprSymbol && "Function not found");
  double (*FP)(const double&, const double&) = (double (*)(const double&, const double&))(intptr_t)cantFail(ExprSymbol.getAddress());
  ASSERT_EQ(FP(2.8, 1.1), 3.9);
  ASSERT_EQ(FP(1.7, 1.1), 2.8);
  ASSERT_EQ(FP(-1.6, 1.1), -0.5);
}
//read LLVM from cache and use the function provided
TEST(FunctionAST, cachedfuncTest){
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();
  LLVMContext C;
  auto TheJIT = std::make_shared<KaleidoscopeJIT>(); // i
  const std::string addName {"_Z3addRKdS0_"};
  const std::string minusName {"_Z5minusRKdS0_"};
  const std::string mulName{"_Z3mulRKdS0_"};
  const std::string divName {"_Z3divRKdS0_"};
  llvm::SMDiagnostic Err;
  const std::string fileName {"../../cache/BasicOperators.ll"};
  std::unique_ptr<Module> M = llvm::parseAssemblyFile(fileName, Err, C);
  auto handler = TheJIT->addModule(std::move(M));
  auto addExprSymbol = TheJIT->findSymbol(addName);
  assert(addExprSymbol && "Function not found");
  double (*add)(const double&, const double&) = (double (*)(const double&, const double&))(intptr_t)cantFail(addExprSymbol.getAddress());
  EXPECT_EQ(add(2.8, 1.1), 3.9);
  EXPECT_EQ(add(1.7, 1.1), 2.8);
  EXPECT_EQ(add(-1.6, 1.1), -0.5);
  auto minusExprSymbol = TheJIT->findSymbol(minusName);
  assert(minusExprSymbol && "Function not found");
  double (*minus)(const double&, const double&) = (double (*)(const double&, const double&))(intptr_t)cantFail(minusExprSymbol.getAddress());
  EXPECT_EQ(minus(-1.6, 1.1), -2.7);
  auto mulExprSymbol = TheJIT->findSymbol(mulName);
  assert(mulExprSymbol && "Function not found");
  double (*mul)(const double&, const double&) = (double (*)(const double&, const double&))(intptr_t)cantFail(mulExprSymbol.getAddress());
  EXPECT_EQ(mul(2.8, 2), 5.6);
  EXPECT_EQ(mul(1.7, -1), -1.7);
  EXPECT_EQ(mul(2, 1.5), 3);
  auto divExprSymbol = TheJIT->findSymbol(divName);
  assert(divExprSymbol && "Function not found");
  double (*div)(const double&, const double&) = (double (*)(const double&, const double&))(intptr_t)cantFail(divExprSymbol.getAddress());
  EXPECT_EQ(div(2.8, 2), 1.4);
  EXPECT_EQ(div(1.7, -1), -1.7);
  EXPECT_EQ(div(2, 2), 1);
}
//create several functions in given module and run
// create a function named foo(double a) : double {a = a + 2; return a;} in current stack
//TODO the allignments exhibit segmentation fault and need to be fixed
TEST(FunctionAST, MutateArguTest){
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();
  auto TheContext = std::make_shared<LLVMContext>();
  auto TheJIT = std::make_shared<KaleidoscopeJIT>(); // i
  auto pairedModule =utils::InitModuleAndPassManager(TheContext.get(), TheJIT.get());
  auto TheModule = std::move(pairedModule.first);
  auto TheFPM = std::move(pairedModule.second);
  auto named_value = std::make_shared<std::map<std::string, AllocaInst *>>();
  auto function_proto = std::make_shared<std::map<std::string, std::unique_ptr<PrototypeAST>>>();
  std::string functionName = std::string("foo");
  std::vector<std::string> args {"a"};
  auto proto = std::unique_ptr<PrototypeAST>(new PrototypeAST(TheContext, functionName, args, TheModule.get()));
  auto args_ = proto->GetArgs();
  ASSERT_EQ(args, args_);
  //create body
  auto two = std::unique_ptr<NumberExprAST>(new NumberExprAST(TheContext, 2.0));
  IRBuilder<> builder(*TheContext); //check it.
  auto var = std::make_unique<VariableExprAST>(named_value, &builder, args[0]);
//  auto alloca = (*named_value)[args[0]];
//  ASSERT_NE(alloca, nullptr);
  std::unique_ptr<ExprAST> expression = std::unique_ptr<BinaryExprAST>(new BinaryExprAST(TheContext, '+', std::move(var), std::move(two)));
  auto funcAST = std::make_unique<FunctionAST>(TheContext, TheModule.get(), TheFPM.get(), named_value, function_proto, std::move(proto), std::move(expression));
  ASSERT_NE(funcAST, nullptr);
  auto *fnIR = funcAST->codegen();
  fnIR->print(errs());
  ASSERT_NE(fnIR, nullptr);
  LOG(INFO) << "???";
  Function* curr = TheModule->getFunction(functionName);
 ASSERT_NE(curr, nullptr);
  outs() << *TheModule;
//  ASSERT_NE(curr, nullptr);
  LOG(INFO) << "???";
  LOG(INFO) << "???";
  ASSERT_NE(TheModule, nullptr);
  ASSERT_NE(TheJIT, nullptr);
  auto handler = TheJIT->addModule(std::move(TheModule));
  LOG(INFO) << "???";
  auto ExprSymbol = TheJIT->findSymbol(functionName);
  assert(ExprSymbol && "Function not found");
}