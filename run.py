#!/usr/bin/python3
import os
import sys
import argparse
LLVM_ROOT="./llvm-project-10.0.1/"
CLANG=LLVM_ROOT + "build/bin/clang"
PASS_LIB="./build/libBackwardSlicing.so"
BBID_LIB="./build/libBBID.so"
DEFAULT="./sample/sample/intraprocedural.c"


def error(msg) :
    print(msg)
    print("Compilation Abort!")
    quit()

def main() :
    parser = argparse.ArgumentParser()
    args = parser.parse_args()
    parser.add_argument('-c', '--source',
                        type=str,
                        help='source script',
                        required=False)
    parser.add_argument('-o', '--output',
                        type=str,
                        help='output file',
                        required=False)

    if not os.path.exists(CLANG) :
        error("Please build LLVM-10.0.1 first")

    if not os.path.exists(PASS_LIB) :
        error("Please build pass first")

    args = parser.parse_args()
    cmds = [CLANG,
            "-Xclang",
            "-load",
            "-Xclang",
            PASS_LIB,
            ]

    ## source code
    src = args.source if args.source else DEFAULT
    print(src)
    if not os.path.exists(src) :
        error("No source input")
    cmds += [src]

    ## output
    if args.output :
        if os.path.exists(args.output) :
            error("output file already exists!")
        cmds += ['-o', args.output]

    print("Punch it !")

    cmds += [
            "-Lbuild/script",
            # "-lBBID",
            "-Wl,-rpath,build/script"
            ]

    os.system(' '.join(cmds))


if __name__ == '__main__' :
    main()
