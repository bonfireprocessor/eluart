# : Tada: Lua2rtt: Tada: #

[! [Build status] (https://travis-ci.org/liu2guang/lua2rtt.svg?branch=master)] (https://travis-ci.org/liu2guang/lua2rtt)
[! [release] (https://img.shields.io/badge/release-v1.0.0-range.svg)] (https://github.com/liu2guang/lua2rtt/releases)

Lua2RTT is a LUA library that transplanted in RT-Thread 3.0 and above, with a seamless embedded RTT, no need for developers to transplant. If you feel that the library is comfortable, please donate a small star. Small stars are newer Power !!!

## 1. renderings

! [Effect] (https://i.imgur.com/nzp2woe.gif)

## 2. Install Lua2rtt

At present, the LUA2RTT library has been added to the RT-Thread official PKGS package, which can be directly enabled in MenuConfig.

1. Run menuconfig in the ENV.
2. Enter the RT-THREAD Online Packages -> Language directory.
3. Open Lua2rtt, select Submitted Version (release release of Lua2rtt library transplant) is the latest version of LateSet, then select Porting Lua Version (Transplant LUA Source Code) to you want to transplant version (currently support 5.1.4 and 5.3.4 .
4. Execute pkgs --update update Lua2rtt to your BSP below.
5. Execute scons / scons --target = xxx to compile generation projects, download and run.

! [Install Process] (https://i.imgur.com/wouodbj.gif)

## 3. Uninstall Lua2rtt

1. Run menuconfig in the ENV.
2. Enter the RT-THREAD Online Packages -> Language directory.
3. Turn off Lua2rtt.
4. Execute pkgs --update, and enter `y`, agreed to delete the PKG package file.
5. Execute scons / scons --target = xxx to compile generation projects, download and run.

! [Unloading Process] (https://i.imgur.com/idfffpn.gif)

## 4. Tutorial recommendation

1. [Alberts Author] (https://www.jianshu.com/u/8fad76e7e05c).
2. [Lua 5.1 Reference Manual Chinese] (https://www.codingnow.com/2000/download/lua_manual.html).
3. [LUA 5.3 Reference Manual Chinese Edition] (http://cloudwu.github.io/lua53doc/contents.html).

## 5. Welcome to join.

Unofficial discussion Tencent QQ group: [289156309] ().

## 6. Thank you

1. This library is based on https://github.com/lua/lua transplantation.
2. Thank Lua Team. This transplant is a version of some of the original author's code to the RTT online package. The warehouse retains the original author's license statement! For specific original author license, please see https://www.lua.org/License .html, the transplantation code section retains https://github.com/liu2guang/lua2rtt/blob/master/license license.