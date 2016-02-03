

#include "pin.H"
#include "python_dynamic.h"
#include "IMG.h"
#include "INS.h"
#include "RTN.h"
#include "SYS.h"
#include "TRACE.h"
#include "./python_pin.h"
#include <string.h>
#include <stdlib.h>

void add_hook(SPPY::PyObject*** hooks, SPPY::PyObject* new_hook) {
    SPPY::PyObject** hooks_list = *hooks;
    if (hooks_list == NULL) {
        hooks_list = (SPPY::PyObject**) malloc(sizeof(SPPY::PyObject*)*2);
        hooks_list[0] = new_hook;
        hooks_list[1] = NULL;
    } else {
        int hook_count;
        for(hook_count=0; hooks_list[hook_count]; hook_count++);
        hooks_list = (SPPY::PyObject**) realloc(hooks_list, sizeof(SPPY::PyObject*)*(hook_count+2));
        hooks_list[hook_count] = new_hook;
        hooks_list[hook_count+1] = NULL;
    }

    *hooks = hooks_list;
}

void Fini(INT32, VOID*) {
    for (int i=0; fini_functions[i]; i++) {
        if (Dyno::PyObject_CallObject(fini_functions[i], NULL) == NULL) {
            Dyno::PyErr_Print();
            exit(1);
        }
    }
    return;
}

SPPY::PyObject* Python_AddFiniFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback;
    SPPY::PyObject* v;
    Dyno::PyArg_ParseTuple(args, "O|O", &callback, &v);

    if (!Dyno::PyCallable_Check(callback)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }

    add_hook(&fini_functions, callback);
    return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
} 

SPPY::PyObject* Python_TRACE_AddInstrumentFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback;
    SPPY::PyObject* v;
    Dyno::PyArg_ParseTuple(args, "O|O", &callback, &v);

    if (!Dyno::PyCallable_Check(callback)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }

    add_hook(&hooks_trace_instrument, callback);
    return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
} 

SPPY::PyObject* Python_INS_AddInstrumentFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback;
    SPPY::PyObject* v;
    Dyno::PyArg_ParseTuple(args, "O|O", &callback, &v);

    if (!Dyno::PyCallable_Check(callback)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }

    add_hook(&hooks_instruction, callback);
    return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
} 

SPPY::PyObject* Python_IMG_AddInstrumentFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback;
    SPPY::PyObject* v;
    Dyno::PyArg_ParseTuple(args, "O|O", &callback, &v);

    if (!Dyno::PyCallable_Check(callback)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }

    add_hook(&hooks_img_load, callback);
    return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
}

SPPY::PyObject* Python_IMG_AddUnloadFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback;
    SPPY::PyObject* v;
    Dyno::PyArg_ParseTuple(args, "O|O", &callback, &v);

    if (!Dyno::PyCallable_Check(callback)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }

    add_hook(&hooks_img_unload, callback);
    return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
}

SPPY::PyObject* Python_RTN_AddInstrumentFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback = (SPPY::PyObject*) malloc(sizeof(SPPY::PyObject));
    Dyno::PyArg_ParseTuple(args, "O", &callback);

    if (!Dyno::PyCallable_Check(callback)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }

    add_hook(&hooks_instrument_function, callback);
    return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
}



SPPY::PyObject* Python_PIN_AddSyscallExitFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback = (SPPY::PyObject*) malloc(sizeof(SPPY::PyObject));
    Dyno::PyArg_ParseTuple(args, "O", &callback);

    if (!Dyno::PyCallable_Check(callback)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }

    add_hook(&hooks_syscall_exit, callback);
    return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
}

SPPY::PyObject* Python_PIN_AddSyscallEntryFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback = (SPPY::PyObject*) malloc(sizeof(SPPY::PyObject));
    Dyno::PyArg_ParseTuple(args, "O", &callback);

    if (!Dyno::PyCallable_Check(callback)) {
        return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_ZeroStruct));
    }

    add_hook(&hooks_syscall_entry, callback);
    return Dyno::Py_BuildValue("O", ((SPPY::PyObject *) &Dyno::_Py_TrueStruct));
}

KNOB<string> KnobPythonModule(KNOB_MODE_WRITEONCE, "pintool", "m", "", "the python pintool to import");
int main(int argc, char** argv) {
	if (Dyno::DynamicPythonSyscall_Init() == false){
		return 0;
	}
	PIN_InitSymbols();
	Dyno::Py_Initialize();
	 //SPPY::PyRun_SimpleString("import sys; sys.path.append('.')\n");
	Dyno::PyRun_SimpleStringFlags("import sys; sys.path.append('.')\n", NULL);
    if (PIN_Init(argc, argv)) {
        printf("Failed to initialize pin.\n");
        exit(1);
    }

	SPPY::PyObject* pin_module =
		Dyno::Py_InitModule4("pin", methods, (char *)NULL, (SPPY::PyObject *)NULL, PYTHON_API_VERSION);
    //SPPY::PyObject* pin_module = Py_InitModule("pin", methods);
    if (pin_module == NULL) {
        printf("Failed to initialize internal pin module\n");
        Dyno::PyErr_Print();
        exit(1);
    }

    Dyno::PyModule_AddIntConstant(pin_module, "IPOINT_BEFORE", IPOINT_BEFORE);
    Dyno::PyModule_AddIntConstant(pin_module, "IPOINT_AFTER", IPOINT_AFTER);
    Dyno::PyModule_AddIntConstant(pin_module, "IMG_TYPE_STATIC", IMG_TYPE_STATIC);
    Dyno::PyModule_AddIntConstant(pin_module, "IMG_TYPE_SHARED", IMG_TYPE_SHARED);
    Dyno::PyModule_AddIntConstant(pin_module, "IMG_TYPE_SHAREDLIB", IMG_TYPE_SHAREDLIB);
    Dyno::PyModule_AddIntConstant(pin_module, "IMG_TYPE_RELOCATABLE", IMG_TYPE_RELOCATABLE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_INVALID", IARG_INVALID);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_ADDRINT", IARG_ADDRINT);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_PTR", IARG_PTR);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_BOOL", IARG_BOOL);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_UINT32", IARG_UINT32);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_INST_PTR", IARG_INST_PTR);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_REG_VALUE", IARG_REG_VALUE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_REG_REFERENCE", IARG_REG_REFERENCE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_REG_CONST_REFERENCE", IARG_REG_CONST_REFERENCE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_MEMORYREAD_EA", IARG_MEMORYREAD_EA);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_MEMORYREAD2_EA", IARG_MEMORYREAD2_EA);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_MEMORYWRITE_EA", IARG_MEMORYWRITE_EA);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_MEMORYREAD_SIZE", IARG_MEMORYREAD_SIZE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_MEMORYWRITE_SIZE", IARG_MEMORYWRITE_SIZE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_BRANCH_TAKEN", IARG_BRANCH_TAKEN);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_BRANCH_TARGET_ADDR", IARG_BRANCH_TARGET_ADDR);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_FALLTHROUGH_ADDR", IARG_FALLTHROUGH_ADDR);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_EXECUTING", IARG_EXECUTING);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_FIRST_REP_ITERATION", IARG_FIRST_REP_ITERATION);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_PREDICATE", IARG_PREDICATE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_STACK_VALUE", IARG_STACK_VALUE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_STACK_REFERENCE", IARG_STACK_REFERENCE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_MEMORY_VALUE", IARG_MEMORY_VALUE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_MEMORY_REFERENCE", IARG_MEMORY_REFERENCE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_NUMBER", IARG_SYSCALL_NUMBER);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_SYSARG_REFERENCE", IARG_SYSARG_REFERENCE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_SYSARG_VALUE", IARG_SYSARG_VALUE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_SYSRET_VALUE", IARG_SYSRET_VALUE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_SYSRET_ERRNO", IARG_SYSRET_ERRNO);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_FUNCARG_CALLSITE_REFERENCE", IARG_FUNCARG_CALLSITE_REFERENCE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_FUNCARG_CALLSITE_VALUE", IARG_FUNCARG_CALLSITE_VALUE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_FUNCARG_ENTRYPOINT_REFERENCE", IARG_FUNCARG_ENTRYPOINT_REFERENCE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_FUNCARG_ENTRYPOINT_VALUE", IARG_FUNCARG_ENTRYPOINT_VALUE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_FUNCRET_EXITPOINT_REFERENCE", IARG_FUNCRET_EXITPOINT_REFERENCE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_FUNCRET_EXITPOINT_VALUE", IARG_FUNCRET_EXITPOINT_VALUE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_RETURN_IP", IARG_RETURN_IP);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_ORIG_FUNCPTR", IARG_ORIG_FUNCPTR);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_PROTOTYPE", IARG_PROTOTYPE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_THREAD_ID", IARG_THREAD_ID);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_CONTEXT", IARG_CONTEXT);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_CONST_CONTEXT", IARG_CONST_CONTEXT);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_PARTIAL_CONTEXT", IARG_PARTIAL_CONTEXT);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_PRESERVE", IARG_PRESERVE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_RETURN_REGS", IARG_RETURN_REGS);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_CALL_ORDER", IARG_CALL_ORDER);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_REG_NAT_VALUE", IARG_REG_NAT_VALUE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_REG_OUTPUT_FRAME_VALUE", IARG_REG_OUTPUT_FRAME_VALUE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_REG_OUTPUT_FRAME_REFERENCE", IARG_REG_OUTPUT_FRAME_REFERENCE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_IARGLIST", IARG_IARGLIST);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_FAST_ANALYSIS_CALL", IARG_FAST_ANALYSIS_CALL);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARG0", IARG_SYSCALL_ARG0);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARGBASE", IARG_SYSCALL_ARGBASE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARG1", IARG_SYSCALL_ARG1);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARG2", IARG_SYSCALL_ARG2);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARG3", IARG_SYSCALL_ARG3);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARG4", IARG_SYSCALL_ARG4);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARG5", IARG_SYSCALL_ARG5);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARGLAST", IARG_SYSCALL_ARGLAST);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_RESULT0", IARG_G_RESULT0);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_RETBASE", IARG_G_RETBASE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_RESULTLAST", IARG_G_RESULTLAST);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARG0_CALLEE", IARG_G_ARG0_CALLEE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARGBASE_CALLEE", IARG_G_ARGBASE_CALLEE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARG1_CALLEE", IARG_G_ARG1_CALLEE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARG2_CALLEE", IARG_G_ARG2_CALLEE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARG3_CALLEE", IARG_G_ARG3_CALLEE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARG4_CALLEE", IARG_G_ARG4_CALLEE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARG5_CALLEE", IARG_G_ARG5_CALLEE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARGLAST_CALLEE", IARG_G_ARGLAST_CALLEE);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARG0_CALLER", IARG_G_ARG0_CALLER);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARGBASE_CALLER", IARG_G_ARGBASE_CALLER);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARG1_CALLER", IARG_G_ARG1_CALLER);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARG2_CALLER", IARG_G_ARG2_CALLER);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARG3_CALLER", IARG_G_ARG3_CALLER);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARG4_CALLER", IARG_G_ARG4_CALLER);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARG5_CALLER", IARG_G_ARG5_CALLER);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_G_ARGLAST_CALLER", IARG_G_ARGLAST_CALLER);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_MEMORYOP_EA", IARG_MEMORYOP_EA);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_FILE_NAME", IARG_FILE_NAME);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_LINE_NO", IARG_LINE_NO);
    Dyno::PyModule_AddIntConstant(pin_module, "IARG_LAST", IARG_LAST);
    Dyno::PyModule_AddIntConstant(pin_module, "CALL_ORDER_FIRST", CALL_ORDER_FIRST);
    Dyno::PyModule_AddIntConstant(pin_module, "CALL_ORDER_DEFAULT", CALL_ORDER_DEFAULT);
    Dyno::PyModule_AddIntConstant(pin_module, "CALL_ORDER_LAST", CALL_ORDER_LAST);
    Dyno::PyModule_AddIntConstant(pin_module, "CALL_ORDER_FIRST", CALL_ORDER_FIRST);
    Dyno::PyModule_AddIntConstant(pin_module, "CALL_ORDER_DEFAULT", CALL_ORDER_DEFAULT);
    Dyno::PyModule_AddIntConstant(pin_module, "CALL_ORDER_LAST", CALL_ORDER_LAST);

     const char* filename = KnobPythonModule.Value().c_str();
//     FILE* tool = fopen(filename, "r");
//     if (tool == NULL) {
//         perror("fopen");
//         exit(1);
//     }
// 
//     SPPY::PyRun_SimpleFile(tool, filename);
//     fclose(tool);

	 SPPY::PyObject* PyFileObject = Dyno::PyFile_FromString((char *)filename, "r");
	 //SPPY::PyRun_SimpleFile(PyFile_AsFile(PyFileObject), filename);
	 Dyno::PyRun_SimpleFileExFlags(Dyno::PyFile_AsFile(PyFileObject), filename, 0, NULL);

    if (fini_functions) {
        PIN_AddFiniFunction(Fini, 0);
    }

    if (hooks_syscall_entry) {
        PIN_AddSyscallEntryFunction(SyscallEntry, 0);
    }

    if (hooks_syscall_exit) {
        PIN_AddSyscallEntryFunction(SyscallExit, 0);
    }

    if (hooks_instrument_function) {
        RTN_AddInstrumentFunction(InstrumentFunction, 0);
    }

    if (hooks_img_load) {
        IMG_AddInstrumentFunction(ImageLoad, 0);
    }

    if (hooks_img_unload) {
        IMG_AddUnloadFunction(ImageUnload, 0);
    }

    if (hooks_trace_instrument) {
        TRACE_AddInstrumentFunction(Trace, 0);
    }
    if (hooks_instruction) {
        INS_AddInstrumentFunction(Ins_Hook, 0);
    }

    PIN_StartProgram();

	//SPPY::Py_Finalize();
	Dyno::Py_Finalize();
    return 0;
}

void Ins_Hook(INS ins, VOID *v){
    SPPY::PyObject* arguments = Dyno::PyTuple_New(1);
    Dyno::PyTuple_SetItem(arguments, 0, Dyno::PyInt_FromLong((long int)&ins));

    for (int i=0; hooks_instruction[i]; i++) {
        if (Dyno::PyObject_CallObject(hooks_instruction[i], arguments) == NULL) {
            Dyno::PyErr_Print();
            exit(1);
        }
    }
    return;
}

void Trace(TRACE trace, VOID *v){
    SPPY::PyObject* arguments = Dyno::PyTuple_New(1);
    Dyno::PyTuple_SetItem(arguments, 0, Dyno::PyInt_FromLong((long int)&trace));

    for (int i=0; hooks_trace_instrument[i]; i++) {
        if (Dyno::PyObject_CallObject(hooks_trace_instrument[i], arguments) == NULL) {
            Dyno::PyErr_Print();
            exit(1);
        }
    }
    return;
}

void InstrumentFunction(RTN rtn, VOID *v) {
    SPPY::PyObject* arguments = Dyno::PyTuple_New(1);
    Dyno::PyTuple_SetItem(arguments, 0, Dyno::PyInt_FromLong((long int)&rtn));

    for (int i=0; hooks_instrument_function[i]; i++) {
        if (Dyno::PyObject_CallObject(hooks_instrument_function[i], arguments) == NULL) {
            Dyno::PyErr_Print();
            exit(1);
        }
    }
}

void SyscallExit(THREADID threadIndex, CONTEXT *ctxt, SYSCALL_STANDARD std, VOID *v) {
    SPPY::PyObject* arguments = Dyno::PyTuple_New(2);
    Dyno::PyTuple_SetItem(arguments, 0, Dyno::PyInt_FromLong((long int)&ctxt));
    Dyno::PyTuple_SetItem(arguments, 1, Dyno::PyInt_FromLong((long int)&std));

    for (int i=0; hooks_syscall_entry[i]; i++) {
        if (Dyno::PyObject_CallObject(hooks_syscall_exit[i], arguments) == NULL) {
            Dyno::PyErr_Print();
            exit(1);
        }
    }
}

void SyscallEntry(THREADID threadIndex, CONTEXT *ctxt, SYSCALL_STANDARD std, VOID *v) {
    SPPY::PyObject* arguments = Dyno::PyTuple_New(2);
    Dyno::PyTuple_SetItem(arguments, 0, Dyno::PyInt_FromLong((long int)&ctxt));
    Dyno::PyTuple_SetItem(arguments, 1, Dyno::PyInt_FromLong((long int)&std));

    for (int i=0; hooks_syscall_entry[i]; i++) {
        if (Dyno::PyObject_CallObject(hooks_syscall_entry[i], arguments) == NULL) {
            Dyno::PyErr_Print();
            exit(1);
        }
    }
}

void ImageLoad(IMG img, VOID *v) {
    SPPY::PyObject* arguments = Dyno::PyTuple_New(1);
    Dyno::PyTuple_SetItem(arguments, 0, Dyno::PyInt_FromLong((long int)&img));

    for (int i=0; hooks_img_load[i]; i++) {
        if (Dyno::PyObject_CallObject(hooks_img_load[i], arguments) == NULL) {
            Dyno::PyErr_Print();
            exit(1);
        }
    }
}

void ImageUnload(IMG img, VOID* v) {
    SPPY::PyObject* arguments = Dyno::PyTuple_New(1);
    Dyno::PyTuple_SetItem(arguments, 0, Dyno::PyInt_FromLong((long int)&img));

    for (int i=0; hooks_img_unload[i]; i++) {
        if (Dyno::PyObject_CallObject(hooks_img_unload[i], arguments) == NULL) {
            Dyno::PyErr_Print();
            exit(1);
        }
    }
}
