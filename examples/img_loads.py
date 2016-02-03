import pypin

def load(img):
    if pypin.IMG_IsMainExecutable(img):
        print "Main executable loaded %s at %s" % (pypin.IMG_Name(img), hex(pypin.IMG_StartAddress(img)))
    else:
        print "Loaded %s at %s" % (pypin.IMG_Name(img), hex(pypin.IMG_StartAddress(img)))

    img_type = pypin.IMG_Type(img)
    if img_type == pypin.IMG_TYPE_STATIC:
        print "IMG_TYPE_STATIC"
    elif img_type == pypin.IMG_TYPE_SHARED:
        print "IMG_TYPE_SHARED"
    elif img_type == pypin.IMG_TYPE_SHAREDLIB:
        print "IMG_TYPE_SHAREDLIB"
    elif img_type == pypin.IMG_TYPE_RELOCATABLE:
        print "IMG_TYPE_RELOCATABLE"
    else:
        print "unknown type"

def unload(img):
    print "Unloaded %s" % (pypin.IMG_Name(img))

pypin.IMG_AddInstrumentFunction(load)
pypin.IMG_AddUnloadFunction(unload)
