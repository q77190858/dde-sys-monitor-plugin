#!/bin/bash
mkdir build
cd build/
if [ $? -ne 0 ]; then
exit
fi
rm -rf *
cmake ..
make
sudo make install
pkill dde-dock
dde-dock
