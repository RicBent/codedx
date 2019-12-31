# UNFINISHED

import struct
import subprocess

def roundSegment(size):
    size += 0xFFF
    size &= ~0xFFF
    return size

def run_proc(cmd):
    return subprocess.call(cmd, shell=True)


out = open('all.bin', 'wb')

f = open('text_decomp', 'rb')
out.write(f.read())
out.seek(roundSegment(out.tell()))

f = open('rodata_decomp', 'rb')
out.write(f.read())
out.seek(roundSegment(out.tell()))

f = open('data_decomp', 'rb')
out.write(f.read())
out.seek(roundSegment(out.tell()))
       
out.seek(0x00CD1000)


if run_proc('llvm-objcopy -O binary ../subsdk0.elf subsdk0.bin') != 0:
    raise Exception('objcopy failed')

f = open('subsdk0.bin', 'rb')
out.write(f.read())


# Apply hooks
f = open('../AEE6DCCC06D9C05B42061E2019123A61.ips', 'rb')
f.read(5)

while True:
    try:
        addr = struct.unpack('>I', f.read(4))[0] - 0x100
        length = struct.unpack('>H', f.read(2))[0]
    except:
        break
    print('address: %08X, length: %04X' % (addr, length))
    data = f.read(length)
    
    out.seek(addr)
    out.write(data)
