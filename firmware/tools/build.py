#!/usr/bin/env python
import argparse
import subprocess 
import shutil
import os

def show_hello():
  print("### COMPILATION BUILD CONFIGURATOR ###")
  
def build_app(cfg):
  cmake_path = os.environ['APP_SOLUTION_CMAKE_DIR_PATH']
  build_command = "cmake . -DBOARD={0} -DTRACE_LEVEL={1} -DTOOLCHAIN={2} .. && make".format(cfg['board'], cfg['trace_level'], cfg['toolchain'])
  print("-- Build command: {0}".format(build_command))
  subprocess.call(build_command, shell=True)

def build_unittests(cfg):
  cmake_path = os.environ['UNITTESTS_SOLUTION_CMAKE_DIR_PATH']
  build_command = "cmake . -DBOARD={0} -DTRACE_LEVEL={1} -DTOOLCHAIN={2} {3} && make".format(cfg['board'], cfg['trace_level'], cfg['toolchain'], cmake_path)

  print(build_command)
  subprocess.call(build_command, shell=True)

def main():
  parser = argparse.ArgumentParser()
  parser.add_argument("--target", required=True, help="Target: prod, unittests .")
  parser.add_argument("--board", required=True, help="Select board.")
  parser.add_argument("--toolchain", required=True, help="Toolchain, e.g. x86_64, arm.")
  parser.add_argument("--trace_level", help="Trace level.")
  
  args = parser.parse_args()

  board = args.board
  toolchain = args.toolchain
  trace_level = args.trace_level

  cfg = {
    'board' : args.board,
    'toolchain' : args.toolchain,
    'trace_level' : args.trace_level,
    'target' : args.target
  }

  build_dir = os.environ['BUILD_DIR']

  if os.getcwd() != build_dir:
    raise Exception("Invalid build directory. Use: cd {0}".format(build_dir))

  print("Configuration:")
  print("-- Board: {0}".format(cfg['board']))
  print("-- Toolchain: {0}".format(cfg['toolchain']))
  print("-- Build target: {0}".format(cfg['target']))
  print("-- Trace level: {0}".format(cfg['trace_level']))

  if cfg['target'] == 'app':
    build_app(cfg)
  elif cfg['target'] == 'unittests':
    build_unittests(cfg)

if __name__ == "__main__":
  try:
    show_hello()
    main()
  except Exception as e:
    print("Error: {0}".format(e))