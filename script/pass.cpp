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
#include <vector>
#include <set> 
using namespace llvm ;

bool
StaticTaintAnalysisPass::doInitialization(Module &M) {

    // init taintSrc
    initTaintSource(M) ;

    std::vector<Value *> visitedStack ;

    // main analysis
    unsigned i = 0 ; 
    while ( !taintSource.empty() ) {
        // run taint analysis for taintRound
        std::vector<Value *> taintRound = taintSource ;
        for ( Value* v: taintSource ) {
            taintVisited.insert(v) ;
        }
        taintSource.clear() ;

        taintAnalysisMain(M, taintRound) ; 
        for ( Value* v: taintRound ) { 
            errs() << "[TAINT_ROUND_" << i << "]: " ;
            errs() << *v << "\n" ; 
        }
        i ++ ; 
        

    }
    return false;
}


void
StaticTaintAnalysisPass::taintAnalysisMain(Module &M, std::vector<Value*> tainted) {

    std::set<BasicBlock*> fullyTaintBlocks = std::set<BasicBlock*>() ;

    for ( auto pF = M.begin(); pF != M.end() ; pF ++) {

        // interprocedural taint analysis: taintDerived<Value>
        std::set<Value*> taintDerived = std::set<Value*>();
        for ( Value* v: tainted ) {
            // TODO: optimize
            taintDerived.insert(v) ;
        }
        //errs() << "\n\n" ;
        //errs() << "#########################################\n" ;
        //errs() << pF->getName() << "()                      \n" ;
        //errs() << "#########################################\n" ;

        for( auto pB = pF->begin(); pB!= pF->end(); pB ++) {
            
            bool fullyTainted = fullyTaintBlocks.find(&*pB)!=fullyTaintBlocks.end() ;
            // propagate tainted values 
            for ( auto pI = pB->begin(); pI !=pB->end(); pI ++ ) {
                Instruction* ins = &*pI ;

                // if any of operand tainted
                bool isTaintedIns = false;
                for ( unsigned i = 0; i < pI->getNumOperands(); ++i ) {
                    Value* op = pI->getOperand(i);
                    if ( taintDerived.find(op) != taintDerived.end() ) {
                        isTaintedIns = true; 
                        break ;
                    }
                }
#ifdef DEBUG
                errs() << "[ " << isTaintedIns << " ] " ;
                errs() << *ins << "\n" ;
#endif 
                
                if ( isTaintedIns ) {
                    if (auto store = dyn_cast<StoreInst>(ins) ) {
                        Value* dst = store->getOperand(1) ;
                        // errs() << "taint store : " << *dst << "\n" ;
                        if ( auto alloca = dyn_cast<AllocaInst>(dst) ) {
                            taintDerived.insert(alloca); 
                        } else if ( auto gv = dyn_cast<GlobalVariable>(dst) ) {
                            if ( taintVisited.find(gv) == taintVisited.end() ) {
                                taintSource.push_back(gv) ;
                            }      
                        } else {
                            errs() << "[DEBUG] either AllocaInst or GlobalVariable\t" ;
                            errs() << *dst << "\n" ;
                        }
                    } else {
                        // errs() << *ins << " just Tainted!\n" ; 
                        taintDerived.insert(ins); 
                    } 
                }
                if ( fullyTainted ) {
                    if (auto store = dyn_cast<StoreInst>(ins) ) {
                        Value* dst = store->getOperand(1) ;
                        // errs() << "taint store : " << *dst << "\n" ;
                        if ( auto alloca = dyn_cast<AllocaInst>(dst) ) {
                            taintDerived.insert(alloca); 
                        } else if ( auto gv = dyn_cast<GlobalVariable>(dst) ) {
                            if ( taintVisited.find(gv) == taintVisited.end() ) {
                                taintSource.push_back(gv) ;
                            }      
                        } else {
                            errs() << "[DEBUG] either AllocaInst or GlobalVariable\t" ;
                            errs() << *dst << "\n" ;
                        }
                        
                    
                    }

                }
            } // for each Instruction
            

            // if the terminator is tainted: 
            //   fullyTaint the successor basic block
            Instruction* termIns = pB->getTerminator() ;
            if ( !termIns ) continue ;

            // if the terminator is tainted 
            if ( taintDerived.find(termIns) != taintDerived.end() ) {
                
                // taint all the successor block
                if ( auto br = dyn_cast<BranchInst>(termIns) ) {
                    for ( unsigned i = 0; i < br->getNumSuccessors(); ++i ) {
                        BasicBlock* successor = br->getSuccessor(i) ;
                        fullyTaintBlocks.insert(successor) ;            
                    } 
                } else if ( auto swit = dyn_cast<SwitchInst>(termIns) ) {
                    for ( unsigned i = 0; i < swit->getNumSuccessors(); ++i ) {
                        BasicBlock* successor = swit->getSuccessor(i) ;
                        fullyTaintBlocks.insert(successor) ;
                    }
                }
            }
                
        } // for each BasicBlock
        
#ifdef DEBUG
        errs() << "\n\n";
        errs() << "==================================\n" ; 
        errs() << pF->getName() << "()         ================\n" ;
        errs() << "==================================\n" ; 
        for ( auto pB = pF->begin(); pB!=pF->end(); pB ++) {
            Instruction* termina = pB->getTerminator() ;

            for ( auto pI=pB->begin(); pI!=pB->end(); pI++ ) {
                bool tainted = taintDerived.find(&*pI) != taintDerived.end() ;
                errs() << "[ " << tainted << " ]\t" << *pI ;
                if ( termina && &*pI == termina ) 
                    errs() << "\t<- terminator\n" ;
                else 
                    errs() << "\n";
            }
        } // for each BasicBlock debug 
#endif 
    
    } // for each Function
}

bool
StaticTaintAnalysisPass::runOnFunction(Function &F) {

    SmallVector<Value*, 0> taint_derived ;




    return false ;
}


void
StaticTaintAnalysisPass::taintGlobalVariable(Instruction *ins) {
    // if store to a global
    if ( auto store = dyn_cast<StoreInst>(ins) ) {
        Value* dst = store->getOperand(1); 
        if ( auto global = dyn_cast<GlobalVariable>(dst) ) {
            if ( taintVisited.find(global) == taintVisited.end() ) {
                errs() << "propagate globals\n" ;
                taintSource.push_back(global) ;
            }
        }
    }

}


bool
StaticTaintAnalysisPass::isTainted(Instruction *ins, SmallVector<Value *, 0> &v) {
    for ( auto it = taintSource.begin(); it != taintSource.end(); ++it ) {
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
StaticTaintAnalysisPass::initTaintSource(Module& M) {
    for ( auto pF = M.begin(); pF != M.end() ; ++ pF )  {
        for ( auto pB = pF->begin(); pB != pF->end(); ++pB ) {
            for ( auto pI = pB->begin(); pI != pB->end(); ++pI) {
                Instruction *pi = &(*pI) ;
                if ( isTaintSource(pi) ) {
                    taintSource.push_back(pi);
                }
            }       
        }
    }
}

bool
StaticTaintAnalysisPass::isTaintSource(Instruction* ins) {
    // true if it's something random
    if ( isRandom(ins) ) 
        return true ;

    // true if it's related to concurrency
    for ( unsigned i = 0; i < ins->getNumOperands(); ++i ) {
        Value* op = ins->getOperand(i) ;
        if ( hasName("WORLD", op) ) {
            return true ;
        }
    }

    return false ; 
}

bool
StaticTaintAnalysisPass::isRandom(Instruction* ins) {
    if ( auto callinst = dyn_cast<CallInst>(ins) ) {
        Value* func = callinst->getOperand(0) ;
        StringRef func_name = func->getName() ;
        return func_name.contains("rand") ; 
    }
    return false; 
}


bool
StaticTaintAnalysisPass::hasName(StringRef pattern, Value *val) {
    StringRef s = val->getName() ;
    return s.contains(pattern) ;
}



//////////////////////
// Pass Registration
///////////////////
char StaticTaintAnalysisPass::ID = 0;
static RegisterPass<StaticTaintAnalysisPass> X("Backward Slicing", 
        "backward slicing for tainted input", 
        false, false ) ;

static RegisterStandardPasses Y(
        PassManagerBuilder::EP_EarlyAsPossible, 
        [](const PassManagerBuilder &Builder, 
            legacy::PassManagerBase &PM) {
        PM.add(new StaticTaintAnalysisPass()) ;
        }
        );
