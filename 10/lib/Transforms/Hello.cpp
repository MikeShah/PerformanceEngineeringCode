//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "hello"

STATISTIC(HelloCounter, "Counts number of functions greeted");

namespace {
  // Hello - The first implementation, without getAnalysisUsage.
  struct Hello : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    Hello() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      ++HelloCounter;
      errs() << "Hello from Mike: ";
      errs().write_escaped(F.getName()) << '\n';
      return false;
    }
  };
}

char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "Hello World Pass");

namespace {
  // Hello2 - The second implementation with getAnalysisUsage implemented.
  struct Hello2 : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    Hello2() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      unsigned int basicBlocksCount = 0;
      unsigned int instructionCount = 0;
      // Iterate through every Basic Block(BB) in a function.
      for(BasicBlock &bb: F){
        ++basicBlocksCount;
        for(Instruction &i: bb){
            ++instructionCount;
        }
      }

      errs().write_escaped(F.getName()) << "\n\tBasic Blocks:" 
                                        << basicBlocksCount
                                        << "\n\tInstructions:"
                                        << instructionCount
                                        << "\n";

      return false;
    }

    // We don't modify the program, so we preserve all analyses.
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
    }
  };
}

char Hello2::ID = 0;
static RegisterPass<Hello2> Y("hello2", "Hello World Pass (with getAnalysisUsage implemented)");

#include "llvm/IR/Instructions.h"
namespace {
  // Hello3 - The second implementation with getAnalysisUsage implemented.
  struct Hello3 : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    Hello3() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      // Iterate through every Basic Block(BB) in a function.
      for(BasicBlock &bb: F){
        for(Instruction &i: bb){
           if(CallInst* callInst = dyn_cast<CallInst>(&i)){
                if(Function* calledFunction = callInst->getCalledFunction()){
                    errs() << "\tDirection call to function: " << calledFunction->getName() << " from " << F.getName() << "\n";
                }
           }
        }
      }


      return false;
    }

    // We don't modify the program, so we preserve all analyses.
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
    }
  };
}

char Hello3::ID = 0;
static RegisterPass<Hello3> Z("hello3", "Show direct function calls");
