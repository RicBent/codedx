import struct

header = 'IPS32'
eof = 'EEOF'

def write_header(stream):
    stream.write(bytes(header, 'utf-8'))

def write_eof(stream):
    stream.write(bytes(eof, 'utf-8'))

def write_record(stream, offset, data):
    stream.write(struct.pack('>I', offset))
    stream.write(struct.pack('>H', len(data)))
    stream.write(data)
