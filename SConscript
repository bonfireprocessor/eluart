# RT-Thread building script for component

Import('rtconfig')
Import('RTT_ROOT')
from building import *

# cwd = GetCurrentDir() + "/src"
# src = Glob("src/*.c" )

        
# CPPPATH = [cwd]

# CPPDEFINES = []

# objs = DefineGroup('eluart', src, depend = [''], CPPPATH = CPPPATH, CPPDEFINES=CPPDEFINES)

# objs = objs + SConscript()


# Return('objs')
import os
from building import *

objs = []
cwd  = GetCurrentDir()
print("sconsript " + cwd)
list = os.listdir(cwd)

for item in list:
    if os.path.isfile(os.path.join(cwd, item, 'SConscript')):
        objs = objs + SConscript(os.path.join(item, 'SConscript'))

Return('objs')
