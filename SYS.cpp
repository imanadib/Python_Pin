#include "pin.H"
/*
namespace SPPY 
{
#include <Python.h>
}
*/
#include "python_dynamic.h"

SPPY::PyObject* Python_PIN_GetSyscallArgument(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* context;
    SPPY::PyObject* std;
    SPPY::PyObject* number;
    Dyno::PyArg_ParseTuple(args, "O|O|O", &context, &std, &number);

    return Dyno::Py_BuildValue("k", PIN_GetSyscallArgument((CONTEXT*) *(CONTEXT**)Dyno::PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)Dyno::PyInt_AsLong(std), (int) Dyno::PyInt_AsLong(number)));
}

SPPY::PyObject* Python_PIN_GetSyscallReturn(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* context;
    SPPY::PyObject* std;
    Dyno::PyArg_ParseTuple(args, "O|O", &context, &std);

    return Dyno::Py_BuildValue("k", PIN_GetSyscallReturn((CONTEXT*) *(CONTEXT**)Dyno::PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)Dyno::PyInt_AsLong(std)));
}

SPPY::PyObject* Python_PIN_GetSyscallNumber(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* context;
    SPPY::PyObject* std;
    Dyno::PyArg_ParseTuple(args, "O|O", &context, &std);

    return Dyno::Py_BuildValue("k", PIN_GetSyscallNumber((CONTEXT*) *(CONTEXT**)Dyno::PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)Dyno::PyInt_AsLong(std)));
}

SPPY::PyObject* Python_PIN_SetSyscallArgument(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* context;
    SPPY::PyObject* std;
    SPPY::PyObject* number;
    SPPY::PyObject* value;
    Dyno::PyArg_ParseTuple(args, "O|O|O|O", &context, &std, &number, &value);

    PIN_SetSyscallArgument((CONTEXT*) *(CONTEXT**)Dyno::PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)Dyno::PyInt_AsLong(std), (int) Dyno::PyInt_AsLong(number), (ADDRINT) Dyno::PyInt_AsLong(value));
    return Dyno::Py_BuildValue("O", (&Dyno::_Py_NoneStruct));
}

SPPY::PyObject* Python_PIN_SetSyscallNumber(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* context;
    SPPY::PyObject* std;
    SPPY::PyObject* value;
    Dyno::PyArg_ParseTuple(args, "O|O|O", &context, &std, &value);

    PIN_SetSyscallNumber((CONTEXT*) *(CONTEXT**)Dyno::PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)Dyno::PyInt_AsLong(std), (ADDRINT) Dyno::PyInt_AsLong(value));
    return Dyno::Py_BuildValue("O", (&Dyno::_Py_NoneStruct));
}

