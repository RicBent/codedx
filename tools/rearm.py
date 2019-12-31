#!/usr/bin/env python3

import sys
import struct
import arm

def main(argc, argv):

    if (argc < 2):
        print("Usage: %s <instruction>" % argv[0])
        sys.exit(1)

    instruction = ' '.join(argv[1:])

    try:
        data = arm.assemble_instruction(instruction)
    except:
        sys.exit(1)

    print("0x%08X" % struct.unpack("<I", data))
    sys.exit(0)

if __name__ == '__main__':
    main(len(sys.argv), sys.argv)
