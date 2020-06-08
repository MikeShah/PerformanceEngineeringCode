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
#include "llvm/IR/Argument.h"
#include "llvm/IR/IRBuilder.h"

#include "llvm/IR/Module.h"
namespace {
  // Hello4 - The second implementation with getAnalysisUsage implemented.
  struct Hello4 : public ModulePass {
    static char ID; // Pass identification, replacement for typeid
    Hello4() : ModulePass(ID) {}

    // Dynamic analysis
    bool runOnModule(Module &M) override {
        // (1) setup our code instrumentation
        setupHooks("@_Z10__initMaini",M);
        // (2)
        Module::FunctionListType &functions = M.getFunctionList();
        for(Module::FunctionListType::iterator FI = functions.begin(), FE = functions.end();  FI != FE; FI++){
            // Debug to see our functions in the module
            // errs() << FI->getName() << "\n";
            
            // Special case to avoid instrumenting 
            // our instrumentation
            if("_Z10__initMaini"==FI->getName()){
                continue;
            }
            if("main"==FI->getName()){
               InstrumentEnterFunction("_Z10__initMaini",*FI, M); 
            }
        }
        
        // We are modifying our source code
        return true;
    }

    void InstrumentEnterFunction(StringRef instrumentingFunctionsName, Function& FunctionToInstrument, Module& M){
        auto &Context = M.getContext();

        Type* voidTy = Type::getVoidTy(Context);
        Type* intTy  = Type::getInt32Ty(Context);

        std::vector<llvm::Type*> params;
        params.push_back(intTy);

        FunctionType* funcTy = FunctionType::get(voidTy, params, false);
        FunctionCallee hook = M.getOrInsertFunction(instrumentingFunctionsName, funcTy);
        // Picking a basic block to instrument(our first one)
        BasicBlock* BB = &FunctionToInstrument.front();
        Instruction* I = &BB->front();
        // Instrument or set the arguments of our instrumenting function
        std::vector<Value*> args;
        for(unsigned int i=0; i < funcTy->getNumParams(); ++i){
            Type* t = funcTy->getParamType(i);
            llvm::Value* foo = 0;
            Value* newValue = ConstantInt::get(t,0x1234);
            args.push_back(newValue);
            errs() << "getNumParams()" << i << "\n";
            
        }
 
        // Insert our hook function that we have created
        // It now has the appropriate function arguments as well
        // for each of its parameters
        IRBuilder<> builder(&BB->front());
        builder.CreateCall(hook,args);  

    }

    void setupHooks(StringRef instrumentingFunctionsName,Module &M){
        auto &Context = M.getContext();
        // Create the stub function
        Type* voidTy = Type::getVoidTy(Context);
        Type* intTy  = Type::getInt32Ty(Context);
        // Create our function with a return value, arguments, and if there aer variable number of args.
        FunctionType* funcTy = FunctionType::get(voidTy, intTy, false);
        Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage)->setName(instrumentingFunctionsName);
    }

  };
}

char Hello4::ID = 0;
static RegisterPass<Hello4> ZZ("hello4", "Dynamic Analysis doing a static instrumentation");


