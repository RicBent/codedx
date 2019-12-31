#!/usr/bin/env python3

import sys
from operator import itemgetter
from termcolor import cprint
from symbols import SymbolTable

 
def fatal(msg):
    cprint(msg, 'red')
    sys.exit(1)


def main(argc, argv):
    
    # Check arguments
    if argc != 5:
        fatal('Usage: %s <symbol table> <symbol base> <new symbol base> <output linker script>' % argv[0])

    sym_path = argv[1]
    sym_path_out = argv[4]

    try:
        sym_base = int( argv[2], 0)
    except:
        fatal('Parsing symbol base failed!')
    
    try:
        sym_base_new = int(argv[3], 0)
    except:
        fatal('Parsing new symbol base failed!')

    try:
        sym_table = SymbolTable.from_file(sym_path, False, sym_base - sym_base_new)
    except:
        fatal('Opening symbol table failed!')
    
    try:
        out_file = open(sym_path_out, "w")
    except:
        fatal('Opening output file failed!')


    # Create linker script with relocated symbols
    for sym_name, sym_address in sorted(sym_table.mangled_dict.items(), key=itemgetter(1)):
        sym_line = '%s = %s;\n' % (sym_name, hex(sym_address))
        out_file.write(sym_line)

    print('Relocated %s from %s to %s into %s' % (sym_path, hex(sym_base), hex(sym_base_new), sym_path_out))

    sys.exit(0)


if __name__ == '__main__':
    main(len(sys.argv), sys.argv)
