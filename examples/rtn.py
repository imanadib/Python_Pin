import pypin
count = 0
def load(img):
	global count
	if count == 0:
		x = pypin.TRACE_Rtn(img)
		sys.stdout.write("\nInteresting fact is I find this information statically :)! but sometimes Im wrong...\n")
		sys.stdout.write("NAME %s\n" % pypin.RTN_Name(x))
		sys.stdout.write("SIZE %x\n" % pypin.RTN_Size(x))
		sys.stdout.write("ID %x\n" % pypin.RTN_Id(x))
		sys.stdout.write("RANGE %x\n" % pypin.RTN_Range(x))
		sys.stdout.write("ADDRESS 0x%x\n" % pypin.RTN_Address(x))
		pypin.RTN_Open(x)
		y = pypin.RTN_InsHead(x)
		sys.stdout.write("DISASSEMBLE HEAD INSTRUCTION: %s\n" % pypin.INS_Disassemble(y))
		sys.stdout.write("NUMBER OF INSTRUCTIONS %x\n" % pypin.RTN_NumIns(x))
		y = pypin.RTN_InsTail(x)
		sys.stdout.write("DISASSEMBLE TAIL INSTRUCTION: %s\n\n" % pypin.INS_Disassemble(y))
		pypin.RTN_Close(x)
		count += 1

pypin.TRACE_AddInstrumentFunction(load)

