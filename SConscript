# RT-Thread building script for component

Import('rtconfig')
Import('RTT_ROOT')
from building import *

cwd = GetCurrentDir() + "/src"
src = Glob("src/*.c")

        
CPPPATH = [cwd]

CPPDEFINES = []

group = DefineGroup('eluart', src, depend = [''], CPPPATH = CPPPATH, CPPDEFINES=CPPDEFINES)

Return('group')
