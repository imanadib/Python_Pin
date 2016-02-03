import sys, pypin
total = 0
info = file("inscount.out", "w")

def counter(trace_addr):
    global total
    x = pypin.TRACE_BblHead(trace_addr)
    y = pypin.BBL_Address(x)
    instrucs = pypin.BBL_NumIns(x)
    total += instrucs
    info.write("Basic Block @ %x SIZE: %x NUM INS= IN BLOCK: %x  TOTAL: %x\n" % (y, pypin.BBL_Size(x), instrucs, total ))

pypin.TRACE_AddInstrumentFunction(counter)
