#!/bin/bash

# Add the repositories
sudo add-apt-repository ppa:ubuntu-toolchain-r/test

# Update the repositories:
sudo apt-get update

# Install gcc/g++ 5,6,7,8,9 32-bit and 64-bit
sudo apt-get --assume-yes install gcc-5 g++-5 gcc-5-multilib g++-5-multilib
sudo apt-get --assume-yes install gcc-6 g++-6 gcc-6-multilib g++-6-multilib
sudo apt-get --assume-yes install gcc-7 g++-7 gcc-7-multilib g++-7-multilib
sudo apt-get --assume-yes install gcc-8 g++-8 gcc-8-multilib g++-8-multilib
sudo apt-get --assume-yes install gcc-9 g++-9 gcc-9-multilib g++-9-multilib

# Add each version of each compiler as an alternative program:
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 50 --slave /usr/bin/g++ g++ /usr/bin/g++-5
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-6
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 70 --slave /usr/bin/g++ g++ /usr/bin/g++-7
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 80 --slave /usr/bin/g++ g++ /usr/bin/g++-8
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90 --slave /usr/bin/g++ g++ /usr/bin/g++-9

# Set the desired compiler versions:
sudo update-alternatives --config gcc

# Check that the versions are correct:
gcc --version
