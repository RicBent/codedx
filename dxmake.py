#!/usr/bin/env python3

import sys
import os
import re
import platform
import subprocess
from termcolor import cprint

if platform.system() == "Windows":
    import colorama
    colorama.init()


main_addr       = 0x00004000
main_size       = 0x00CD1000
subsdk_addr     = main_addr + main_size
main_build_id   = 'AEE6DCCC06D9C05B42061E2019123A61'
out_nso         = 'subsdk0'
out_ips         = main_build_id + '.ips'


def fatal(msg):
    cprint(msg, 'red')
    sys.exit(1)

def run_proc(cmd):
    return subprocess.call(cmd, shell=True)


def command_available(cmd):
    test_cmd = "which" if platform.system() != "Windows" else "where"
    try: 
        rc = subprocess.call([test_cmd, cmd], stdout=open(os.devnull, 'wb'), stderr=open(os.devnull, 'wb'))
        return rc == 0
    except: 
        return False


targets = {
#   target      tasks
    'syms':     ['syms'],
    'make':     ['syms', 'make'],
    'nso':      ['syms', 'make', 'nso'],
    'ips':      ['syms', 'make', 'ips'],
    'all':      ['syms', 'make', 'nso', 'ips'],
    'ftp':      ['syms', 'make', 'nso', 'ips', 'ftp'],
    'srv':      ['syms', 'make', 'nso', 'ips', 'ftp', 'srv'],
    'ftp-only': ['ftp'],
    'srv-only': ['srv'],
    'clean':    ['clean']
}

default_target = 'all'

def main(argc, argv):

    # Check environment
    if sys.version_info.major < 3:
        fatal("Python 3 or newer is required!")

    required_commands = ['make', 'clang', 'clang++', 'llvm-objdump', 'arm-none-eabi-ld']

    for cmd in required_commands:
        if command_available(cmd) == False:
            fatal('Required command \"%s\" is not available!' % cmd)


    # Check argument
    if argc > 2:
        fatal('Usage: %s [target]' % argv[0])

    if argc == 1:
        target_name = default_target
    else:
        target_name = argv[1]

    # Check target
    try:
        commands = targets[target_name]
    except KeyError:
        fatal('Invalid target \"%s\"' % target_name)


    # Remove all build files
    if 'clean' in commands:
        run_proc('make clean')

        for p in ['main.ld', out_ips, out_nso]:
            try:
                os.remove(p)
            except:
                pass
        print('Clean.')

    # Relocate main symbols to to subsdk0
    if 'syms' in commands:
        rc = run_proc('%s tools/symbol_relocate.py main.sym %s %s main.ld' % (sys.executable, hex(main_addr), hex(main_addr+main_size)))
        if rc != 0:
            fatal('Relocating main symbols failed!')

    # Compile and link code to ELF
    if 'make' in commands:
        rc = run_proc('make')
        if rc != 0:
            fatal('Running make failed!')

    # Create NSO from ELF
    if 'nso' in commands:
        rc = run_proc('%s tools/elf2nso.py %s.elf %s -s -c' % (sys.executable, out_nso, out_nso))
        if rc != 0:
            fatal('Creating NSO failed!')

    # Create IPS form hooks
    if 'ips' in commands:
        rc = run_proc('%s tools/hooks_to_ips.py hooks %s.sym %s %s' % (sys.executable, out_nso, hex(subsdk_addr - main_addr), out_ips))
        if rc != 0:
            fatal('Creating IPS failed!')

    # Upload NSO and IPS to switch
    if 'ftp' in commands:
        rc = run_proc('%s tools/ftp_up.py ftp.cfg %s %s' % (sys.executable, out_nso, out_ips))
        if rc != 0:
            sys.exit(1)

    # Run log server
    if 'srv' in commands:
        try:
            run_proc('%s tools/log_server.py -s' % sys.executable)
        except KeyboardInterrupt:
            pass

    sys.exit(0)


if __name__ == '__main__':
    main(len(sys.argv), sys.argv)
