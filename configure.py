#!/usr/bin/python
import subprocess
import os

## git submodule init update
# https://github.com/boostorg/boost
if os.name == 'nt' :
    subprocess.run(["cmake", "install", ".", 
                    "-s", "build_type=RelWithDebInfo", 
                    "--install-folder=cmake-build-relwithdebinfo-msvc22",
                    "--build=missing","-G", 
                    "Visual Studio 17 2022"
                    ])
    subprocess.run(["cmake", "install", ".", 
                    "-s", "build_type=RelWithDebInfo", 
                    "--install-folder=cmake-build-relwithdebinfo-ninja",
                    "--build=missing","-G", 
                    "Ninja Multi-Config"
                    ])
else:
    subprocess.run(["conan", "install", ".", "-s", "build_type=Release", "--install-folder=cmake-build-release","--build=missing"])
    subprocess.run(["conan", "install", ".", "-s", "build_type=Debug", "--install-folder=cmake-build-debug","--build=missing"])

# Windows -G "Ninja Multi-Config" -DCONAN_DISABLE_CHECK_COMPILER=1 | set CONAN_REVISIONS_ENABLED=1 && conan install --build=missing --remote=bincrafters .
