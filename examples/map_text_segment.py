import sys, pypin
total = 0
info = file("map.out", "w")

#map the text segment of an executable
def map(ins_addr):
	x = pypin.INS_Address(ins_addr)
	if x < 0x500000:
		info.write("Instruction Address_1: %x  OPCODE %s\n" % (x, pypin.INS_Disassemble(ins_addr)))


pypin.INS_AddInstrumentFunction(map)
