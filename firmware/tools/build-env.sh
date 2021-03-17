#!/bin/bash

export REPOROOT="$(dirname "$(dirname "$(readlink -fm "$0")")")"
export SOURCEROOT="$REPOROOT/src"
export BUILDDIR="$REPOROOT/build"

alias build="$REPOROOT/tools/build.py"
alias clean="$REPOROOT/tools/clean.py"