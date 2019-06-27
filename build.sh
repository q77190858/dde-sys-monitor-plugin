#!/bin/bash
mkdir build
cd build/ || exit
rm -rf * || exit
cmake .. || exit
make || exit
sudo make install || exit
pkill dde-dock
dde-dock
