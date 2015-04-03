# File      : ua.py
#             Tool Script for building User Applications
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
# Change Logs:
# Date           Author       Notes
# 2015-02-07     Bernard      The firstly version
#

import os
import sys
from SCons.Script import *

Rtt_Root = ''
BSP_Root = ''
Env = None

def BuildEnv(BSP_ROOT, RTT_ROOT):
    if BSP_ROOT == None:
        if os.getenv('BSP_ROOT'):
            BSP_ROOT = os.getenv('BSP_ROOT')
        else:
            print 'Please set BSP(board support package) directory!'
            exit(-1)

    if not os.path.exists(BSP_ROOT):
        print 'No BSP(board support package) directory found!'
        exit(-1)

    if RTT_ROOT == None:
        # get RTT_ROOT from BSP_ROOT
        sys.path = sys.path + [BSP_ROOT]
        try:
            import rtconfig
            RTT_ROOT = rtconfig.RTT_ROOT
        except Exception as e:
            print 'Import rtconfig.py in BSP(board support package) failed.'
            print e
            exit(-1)

    global Rtt_Root
    global BSP_Root

    Rtt_Root = RTT_ROOT
    BSP_Root = BSP_ROOT

def BuildHostApplication(TARGET, SConscriptFile):
    sys.path = sys.path + [os.path.join(os.getcwd(), 'tools', 'host')]

    from building import PrepareHostModuleBuilding

    Env = Environment()
    PrepareHostModuleBuilding(Env)
    objs = SConscript(SConscriptFile)
    target = Env.Program(TARGET, objs)
    return

def BuildApplication(TARGET, SConscriptFile, BSP_ROOT = None, RTT_ROOT = None):
    global Env
    global Rtt_Root
    global BSP_Root

    # build application in host 
    if BSP_ROOT == None and RTT_ROOT == None and not os.getenv('BSP_ROOT'):
        BuildHostApplication(TARGET, SConscriptFile)
        return

    # handle BSP_ROOT and RTT_ROOT
    BuildEnv(BSP_ROOT, RTT_ROOT)

    sys.path = sys.path + [os.path.join(Rtt_Root, 'tools'), BSP_Root]

    # get configuration from BSP 
    import rtconfig 
    from rtua import GetCPPPATH
    from building import PrepareModuleBuilding

    linkflags = rtconfig.M_LFLAGS + ' -e main'
    CPPPATH = GetCPPPATH(BSP_Root, Rtt_Root)

    if rtconfig.PLATFORM == 'cl': 
        Env = Environment(TARGET_ARCH='x86')
        Env.Append(CCFLAGS=rtconfig.M_CFLAGS)
        Env.Append(LINKFLAGS=rtconfig.M_LFLAGS)
        Env.Append(CPPPATH=CPPPATH)
        Env.Append(LIBS='rtthread', LIBPATH=BSP_Root)
        Env.Append(CPPDEFINES=['RTT_IN_MODULE'])
        Env.PrependENVPath('PATH', rtconfig.EXEC_PATH)
    else:
        Env = Environment(tools = ['mingw'],
            AS = rtconfig.AS, ASFLAGS = rtconfig.AFLAGS,
            CC = rtconfig.CC, CCFLAGS = rtconfig.M_CFLAGS,
            CXX = rtconfig.CXX, AR = rtconfig.AR, ARFLAGS = '-rc',
            LINK = rtconfig.LINK, LINKFLAGS = linkflags,
            CPPPATH = CPPPATH)

    PrepareModuleBuilding(Env, Rtt_Root, BSP_Root)

    objs = SConscript(SConscriptFile)

    # build program 
    if rtconfig.PLATFORM == 'cl':
        dll_target = TARGET.replace('.mo', '.dll')
        target = Env.SharedLibrary(dll_target, objs)

        target = Command("$TARGET", dll_target, [Move(TARGET, dll_target)])
        # target = dll_target
    else:
        target = Env.Program(TARGET, objs)

    if hasattr(rtconfig, 'M_POST_ACTION'):
        Env.AddPostAction(target, rtconfig.POST_ACTION)

    if hasattr(rtconfig, 'M_BIN_PATH'):
        Env.AddPostAction(target, [Copy(rtconfig.M_BIN_PATH, TARGET)])
