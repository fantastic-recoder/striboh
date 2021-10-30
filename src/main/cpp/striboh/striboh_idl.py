import sys

sys.path.append('../lib')
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
