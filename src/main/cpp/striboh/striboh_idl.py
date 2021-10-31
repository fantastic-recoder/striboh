import sys
import os

my_skript_dir=os.path.dirname(sys.argv[0])

print("Skript dir {my_skript_dir}".format(my_skript_dir=my_skript_dir))

sys.path += [my_skript_dir+'/../lib', my_skript_dir+'../../../cmake-build-debug/lib']

print("Current directory {my_cur_dir}".format(my_cur_dir=os.path.abspath(os.curdir)))
print("Current path {my_cur_path}".format(my_cur_path=sys.path))

import stribohIdl


def main():
    print("Version:" + stribohIdl.version())
    my_ret_val = stribohIdl.process(sys.argv)
    if my_ret_val != 0:
        print(f"\nBackend returned error # {my_ret_val}\n".format(my_ret_val=my_ret_val))
    else:
        print("Backend returned OK ({my_ret_val})\n".format(my_ret_val=my_ret_val))
    return my_ret_val


if __name__ == "__main__":
    # execute only if run as a script
    main()
