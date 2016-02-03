#include "pin.H"

/*namespace SPPY 
{
#include <Python.h>
}*/

#include "python_dynamic.h"

#include "RTN.h"

SPPY::PyObject* get_pointer(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* target;
    Dyno::PyArg_ParseTuple(args, "k", &target);
    return Dyno::PyInt_FromLong(*(ADDRINT*)target);
}

SPPY::PyObject* set_pointer(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* target;
    SPPY::PyObject* value;
    Dyno::PyArg_ParseTuple(args, "O|O", &target, &value);
    ADDRINT* p_target = (ADDRINT*) Dyno::PyInt_AsLong(target);
    ADDRINT p_value = (ADDRINT) Dyno::PyInt_AsLong(value);
    //printf("*%p = %lx\n", p_target, p_value);
    *p_target = p_value;
    return ((SPPY::PyObject *) &Dyno::_Py_TrueStruct);
}


void RTN_IPOINT_AFTER(
        char* name, SPPY::PyObject* callback, long int return_value,
        ADDRINT* reg_gax, ADDRINT* reg_gbx, ADDRINT* reg_gcx, ADDRINT* reg_gdx,
        ADDRINT* reg_gbp, ADDRINT* reg_gsp, ADDRINT* reg_gdi, ADDRINT* reg_gsi
    ) {
    SPPY::PyObject* arguments = Dyno::PyTuple_New(1);

    SPPY::PyObject* everything = Dyno::PyDict_New();
    Dyno::PyDict_SetItemString(everything, "function", Dyno::PyString_FromString(name));
    Dyno::PyDict_SetItemString(everything, "return", Dyno::PyInt_FromLong(return_value));
    Dyno::PyDict_SetItemString(everything, "reg_gax", Dyno::Py_BuildValue("k", reg_gax));
    Dyno::PyDict_SetItemString(everything, "reg_gbx", Dyno::Py_BuildValue("k", reg_gbx));
    Dyno::PyDict_SetItemString(everything, "reg_gcx", Dyno::Py_BuildValue("k", reg_gcx));
    Dyno::PyDict_SetItemString(everything, "reg_gdx", Dyno::Py_BuildValue("k", reg_gdx));
    Dyno::PyDict_SetItemString(everything, "reg_gbp", Dyno::Py_BuildValue("k", reg_gbp));
    Dyno::PyDict_SetItemString(everything, "reg_gsp", Dyno::Py_BuildValue("k", reg_gsp));
    Dyno::PyDict_SetItemString(everything, "reg_gdi", Dyno::Py_BuildValue("k", reg_gdi));
    Dyno::PyDict_SetItemString(everything, "reg_gsi", Dyno::Py_BuildValue("k", reg_gsi));

    Dyno::PyTuple_SetItem(arguments, 0, everything);
    Dyno::PyObject_CallObject(callback, arguments);
}

void RTN_IPOINT_BEFORE(
        char* name, int num_args, SPPY::PyObject* callback,
        long int arg0, long int arg1, long int arg2, long int arg3, long int arg4,
        long int arg5, long int arg6, long int arg7, long int arg8, long int arg9, long int arg10,
        ADDRINT* ref_arg0, ADDRINT* ref_arg1, ADDRINT* ref_arg2, ADDRINT* ref_arg3, ADDRINT* ref_arg4,
        ADDRINT* ref_arg5, ADDRINT* ref_arg6, ADDRINT* ref_arg7, ADDRINT* ref_arg8, ADDRINT* ref_arg9, ADDRINT* ref_arg10,
        ADDRINT* reg_gax, ADDRINT* reg_gbx, ADDRINT* reg_gcx, ADDRINT* reg_gdx,
        ADDRINT* reg_gbp, ADDRINT* reg_gsp, ADDRINT* reg_gdi, ADDRINT* reg_gsi
    ) {
    SPPY::PyObject* arguments = Dyno::PyTuple_New(1);

    SPPY::PyObject* everything = Dyno::PyDict_New();
    Dyno::PyDict_SetItemString(everything, "function", Dyno::PyString_FromString(name));
    Dyno::PyDict_SetItemString(everything, "arg_0", Dyno::PyInt_FromLong(arg0));
    Dyno::PyDict_SetItemString(everything, "arg_1", Dyno::PyInt_FromLong(arg1));
    Dyno::PyDict_SetItemString(everything, "arg_2", Dyno::PyInt_FromLong(arg2));
    Dyno::PyDict_SetItemString(everything, "arg_3", Dyno::PyInt_FromLong(arg3));
    Dyno::PyDict_SetItemString(everything, "arg_4", Dyno::PyInt_FromLong(arg4));
    Dyno::PyDict_SetItemString(everything, "arg_5", Dyno::PyInt_FromLong(arg5));
    Dyno::PyDict_SetItemString(everything, "arg_6", Dyno::PyInt_FromLong(arg6));
    Dyno::PyDict_SetItemString(everything, "arg_7", Dyno::PyInt_FromLong(arg7));
    Dyno::PyDict_SetItemString(everything, "arg_8", Dyno::PyInt_FromLong(arg8));
    Dyno::PyDict_SetItemString(everything, "arg_9", Dyno::PyInt_FromLong(arg9));
    Dyno::PyDict_SetItemString(everything, "arg_10", Dyno::PyInt_FromLong(arg10));
    Dyno::PyDict_SetItemString(everything, "ref_arg_0", Dyno::PyInt_FromLong((long int) ref_arg0));
    Dyno::PyDict_SetItemString(everything, "ref_arg_1", Dyno::PyInt_FromLong((long int) ref_arg1));
    Dyno::PyDict_SetItemString(everything, "ref_arg_2", Dyno::PyInt_FromLong((long int) ref_arg2));
    Dyno::PyDict_SetItemString(everything, "ref_arg_3", Dyno::PyInt_FromLong((long int) ref_arg3));
    Dyno::PyDict_SetItemString(everything, "ref_arg_4", Dyno::PyInt_FromLong((long int) ref_arg4));
    Dyno::PyDict_SetItemString(everything, "ref_arg_5", Dyno::PyInt_FromLong((long int) ref_arg5));
    Dyno::PyDict_SetItemString(everything, "ref_arg_6", Dyno::PyInt_FromLong((long int) ref_arg6));
    Dyno::PyDict_SetItemString(everything, "ref_arg_7", Dyno::PyInt_FromLong((long int) ref_arg7));
    Dyno::PyDict_SetItemString(everything, "ref_arg_8", Dyno::PyInt_FromLong((long int) ref_arg8));
    Dyno::PyDict_SetItemString(everything, "ref_arg_9", Dyno::PyInt_FromLong((long int) ref_arg9));
    Dyno::PyDict_SetItemString(everything, "ref_arg_10", Dyno::PyInt_FromLong((long int) ref_arg10));
    Dyno::PyDict_SetItemString(everything, "reg_gax", Dyno::Py_BuildValue("k", reg_gax));
    Dyno::PyDict_SetItemString(everything, "reg_gbx", Dyno::Py_BuildValue("k", reg_gbx));
    Dyno::PyDict_SetItemString(everything, "reg_gcx", Dyno::Py_BuildValue("k", reg_gcx));
    Dyno::PyDict_SetItemString(everything, "reg_gdx", Dyno::Py_BuildValue("k", reg_gdx));
    Dyno::PyDict_SetItemString(everything, "reg_gbp", Dyno::Py_BuildValue("k", reg_gbp));
    Dyno::PyDict_SetItemString(everything, "reg_gsp", Dyno::Py_BuildValue("k", reg_gsp));
    Dyno::PyDict_SetItemString(everything, "reg_gdi", Dyno::Py_BuildValue("k", reg_gdi));
    Dyno::PyDict_SetItemString(everything, "reg_gsi", Dyno::Py_BuildValue("k", reg_gsi));

    Dyno::PyTuple_SetItem(arguments, 0, everything);

    if (Dyno::PyObject_CallObject(callback, arguments)) {
    } else {
        printf("no\n");
        Dyno::PyErr_Print();
    }
}

SPPY::PyObject* Python_RTN_InsertCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* num_args;
    SPPY::PyObject* function_name;
    SPPY::PyObject* rtn;
    SPPY::PyObject* callable;
    SPPY::PyObject* ipoint;

    Dyno::PyArg_ParseTuple(args, "k|O|k|k|O", &ipoint, &function_name, &rtn, &num_args, &callable);
    if (!Dyno::PyCallable_Check(callable) || (long int) num_args > 10 || (long int) num_args < 0) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }

    //cout << "function_name: " << Dyno::PyString_AsString(function_name) << endl;
    RTN rtn_object = *(RTN*) rtn;
    if ((long int) ipoint == IPOINT_AFTER) {
        RTN_InsertCall(rtn_object, IPOINT_AFTER, (AFUNPTR) RTN_IPOINT_AFTER,
            IARG_ADDRINT, Dyno::PyString_AsString(function_name),
            IARG_PTR, callable,
            IARG_FUNCRET_EXITPOINT_VALUE,
            IARG_REG_REFERENCE, REG_GAX,
            IARG_REG_REFERENCE, REG_GBX,
            IARG_REG_REFERENCE, REG_GCX,
            IARG_REG_REFERENCE, REG_GDX,
            IARG_REG_REFERENCE, REG_GBP,
            IARG_REG_REFERENCE, REG_STACK_PTR,
            IARG_REG_REFERENCE, REG_GDI,
            IARG_REG_REFERENCE, REG_GSI,
            IARG_END);
    } else if ((long int) ipoint == IPOINT_BEFORE) {
        RTN_InsertCall(rtn_object, IPOINT_BEFORE, (AFUNPTR) RTN_IPOINT_BEFORE,
            IARG_ADDRINT, Dyno::PyString_AsString(function_name),
            IARG_ADDRINT, num_args,
            IARG_PTR, callable,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 6,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 7,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 8,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 9,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 10,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 0,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 1,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 2,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 3,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 4,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 5,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 6,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 7,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 8,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 9,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 10,
            IARG_REG_REFERENCE, REG_GAX,
            IARG_REG_REFERENCE, REG_GBX,
            IARG_REG_REFERENCE, REG_GCX,
            IARG_REG_REFERENCE, REG_GDX,
            IARG_REG_REFERENCE, REG_GBP,
            IARG_REG_REFERENCE, REG_STACK_PTR,
            IARG_REG_REFERENCE, REG_GDI,
            IARG_REG_REFERENCE, REG_GSI,
            IARG_END);
    } else {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }

    return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
/*
    for (int i=0; i < PyTuple_Size(args); i++) {
        cur = PyTuple_GetItem(args, i);
        if (PyString_Check(cur)) {
            printf("[str] %s\n", Dyno::PyString_AsString(cur));
        } else if (PyInt_Check(cur)) {
            printf("[int] %ld\n", Dyno::PyInt_AsLong(cur));
        }
    }

    return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));*/
}

SPPY::PyObject* Python_RTN_Next(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    Dyno::PyArg_ParseTuple(args, "k", &x);
    RTN x_object = *(RTN*) x;
    RTN* rtn_return = (RTN*) malloc(sizeof(RTN));
    *rtn_return = RTN_Next(x_object);
    return Dyno::Py_BuildValue("k", rtn_return);
}

SPPY::PyObject* Python_RTN_Prev(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    Dyno::PyArg_ParseTuple(args, "k", &x);
    RTN x_object = *(RTN*) x;
    RTN* rtn_return = (RTN*) malloc(sizeof(RTN));
    *rtn_return = RTN_Prev(x_object);
    return Dyno::Py_BuildValue("k", rtn_return);
}

SPPY::PyObject* Python_RTN_Invalid(SPPY::PyObject* self, SPPY::PyObject* args) {
    RTN* rtn_return = (RTN*) malloc(sizeof(RTN));
    *rtn_return = RTN_Invalid();
    return Dyno::Py_BuildValue("k", rtn_return);
}

SPPY::PyObject* Python_RTN_Valid(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    Dyno::PyArg_ParseTuple(args, "k", &x);
    RTN x_object = *(RTN*) x;
    if (RTN_Valid(x_object)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
    } else {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_RTN_Name(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    Dyno::PyArg_ParseTuple(args, "k", &x);
    RTN x_object = *(RTN*) x;
    return Dyno::Py_BuildValue("s", RTN_Name(x_object).c_str());
}

SPPY::PyObject* Python_RTN_Sym(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    Dyno::PyArg_ParseTuple(args, "k", &x);
    RTN x_object = *(RTN*) x;
    SYM* sym_return = (SYM*) malloc(sizeof(SYM));
    *sym_return = RTN_Sym(x_object);
    return Dyno::Py_BuildValue("k", sym_return);
}

SPPY::PyObject* Python_RTN_Id(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    Dyno::PyArg_ParseTuple(args, "k", &x);
    RTN x_object = *(RTN*) x;
    return Dyno::Py_BuildValue("k", RTN_Id(x_object));
}

SPPY::PyObject* Python_RTN_Range(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    Dyno::PyArg_ParseTuple(args, "k", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    return Dyno::Py_BuildValue("k", RTN_Range(rtn_object));
}

SPPY::PyObject* Python_RTN_Size(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    Dyno::PyArg_ParseTuple(args, "k", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    return Dyno::Py_BuildValue("k", RTN_Size(rtn_object));
}

SPPY::PyObject* Python_RTN_FindNameByAddress(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* address;
    Dyno::PyArg_ParseTuple(args, "k", &address);
    ADDRINT address_object = (ADDRINT) address;
    return Dyno::Py_BuildValue("s", RTN_FindNameByAddress(address_object).c_str());
}

SPPY::PyObject* Python_RTN_FindByAddress(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* address;
    Dyno::PyArg_ParseTuple(args, "k", &address);
    ADDRINT address_object = (ADDRINT) address;
    RTN* rtn_return = (RTN*) malloc(sizeof(RTN));
    *rtn_return = RTN_FindByAddress(address_object);
    return Dyno::Py_BuildValue("k", rtn_return);
}

SPPY::PyObject* Python_RTN_FindByName(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    SPPY::PyObject* name;
    Dyno::PyArg_ParseTuple(args, "k|O", &img, &name);
    IMG img_object = *(IMG*) img;
    char* name_object = Dyno::PyString_AsString(name);
    RTN* rtn_return = (RTN*) malloc(sizeof(RTN));
    *rtn_return = RTN_FindByName(img_object, name_object);
    return Dyno::Py_BuildValue("k", rtn_return);
}

SPPY::PyObject* Python_RTN_Open(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    Dyno::PyArg_ParseTuple(args, "k", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    RTN_Open(rtn_object);
    return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
}

SPPY::PyObject* Python_RTN_Close(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    Dyno::PyArg_ParseTuple(args, "k", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    RTN_Close(rtn_object);
    return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
}

SPPY::PyObject* Python_RTN_InsHead(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    Dyno::PyArg_ParseTuple(args, "k", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    INS* ins_return = (INS*) malloc(sizeof(INS));
    *ins_return = RTN_InsHead(rtn_object);
    return Dyno::Py_BuildValue("k", ins_return);
}

SPPY::PyObject* Python_RTN_InsHeadOnly(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    Dyno::PyArg_ParseTuple(args, "k", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    INS* ins_return = (INS*) malloc(sizeof(INS));
    *ins_return = RTN_InsHeadOnly(rtn_object);
    return Dyno::Py_BuildValue("k", ins_return);
}

SPPY::PyObject* Python_RTN_InsTail(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    Dyno::PyArg_ParseTuple(args, "k", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    INS* ins_return = (INS*) malloc(sizeof(INS));
    *ins_return = RTN_InsTail(rtn_object);
    return Dyno::Py_BuildValue("k", ins_return);
}

SPPY::PyObject* Python_RTN_NumIns(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    Dyno::PyArg_ParseTuple(args, "k", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    return Dyno::Py_BuildValue("k", RTN_NumIns(rtn_object));
}

SPPY::PyObject* Python_RTN_Address(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    Dyno::PyArg_ParseTuple(args, "k", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    return Dyno::Py_BuildValue("k", RTN_Address(rtn_object));
}

SPPY::PyObject* Python_RTN_CreateAt(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* address;
    SPPY::PyObject* name;
    Dyno::PyArg_ParseTuple(args, "k|s", &address, &name);
    ADDRINT address_object = (ADDRINT) address;
    char* name_object = Dyno::PyString_AsString(name);
    RTN* rtn_return = (RTN*) malloc(sizeof(RTN));
    *rtn_return = RTN_CreateAt(address_object, name_object);
    return Dyno::Py_BuildValue("k", rtn_return);
}

SPPY::PyObject* Python_RTN_IsDynamic(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    Dyno::PyArg_ParseTuple(args, "k", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    if (RTN_IsDynamic(rtn_object)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
    } else {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_RTN_IsSafeForProbedInsertion(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    Dyno::PyArg_ParseTuple(args, "k", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    if (RTN_IsSafeForProbedInsertion(rtn_object)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
    } else {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_RTN_IsSafeForProbedInsertionEx(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    SPPY::PyObject* mode;
    Dyno::PyArg_ParseTuple(args, "k|k", &rtn, &mode);
    RTN rtn_object = *(RTN*) rtn;
    PROBE_MODE mode_object = *(PROBE_MODE*) mode;
    if (RTN_IsSafeForProbedInsertionEx(rtn_object, mode_object)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
    } else {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_RTN_IsSafeForProbedReplacement(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    Dyno::PyArg_ParseTuple(args, "k", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    if (RTN_IsSafeForProbedReplacement(rtn_object)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
    } else {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_RTN_IsSafeForProbedReplacementEx(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* rtn;
    SPPY::PyObject* mode;
    Dyno::PyArg_ParseTuple(args, "k|k", &rtn, &mode);
    RTN rtn_object = *(RTN*) rtn;
    PROBE_MODE mode_object = *(PROBE_MODE*) mode;
    if (RTN_IsSafeForProbedReplacementEx(rtn_object, mode_object)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
    } else {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }
}