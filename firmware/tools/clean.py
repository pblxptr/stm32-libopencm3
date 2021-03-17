#!/usr/bin/env python 

import os
from pathlib import Path
import shutil

directories_to_remove = [
  'CMakeFiles'
]

files_to_remove = [
  'Makefile',
  'CMakeCache'
]

extensions_to_remove = [
  '.ii',
  '.s'
]

def show_hello():
  print("### Cleaning.... ###")

def erase_build(build_dir):
  for subdir, dirs, files in os.walk(build_dir):
    dir_path = Path(subdir)

    for filename in files:
      filepath = Path(subdir + os.sep + filename)
      os.remove(str(filepath))

    if dir_path == Path(build_dir):
      continue

    shutil.rmtree(str(dir_path))
    continue

def main():
  build_dir = os.environ['BUILDDIR']
  src_dir = os.environ['SOURCEROOT']

  if src_dir is None or build_dir is None:
    raise Exception("Invalid source or build dir.")

  erase_build(build_dir)

  for subdir, dirs, files in os.walk(src_dir):
    dir_path = Path(subdir)
    if dir_path.name in directories_to_remove:
      print("Removing directory: {0}".format(dir_path))
      shutil.rmtree(str(dir_path))
      continue

    for filename in files:
      filepath = Path(subdir + os.sep + filename)
      if filepath.name in files_to_remove or filepath.suffix in extensions_to_remove:
        print("Removing file: {0}".format(filepath))
        os.remove(str(filepath))



if __name__ == "__main__":
  try:
    show_hello()
    main()
  except Exception as e:
    print("Error: {0}".format(e))