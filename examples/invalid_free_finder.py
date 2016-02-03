import pypin, sys

allocated_buffers = []

def malloc_before(a=None, b=None, c=None, d=None):
    sys.stdout.write("%s(%s) = "%(a, (hex(b))))

def malloc_after(a=None, b=None):
    print "0x%x" % (b)
    allocated_buffers.append(b)

def free(a, b):
    if b == 0:
        print "free(NULL) detected"
        return

    if b in allocated_buffers:
        "Freeing %s"%(hex(b))
        allocated_buffers.remove(b)
    else:
        print "freeing something that wasn't malloc'd (%d)" % (b)

def image_load(img):
    rtn = pypin.RTN_FindByName(img, "malloc")
    if pypin.RTN_Valid(rtn):
        pypin.RTN_Open(rtn)
        pypin.RTN_InsertCall(pypin.IPOINT_BEFORE, "malloc", rtn, 1, malloc_before)
        pypin.RTN_InsertCall(pypin.IPOINT_AFTER, "malloc", rtn, 1, malloc_after)
        pypin.RTN_Close(rtn)

    rtn = pypin.RTN_FindByName(img, "free")
    if pypin.RTN_Valid(rtn):
        pypin.RTN_Open(rtn)
        pypin.RTN_InsertCall(pypin.IPOINT_BEFORE, "malloc", rtn, 1, free)
        pypin.RTN_Close(rtn)

pypin.IMG_AddInstrumentFunction(image_load)
