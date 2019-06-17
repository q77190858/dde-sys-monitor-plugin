#!/bin/bash
cd build/
rm -rf *
cmake ..
make
sudo make install
pkill dde-dock
dde-dock
