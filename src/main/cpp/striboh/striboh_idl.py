import sys
import os
import logging

my_skript_dir = os.path.dirname(sys.argv[0])

logging.debug("striboh_idl: Skript dir \"{my_skript_dir}\".".format(my_skript_dir=my_skript_dir))

if len(my_skript_dir) > 0:
    my_skript_dir += '/'

my_skript_dir = os.path.normpath(my_skript_dir)
my_striboh_libs = os.path.normpath('${CMAKE_BINARY_DIR}/lib')
sys.path += [my_striboh_libs, my_skript_dir]

if os.name == 'nt':
    os.add_dll_directory("${CMAKE_BINARY_DIR}/lib")

logging.debug("striboh_idl: Current directory {my_cur_dir}".format(my_cur_dir=os.path.abspath(os.curdir)))
logging.debug("striboh_idl: Current path {my_cur_path}".format(my_cur_path=sys.path))

import stribohmodule as idl


def main():
    print("Version:" + idl.version())
    my_ret_val = idl.process(sys.argv)
    if my_ret_val != 0:
        print(f"\nBackend returned error # {my_ret_val}\n".format(my_ret_val=my_ret_val))
    else:
        print("Backend returned OK ({my_ret_val})\n".format(my_ret_val=my_ret_val))
    sys.exit(my_ret_val)


if __name__ == "__main__":
    # execute only if run as a script
    main()
