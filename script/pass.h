#ifndef PASS_H
#define PASS_H

#include "llvm/Pass.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/APFloat.h"
using namespace llvm;

class BackwardSlicingPass: public FunctionPass {
private:
    SmallVector<Value*, 0> taint_src ;
    // initialization and its helper functions
    void initTaintSource(Module &M) ;
    bool isTaintSource(Instruction *ins) ;
    bool isRandom(Instruction *ins) ;
    bool hasNameLock(Value *val) ;
    // backtrace and its helpers
    bool isTainted(Instruction* ins, SmallVector<Value*, 0> &v) ;
public:
    static char ID ;
    BackwardSlicingPass(): FunctionPass(ID) {}
    virtual bool doInitialization(Module &M) ;
    virtual bool runOnFunction(Function &F) ;
};

#endif
