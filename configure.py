#!/usr/bin/python
import subprocess
import os
subprocess.run(["conan", "install", ".", "-s", "build_type=Debug", "--install-folder=cmake-build-debug"])
subprocess.run(["conan", "install", ".", "-s", "build_type=Release", "--install-folder=cmake-build-release"])
