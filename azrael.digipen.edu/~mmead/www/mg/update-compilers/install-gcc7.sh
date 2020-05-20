#!/bin/bash

# Add the repositories
sudo add-apt-repository ppa:ubuntu-toolchain-r/test

# Update the repositories:
sudo apt-get update

# Install gcc-7, g++-7, and 32-bit libs
sudo apt-get install gcc-7 g++-7 gcc-7-multilib g++-7-multilib

# Add each version of each compiler as an alternative program:
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 50 --slave /usr/bin/g++ g++ /usr/bin/g++-5
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 90 --slave /usr/bin/g++ g++ /usr/bin/g++-7

# Set the desired compiler versions:
sudo update-alternatives --config gcc

# Check that the versions are correct:
gcc --version
