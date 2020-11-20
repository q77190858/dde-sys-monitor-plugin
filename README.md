dde-sys-monitor-plugin

Deepin monitors the dock plug-in, which monitors CPU usage, memory usage, swap usage, total upload downloads, real-time speed and battery discharge power, available in text and chart modes

-----------------------

## One, reference project

-[CMDU_DDE_DOCK for deepin](https://github.com/sonichy/CMDU_DDE_DOCK)@sonichy

-[indicator-multiload in ubuntu](https://launchpad.net/ubuntu/+source/indicator-multiload/)

## 2. Picture display

![alt](image/wordmode1.jpg) ![alt](image/chartmode1.jpg) ![alt](image/wordmode2.jpg) ![alt](image/chartmode2.jpg)

The above four pictures are the performance of the plug-in in text mode and chart mode, and the plug-in is highly configurable

![alt](image/setting1.jpg) ![alt](image/setting2.jpg)

There are setting options in the right-click menu, you can set the display content in each mode

## Three, download and install
### 1. Code cloud one-click download installation

Deepin20 english plugin

''bash
wget https://github.com/khumnath/dde-sys-monitor-plugin/releases/download/20201025en/libsys_monitor.so . . .
sudo mv libsys_monitor.so /usr/lib/dde-dock/plugins/
pkill dde-dock


### 2. Download the address manually
english version https://github.com/khumnath/dde-sys-monitor-plugin/releases/download/20201025en/libsys_monitor.so
chinese: libsys_monitor.so (https://github.com/q77190858/dde-sys-monitor-plugin/raw/master/bin/libsys_monitor.so)

Code Cloud: libsys_monitor.so (https://gite.com/q77190858/dde-sys-monitor-plugin/raw/master/bin/libsys_monitor.so)

for english users (libsys_monitor.so) () https://github.com/khumnath/dde-sys-monitor-plugin/releases/download/20201025en/libsys_monitor.so)

### 3. The installation command

''bash
sudo cp libsys_monitor.so /usr/lib/dde-dock/plugins/
pkill dde-dock
dde-dock


Fourth, source code compilation and installation

### 1. Official plug-in development tutorial

See the "Official Development Document" (https://github.com/linuxdeepin/dde-dock/blob/master/plugins/plugin-guide/plugins-developer-guide.md
)

### 2. Installation dependency

Compilation also requires the following dependencies to be installed (the environment configuration described in the official development documentation is incomplete):

''bash
sudo apt install build-essential
sudo apt install dde-dock-dev
sudo apt install qtbase5-dev-tools
sudo apt install libdtkwidget-dev
#使用qtcreator集成环境可以直接设计ui界面, the current qt version is 5.11.3, not necessary
sudo apt install qtcreator
#使用qtcreator打开cmake工程要先安装cmake
sudo apt install cmake
```

### 3. One-click compilation installation

''bash
cd dde-sys-monitor-plugin
./build.sh
```

Five, update the log

Have questions welcome back feedback! See my blog for the experience of development
(http://blog.mxslly.com/archives/95.html) (http://blog.mxslly.com/archives/95.html)

- 20190617 22:37 Update: Fix upload download consistent bug, download address same above

- 20190619 12:07 Update: Reduced width, small bubble text alignment, compilation script optimization, download address i.m

- 20190627 16:04 Update: Fix the fashion mode display incomplete problem, now fashion mode only shows the internet speed

- 20190830 03:14 Update: Reduce 1 character width, now the lowest unit is KB, do not display B

- 20191211 10:09 Update: Import items to qtcreator, add settings, set up display content

- 20200214 21:09 Update: optimized for high split-screen dpi, display leading can be set, save settings using system functions, and click on small bubbles after the update cannot pop up for unknown reasons

- 20200322 16:31 Update: Add battery power display

- 20200420 00:01 Update: Failed to fix a UI problem that the plug-in interface appears blank

- 20200421 17:01 Update: Fix the problem of failed battery information reading and add a battery information switch

- 20200721 20:38 Update: Refactoring the code architecture to improve scalability, refer to indicator-multiload to add chart mode, add many setup options, use upower to get battery power to improve compatibility, and adapt the upper and lower left and right positions of the deeppin20dock

- 20200818 15:50 Update: Inspired by the @zty199, the ability to change the color of text following the system theme has been added, limited to text mode

- 20200826 23:20 Update: Fix the problem of inaccurate network speed display when the sampling interval is not 1s

- 20200916 21:06 Update: Fix plug-ins that sometimes are obscured by dde-dock;

- 20200922 23:51 Update: Fix the problem that the plug-in is too white when the dock is left in the left and right positions

- 20200928 20:06 Update: Fix bugs that are not aligned in text mode;

- 20201025 12:50 Update: Temporarily modify the plug-in named datetime to prevent being blocked by the dock
