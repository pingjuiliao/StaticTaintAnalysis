#include "pass.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/APFloat.h"
using namespace llvm ;

bool
BackwardSlicingPass::doInitialization(Module &M) {
    initTaintSource(M) ;
    return false;
}

bool
BackwardSlicingPass::runOnFunction(Function &F) {
    
    SmallVector<Value*, 0> taint_derived ;

    // DEBUG: show the tainted sources
    for ( auto it = taint_src.begin(); it != taint_src.end() ; ++it ) 
        errs() << "[TAINT_SRC] " << **it << "\n" ;
    
    // propagate
    for ( auto pB = F.begin() ; pB != F.end(); ++pB ) {
        for ( auto pI = pB->begin(); pI != pB->end(); ++ pI ) {
            Instruction* ins = &*pI ;
            if ( auto c = dyn_cast<Constant>(ins) ) {
                continue;
            }
            if ( isTainted(ins, taint_derived) ) {
                taint_derived.push_back(ins);
            }
             
        }
    }
    
    // show result
    for ( auto it = taint_derived.begin(); it != taint_derived.end(); ++it ) {
        errs() << "[TAINTED] " << **it << "\n" ; 
    }

    return false ;
}

bool
BackwardSlicingPass::isTainted(Instruction *ins, SmallVector<Value *, 0> &v) {
    for ( auto it = taint_src.begin(); it != taint_src.end(); ++it ) {
        if ( ins == *it ) 
            return true ;
    }
    for ( auto it = v.begin(); it != v.end(); ++it ) {
        if ( ins == *it ) 
            return true;
    } 
    return false ;
}


// initialize taint source
void
BackwardSlicingPass::initTaintSource(Module& M) {
    for ( auto pF = M.begin(); pF != M.end() ; ++ pF )  {
        for ( auto pB = pF->begin(); pB != pF->end(); ++pB ) {
            for ( auto pI = pB->begin(); pI != pB->end(); ++pI) {
                Instruction *pi = &(*pI) ;
                if ( isTaintSource(pi) ) {
                    taint_src.push_back(pi);
                }
            }       
        }
    }
}

bool
BackwardSlicingPass::isTaintSource(Instruction* ins) {
    // true if it's something random
    if ( isRandom(ins) ) 
        return true ;
    
    // true if it's related to concurrency
    for ( unsigned i = 0; i < ins->getNumOperands(); ++i ) {
        Value* op = ins->getOperand(i) ;
        if ( hasNameLock(op) ) {
            return true ;
        }
    }

    return false ; 
}

bool
BackwardSlicingPass::isRandom(Instruction* ins) {
    if ( auto callinst = dyn_cast<CallInst>(ins) ) {
        Value* func = callinst->getOperand(0) ;
        StringRef func_name = func->getName() ;
        return func_name.contains("rand") ; 
    }
    return false; 
}


bool
BackwardSlicingPass::hasNameLock(Value *val) {
    StringRef s = val->getName() ;
    return s.contains("lock") ;
}



//////////////////////
// Pass Registration
///////////////////
char BackwardSlicingPass::ID = 0;
static RegisterPass<BackwardSlicingPass> X("Backward Slicing", 
        "backward slicing for tainted input", 
        false, false ) ;

static RegisterStandardPasses Y(
        PassManagerBuilder::EP_EarlyAsPossible, 
        [](const PassManagerBuilder &Builder, 
            legacy::PassManagerBase &PM) {
            PM.add(new BackwardSlicingPass()) ;
        }
        );
