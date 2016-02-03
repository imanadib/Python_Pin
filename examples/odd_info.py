import sys, pypin
total = 0
info = file("odd.out", "w")


def counter(ins_addr):
	x = pypin.INS_Address(ins_addr)
	y = pypin.INS_IsMov(ins_addr)
	if y:
		info.write("MOV @ : " + hex(x) + pypin.INS_Disassemble(ins_addr) + "\n")	

	y = pypin.INS_IsNop(ins_addr)
	if y:
		info.write("NOP @ : " + hex(x) + pypin.INS_Disassemble(ins_addr) + "\n")	

	y = pypin.INS_IsLea(ins_addr)
	if y:
		info.write("LEA @ : " + hex(x) + pypin.INS_Disassemble(ins_addr) + "\n")	


pypin.INS_AddInstrumentFunction(counter)
