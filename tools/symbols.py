import collections
import demangler


def demangle(mangled_str):
    try:
        demangled = demangler.demangle(mangled_str)

        if demangled == None:
            raise Exception('Demangling failed')

        return str(demangled)
    except:
        raise Exception('Demangling failed')


class SymbolTable():

    def __init__(self, demangle=True):
        self.mangled_dict = dict()
        self.demangled_dict = dict()
        self.hasDemangled = demangle


    def __getitem__(self, key):
        address = self.mangled_dict.get(key)

        if address == None and self.hasDemangled == True:
            address = self.demangled_dict.get(key)

        return address


    def add(self, mangled_name, address):
        self.mangled_dict[mangled_name] = address

        if self.hasDemangled == True:
            try:
                demangled_name = demangle(mangled_name)
                self.demangled_dict[demangled_name] = address
            except:
                pass


    def mangled_syms(self):
        return self.mangled_dict


    def demangled_syms(self):
        return self.demangled_dict


    @staticmethod
    def from_file(path, demangle=True, offset=0):

        f = open(path, "r")

        sym_table = SymbolTable(demangle)

        is_map_file = False

        i = 0
        for line in f:
            if i == 3:
                if line.startswith('SYMBOL TABLE:'):
                    is_map_file = True
                break
            i += 1
        
        f.seek(0)

        # Map file
        i = 0
        if is_map_file == True:
            for line in f:
                if i < 4:
                    i += 1
                    continue

                line_sanitized = line.replace(r'\ŧ', ' ')
                line_sanitized = line_sanitized.strip('\r')
                line_sanitized = line_sanitized.strip('\n')
                
                line_segs = line_sanitized.split(' ')
                if len(line_segs) < 2:
                    continue

                if len(line_segs[0]) != 8:
                    continue

                try:
                    address = int(line_segs[0], 0x10)
                except:
                    continue

                if(address & 0x80000000):
                    address = -0x100000000 + address

                mangled_name = line_segs[len(line_segs)-1]
                if len(mangled_name) == 0:
                    continue

                sym_table.add(mangled_name, address+offset)

        # General smybol table
        else:
            for line in f:
                if line.startswith('#'):
                    continue

                line_sanitized = line.replace('\t', ' ')
                line_sanitized = line_sanitized.replace('\r', '')
                line_sanitized = line_sanitized.replace('\n', '')
                line_sanitized = line_sanitized.replace('=', ' ')
                line_sanitized = line_sanitized.replace(':', ' ')
                line_sanitized = line_sanitized.replace(';', ' ')
                
                line_segs = line_sanitized.split()

                if len(line_segs) < 2:
                    continue

                mangled_name = line_segs[0]
                address_seg = line_segs[1]

                try:
                    address = int(address_seg, 0)
                except:
                    continue

                sym_table.add(mangled_name, address+offset)

        return sym_table
