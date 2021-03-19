#!/usr/bin/env python

import argparse
import subprocess 
import shutil
import os

path_to_jlink_scripts_dir = "{0}/jlink".format(os.path.dirname(__file__))

jlink_flash_command_filename = "flashCommand.jlink"

def update_jlink_flash_file(binary_path):
  path_to_jlink_flash_script = "{0}/{1}".format(path_to_jlink_scripts_dir, jlink_flash_command_filename)
  
  lines = []

  with open(path_to_jlink_flash_script, "r") as f:
      lines = f.readlines()

  lines = lines[1:]

  with open(path_to_jlink_flash_script, "w") as f:
    f.write("loadFile {0}\n".format(binary_path))

    for l in lines:
      f.write(l)

def flash(binary_path, target):
  update_jlink_flash_file(binary_path)

  path_to_jlink_flash_script = "{0}/{1}".format(path_to_jlink_scripts_dir, jlink_flash_command_filename)
  flash_command = "JLinkExe -device {0} -If SWD -Speed 1000 -CommandFile {1}".format(target, path_to_jlink_flash_script)
  print(flash_command)
  subprocess.call(flash_command, shell=True)

def main():
  parser = argparse.ArgumentParser()
  parser.add_argument("binary_path", help="Path to the hex file that contains binary code.")
  parser.add_argument("target", help="Flashing target e.g. STM32F103C8T6.")
  args = parser.parse_args()

  binary_path = args.binary_path
  target = args.target 

  flash(binary_path, target)

if __name__ == "__main__":
  main()
