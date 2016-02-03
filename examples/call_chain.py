import pypin, sys

def print_chain(ins_object):
    if pypin.INS_IsDirectCall(ins_object):
        name = pypin.RTN_FindNameByAddress(int(pypin.INS_DirectBranchOrCallTargetAddress(ins_object)))
        callee_name = pypin.RTN_FindNameByAddress(int(pypin.INS_Address(ins_object)))
        if name and name[0] != "." and callee_name and callee_name[0] != "." and name[0] != "_" and callee_name[0] != "_":
            print "call", callee_name, "->", name
    return

    if pypin.INS_IsMov(ins_object):
        if pypin.INS_IsMemoryWrite(ins_object):
            print pypin.INS_Disassemble(ins_object)
            print pypin.INS_MemoryWriteSize(ins_object)
    if pypin.INS_IsNop(ins_object):
        print pypin.INS_Disassemble(ins_object)
        return
    if pypin.INS_IsRet(ins_object):
        print pypin.INS_Disassemble(ins_object)
        return
        if pypin.INS_IsMemoryWrite(ins_object):
            print pypin.INS_Disassemble(ins_object)
            print pypin.INS_MemoryWriteSize(ins_object)
    return

pypin.INS_AddInstrumentFunction(print_chain)
