#!/bin/bash

# Add the repositories
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-add-repository "deb http://llvm.org/apt/trusty/ llvm-toolchain-trusty-3.8 main"

# Update the repositories:
sudo apt-get update

# Install gcc-5, g++-5, clang-3.8, and clang++-3.8:
sudo apt-get install gcc-5 g++-5 clang-3.8

# Add each version of each compiler as an alternative program:
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50 --slave /usr/bin/g++ g++ /usr/bin/g++-4.8
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 60 --slave /usr/bin/g++ g++ /usr/bin/g++-5
sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3.5 50 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-3.5
sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3.8 60 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-3.8

# Set the desired compiler versions:
sudo update-alternatives --config gcc
sudo update-alternatives --config clang

# Check that the versions are correct:
gcc --version
clang --version
