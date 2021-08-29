import sys

sys.path.append('../lib')
import stribohIdl


def main():
    print("Version:" + stribohIdl.version())
    myRetVal = stribohIdl.process(sys.argv)
    if myRetVal !=0 :
        print(f"\nError # {myRetVal}")
    return myRetVal


if __name__ == "__main__":
    # execute only if run as a script
    main()
