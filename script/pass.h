#ifndef PASS_H
#define PASS_H

#include "llvm/Pass.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/APFloat.h"
#include <set>
#include <vector>
using namespace llvm;

class StaticTaintAnalysisPass: public FunctionPass {
private:
    std::vector<Value*> taintSource ;
    std::set<Value*> taintVisited ;
    // initialization and its helper functions
    void initTaintSource(Module &M) ;
    bool isTaintSource(Instruction *ins) ;
    bool isRandom(Instruction *ins) ;
    bool hasName(StringRef pattern, Value *val) ;
    // module level analysis
    void taintAnalysisMain(Module &M, std::vector<Value*> tainted) ;
    
    void taintGlobalVariable(Instruction *ins) ;
    // backtrace and its helpers
    bool isTainted(Instruction* ins, SmallVector<Value*, 0> &v) ;
public:
    static char ID ;
    StaticTaintAnalysisPass(): FunctionPass(ID) {}
    virtual bool doInitialization(Module &M) ;
    virtual bool runOnFunction(Function &F) ;
};

#endif
