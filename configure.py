#!/usr/bin/python
import subprocess
import os
subprocess.run(["conan", "install", ".", "-s", "build_type=Debug", "--install-folder=cmake-build-debug","--build=missing"])
#subprocess.run(["conan", "install", ".", "-s", "build_type=Release", "--install-folder=cmake-build-release","--build=missing"])

# Windows -G "Ninja Multi-Config" -DCONAN_DISABLE_CHECK_COMPILER=1 | set CONAN_REVISIONS_ENABLED=1 && conan install --build=missing --remote=bincrafters .