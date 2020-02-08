//
// Created by zzh24 on 1/18/2020.
//
// demo for unit testing purpose // will never use it
#ifndef TESTTEST_SRC_AST_AST_H_
#define TESTTEST_SRC_AST_AST_H_
#include <iostream>
#include <memory>
#include <string>
#include <vector>
class AST {
public:
  AST(std::string val) : val_(std::move(val)) {}
  std::string getName();

private:
  std::string val_;
};

#endif // TESTTEST_SRC_AST_AST_H_
