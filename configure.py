#!/usr/bin/python
import subprocess
import os

if os.name == 'nt' :
    subprocess.run(["cmake", "install", ".", "-s", "build_type=Release", "--install-folder=cmake-build-release","--build=missing"])
else:
    subprocess.run(["conan", "install", ".", "-s", "build_type=Release", "--install-folder=cmake-build-release","--build=missing"])

# Windows -G "Ninja Multi-Config" -DCONAN_DISABLE_CHECK_COMPILER=1 | set CONAN_REVISIONS_ENABLED=1 && conan install --build=missing --remote=bincrafters .
#cmake -G "Visual Studio 17 2022"