import pypin, sys

def image_load(image):
    rtn = RTN_FindByName('printf')
    if pypin.RTN_Valid(rtn):
        print "Found %s in %s" % (routine, pypin.IMG_Name(img))
        pypin.RTN_Open(rtn)
        print "0x%x"%pypin.RTN_Address(rtn)
        first_instr = pypin.RTN_InsHead(rtn)
        print pypin.INS_Disassemble(first_instr)
        next_instr = pypin.INS_Next(first_instr)
        for i in range(10):
            disp = pypin.INS_Disassemble(next_instr)
            print pypin.INS_Disassemble(next_instr)
            if "ret" in disp:
                break
            next_instr = pypin.INS_Next(next_instr)
        pypin.RTN_Close(rtn)
        print "\n"*5
 
pypin.IMG_AddInstrumentFunction(image_load)
