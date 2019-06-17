#!/bin/bash
cd -p ~/plugin-guide/sys_monitor/build/
rm -rf *
cmake ..
make
sudo make install
pkill dde-dock
dde-dock
