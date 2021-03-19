#!/bin/bash

export REPO_ROOT="$(dirname "$(dirname "$(readlink -fm "$0")")")"
export BUILD_DIR="$REPO_ROOT/build"
export SOURCE_DIR="$REPO_ROOT/src"
export TEST_DIR="$REPO_ROOT/test"
export EXTERNAL_LIB_DIR="$REPO_ROOT/lib"
export TOOLS_DIR="$REPO_ROOT/tools"

### SOLUTIONS ###
export APP_SOLUTION_CMAKE_DIR_PATH="$REPO_ROOT"
export UNITTESTS_SOLUTION_CMAKE_DIR_PATH="$TEST_DIR/unittests"

### ALIASES ####
alias build="$REPO_ROOT/tools/build.py"
alias clean="$REPO_ROOT/tools/clean.py"

### BUILD ALIASES ###
alias buildapp='build --solution=app --board=black_pill --toolchain=arm --trace_level=TRACE_LVL_1'
alias run_ts='build --solution=unittests --board=linux --toolchain=x86_64 --trace_level=TRACE_LVL_1 && ./bin/Henhouse-UnitTests'