# By RicBent
# Requires clang in path

import struct
import os
import subprocess
from elftools.elf.elffile import ELFFile
from elftools.common.exceptions import ELFError, ELFParseError

def run_proc(cmd):
    return subprocess.call(cmd, shell=True)


branch_conditions = {
    'eq': 0,
    'ne': 1,
    'cs': 2,
    'cc': 3,
    'mi': 4,
    'pl': 5,
    'vs': 6,
    'vc': 7,
    'hi': 8,
    'ls': 9,
    'ge': 10,
    'lt': 11,
    'gt': 12,
    'le': 13,
    'al': 14, 
    ''  : 14
}

def make_branch_instruction(src, dest, link, condition=''):

    if condition not in branch_conditions:
        raise Exception('Invalid condition \"%s\"' % condition)

    if dest % 4 or src % 4:
        raise Exception('Source and destination must be 4 byte aligned')

    # Offset (2 complement, 24 bis)
    instruction = (dest // 4) - (src // 4) - 2

    if not (-0x1000000 <= instruction <= 0xFFFFFF):
        raise Exception('Out of bounds jump range!')

    instruction &= 0x00FFFFFF

    # Brach opcode
    instruction |= 0b101 << 25

    # Link flag
    if link == True:
        instruction |= 0b1 << 24

    # Condition
    instruction |= branch_conditions[condition] << 28

    return struct.pack('<I', instruction)


def assemble_instruction(str):

    def try_remove(path):
        try:
            os.remove(path)
        except:
            pass

    if '\n' in str:
        raise Exception('Only one instruction may be assebled!')

    workdir = os.path.dirname(__file__)

    instruction_src_file = open(workdir + '/instruction_source.s', 'w')
    instruction_src_file.write('.section \".instruction\"\n.arm\n.fpu crypto-neon-fp-armv8\n    %s\n' % str)
    instruction_src_file.close()

    ret = run_proc('clang %s --target=armv7l-none-eabihf -mabi=aapcs-linux -mcpu=cortex-a57 -mfpu=crypto-neon-fp-armv8 -mfloat-abi=hard -o %s -c' % (workdir + '/instruction_source.s', workdir + '/instruction.o'))
    try_remove(workdir + '/instruction_source.s')
    if ret != 0:
        raise Exception('Compiling instruction failed!')

    try:
        elf = ELFFile(open(workdir + '/instruction.o', 'rb'))
    except IOError:
        try_remove(workdir + '/instruction.o')
        raise Exception('Opening instruction ELF failed!')

    try_remove(workdir + '/instruction.o')

    section = elf.get_section_by_name('.instruction')

    if section == None:
        raise Exception('Instruction ELF is invalid!')

    if section.data_size != 4:
        raise Exception('Input does not compile to a single instruction!')
    
    return section.data()
