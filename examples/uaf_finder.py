import pypin, sys

debug = True
allocations = []
last_allocated_size = 0
log_file = open('uaf.txt', 'w')

def add_allocation(address, size):
    for allocation in allocations:
        if allocation['address'] == address:
            allocation['size'] = size
            allocation['in_use'] = True
            return

    allocations.append({"address":address, "size":size, "in_use": True})

def mark_free(address):
    global allocations
    for allocation in allocations:
        if allocation['address'] == address:
            allocation['in_use'] = False

def a_heap_thing(address):
    global allocations
    for allocation in allocations:
        if address in range(allocation['address'], allocation['address']+allocation['size']):
            return allocation

    return None

def in_use(address):
    global allocations
    for allocation in allocations:
        if allocation['address'] == address and allocation['in_use']:
            return True
    return False

def malloc_before(everything):
    global last_allocated_size
    last_allocated_size = everything['arg_0']
    #print everything['arg_0'], hex(everything['ref_arg_0'])
    #pypin.set_pointer(everything['ref_arg_0'], 1)

def malloc_after(everything):
    global last_allocated_size
    address = everything['return']
    #print pypin.get_pointer(everything['reg_gax']), everything['return']
    #print "gax:%x;gbx:%x;gcx:%x;gdx:%x"%(everything['reg_gax'], everything['reg_gbx'], everything['reg_gcx'], everything['reg_gdx'])
    if last_allocated_size == 0:
        return
    add_allocation(address, last_allocated_size)

def free(everything):
    mark_free(everything['arg_0'])

def handle_reads(ins_info):
    global log_file
    heap_read_addr = ins_info['MEM_OP0']
    h = a_heap_thing(heap_read_addr)
    if h and not h['in_use']:
        # print " 0x%x %s" % (ins_info['IP'], ins_info['mnemonic'])
        if (ins_info['IP'] > 0):
            print "Reading a freed object!"
            print "UAF located at 0x%x [0x%x %s]" % (heap_read_addr, ins_info['IP'], ins_info['mnemonic'])
    return

def ins_test(ins):
    if pypin.INS_IsMov(ins) and (pypin.INS_IsMemoryRead(ins) or pypin.INS_IsMemoryWrite(ins)):
        pypin.INS_InsertCall(pypin.IPOINT_BEFORE, ins, handle_reads)

def memset_pre(everything):
    pypin.set_pointer(everything['reg_gsi'], 0x43)

def image_load(img):
    rtn = pypin.RTN_FindByName(img, "memset")
    if pypin.RTN_Valid(rtn):
        pypin.RTN_Open(rtn)
        pypin.RTN_InsertCall(pypin.IPOINT_BEFORE, "memset", rtn, 3, memset_pre)
        pypin.RTN_Close(rtn)

    rtn = pypin.RTN_FindByName(img, "malloc")
    if pypin.RTN_Valid(rtn):
        pypin.RTN_Open(rtn)
        #pypin.RTN_InsertCall(pypin.IPOINT_BEFORE, "malloc", rtn, 1, malloc_before)
        #pypin.RTN_InsertCall(pypin.IPOINT_AFTER, "malloc", rtn, 1, malloc_after)
        pypin.RTN_Close(rtn)

    rtn = pypin.RTN_FindByName(img, "free")
    if pypin.RTN_Valid(rtn):
        pypin.RTN_Open(rtn)
        #pypin.RTN_InsertCall(pypin.IPOINT_BEFORE, "malloc", rtn, 1, free)
        pypin.RTN_Close(rtn)

def exiting():
    global allocations
    # print allocations

pypin.IMG_AddInstrumentFunction(image_load)
pypin.INS_AddInstrumentFunction(ins_test)
pypin.AddFiniFunction(exiting)

