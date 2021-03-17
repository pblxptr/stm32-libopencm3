#!/usr/bin/env python
import argparse
import subprocess 
import shutil
import os

def show_hello():
  print("### COMPILATION BUILD CONFIGURATOR ###")


def main():
  parser = argparse.ArgumentParser()
  parser.add_argument("--board", required=True, help="Board.")
  parser.add_argument("--toolchain", required=True, help="Flashing target e.g. STM32F103C8T6.")
  parser.add_argument("--trace_level", help="Trace level.")
  
  args = parser.parse_args()

  board = args.board
  toolchain = args.toolchain
  trace_level = args.trace_level
  build_dir = os.environ['BUILDDIR']

  if os.getcwd() != build_dir:
    raise Exception("Invalid build directory. Use: cd {0}".format(build_dir))

  print("Configuration:")
  print("-- Board: {0}".format(board))
  print("-- Toolchain: {0}".format(toolchain))
  print("-- Trace level: {0}".format(trace_level))


  build_command = "cmake . -DBOARD={0} -DTRACE_LEVEL={1} -DTOOLCHAIN={2} .. && make".format(board, trace_level, toolchain)
  print("-- Build command: {0}".format(build_command))
  subprocess.call(build_command, shell=True)

if __name__ == "__main__":
  try:
    show_hello()
    main()
  except Exception as e:
    print("Error: {0}".format(e))