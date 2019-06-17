#!/bin/bash
cd ~/plugin-guide/sys_monitor/build/
rm -rf *
cmake ..
make
sudo make install
pkill dde-dock
dde-dock
