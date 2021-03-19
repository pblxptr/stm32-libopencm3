#!/bin/bash

export REPO_ROOT="$(dirname "$(dirname "$(readlink -fm "$0")")")"
export BUILD_DIR="$REPO_ROOT/build"
export SOURCE_DIR="$REPO_ROOT/src"
export TEST_DIR="$REPO_ROOT/test"
export EXTERNAL_LIB_DIR="$REPO_ROOT/lib"

### SOLUTIONS ###
export APP_SOLUTION_CMAKE_DIR_PATH="$REPO_ROOT"
export UNITTESTS_SOLUTION_CMAKE_DIR_PATH="$TEST_DIR/unittests"

### ALIASES ####
alias build="$REPO_ROOT/tools/build.py"
alias clean="$REPO_ROOT/tools/clean.py"