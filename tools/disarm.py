#!/usr/bin/env python3

import sys
import struct
import binascii
import capstone


def main(argc, argv):

    if (argc != 2):
        print("Usage: %s <code>" % argv[0])
        sys.exit(1)

    string = argv[1]

    if string.startswith("0x") or string.startswith("0X"):
        try:
            data = struct.pack("<I", int(string, 0x10))
        except:
            print("Illegal code format!")
            sys.exit(1)

    else:
        try:
            data = binascii.unhexlify(string)
        except:
            print("Illegal code format!")
            sys.exit(1)


    md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_ARM)

    for i in md.disasm(data, 0):
        print("%s\t%s" % (i.mnemonic, i.op_str))


if __name__ == '__main__':
    main(len(sys.argv), sys.argv)
