#pragma once
#include <stdio.h>

namespace SPPY{
#include <Python.h>
#include <Windows.h>
}
namespace WINDOWS{

}
namespace Dyno{
	typedef int(*PyArg_ParseTuple_Ptr)(SPPY::PyObject *, const char *, ...);
	typedef int(*PyDict_SetItemString_Ptr)(SPPY::PyObject *dp, const char *key, SPPY::PyObject *item);
	typedef SPPY::PyObject*(*PyString_FromString_Ptr)(const char *);
	typedef void(*PyErr_Print_Ptr)(void);
	typedef int(*PyRun_SimpleFileExFlags_Ptr)(FILE *, const char *, int, SPPY::PyCompilerFlags *);
	typedef int(*PyRun_SimpleStringFlags_Ptr)(const char *, SPPY::PyCompilerFlags *);
	typedef void(*Py_Finalize_Ptr)(void);
	typedef void(*Py_Initialize_Ptr)(void);
	typedef SPPY::PyObject*(*Py_InitModule4_Ptr)(const char *name, SPPY::PyMethodDef *methods, const char *doc, SPPY::PyObject *self, int apiver);
	typedef int(*PyModule_AddIntConstant_Ptr)(SPPY::PyObject *, const char *, long);
	typedef FILE*(*PyFile_AsFile_Ptr)(SPPY::PyObject *);
	typedef SPPY::PyObject*(*PyFile_FromString_Ptr)(char *, char *);

	typedef SPPY::PyObject*(*PyInt_FromLong_Ptr)(long);
	typedef SPPY::PyObject*(*PyObject_CallObject_Ptr)(SPPY::PyObject *callable_object, SPPY::PyObject *args);
	typedef SPPY::PyObject*(*PyDict_New_Ptr)(void);
	typedef int(*PyTuple_SetItem_Ptr)(SPPY::PyObject *, SPPY::Py_ssize_t, SPPY::PyObject *);
	typedef SPPY::PyObject*(*PyTuple_New_Ptr)(SPPY::Py_ssize_t size);
	typedef int(*PyCallable_Check_Ptr)(SPPY::PyObject *);

	typedef SPPY::PyObject*(*Py_BuildValue_Ptr)(const char *, ...);
	typedef char*(*PyString_AsString_Ptr)(SPPY::PyObject *);
	typedef long(*PyInt_AsLong_Ptr)(SPPY::PyObject *);

	typedef SPPY::PyObject(*_Py_NoneStruct_Ptr)();
	typedef SPPY::PyIntObject(*_Py_TrueStruct_Ptr)();
	typedef SPPY::PyIntObject(*_Py_ZeroStruct_Ptr)();

	static PyArg_ParseTuple_Ptr PyArg_ParseTuple = NULL;
	static PyDict_SetItemString_Ptr PyDict_SetItemString = NULL;
	static PyString_FromString_Ptr PyString_FromString = NULL;
	static PyErr_Print_Ptr PyErr_Print = NULL;
	static PyRun_SimpleFileExFlags_Ptr PyRun_SimpleFileExFlags = NULL;
	static PyRun_SimpleStringFlags_Ptr PyRun_SimpleStringFlags = NULL;
	static Py_Finalize_Ptr Py_Finalize = NULL;
	static Py_Initialize_Ptr Py_Initialize = NULL;
	static Py_InitModule4_Ptr Py_InitModule4 = NULL;
	static PyModule_AddIntConstant_Ptr PyModule_AddIntConstant = NULL;
	static PyFile_AsFile_Ptr PyFile_AsFile = NULL;
	static PyFile_FromString_Ptr PyFile_FromString = NULL;

	static PyInt_FromLong_Ptr PyInt_FromLong = NULL;
	static PyObject_CallObject_Ptr PyObject_CallObject = NULL;
	static PyDict_New_Ptr PyDict_New = NULL;
	static PyTuple_SetItem_Ptr PyTuple_SetItem = NULL;
	static PyTuple_New_Ptr PyTuple_New = NULL;
	static PyCallable_Check_Ptr PyCallable_Check = NULL;

	static Py_BuildValue_Ptr Py_BuildValue = NULL;
	static PyString_AsString_Ptr PyString_AsString = NULL;
	static PyInt_AsLong_Ptr PyInt_AsLong = NULL;

	static _Py_NoneStruct_Ptr _Py_NoneStruct = NULL;
	static _Py_TrueStruct_Ptr _Py_TrueStruct = NULL;
	static _Py_ZeroStruct_Ptr _Py_ZeroStruct = NULL;



	static bool DynamicPythonSyscall_Init(){

		SPPY::HMODULE pythonModule = SPPY::LoadLibraryW(L"python27.dll");
		if (pythonModule == NULL)
			return false;
		PyArg_ParseTuple = (PyArg_ParseTuple_Ptr)SPPY::GetProcAddress(pythonModule, "PyArg_ParseTuple");
		PyDict_SetItemString = (PyDict_SetItemString_Ptr)SPPY::GetProcAddress(pythonModule, "PyDict_SetItemString");
		PyString_FromString = (PyString_FromString_Ptr)SPPY::GetProcAddress(pythonModule, "PyString_FromString");
		PyErr_Print = (PyErr_Print_Ptr)SPPY::GetProcAddress(pythonModule, "PyErr_Print");
		PyRun_SimpleFileExFlags = (PyRun_SimpleFileExFlags_Ptr)SPPY::GetProcAddress(pythonModule, "PyRun_SimpleFileExFlags");
		PyRun_SimpleStringFlags = (PyRun_SimpleStringFlags_Ptr)SPPY::GetProcAddress(pythonModule, "PyRun_SimpleStringFlags");
		Py_Finalize = (Py_Finalize_Ptr)SPPY::GetProcAddress(pythonModule, "Py_Finalize");
		Py_Initialize = (Py_Initialize_Ptr)SPPY::GetProcAddress(pythonModule, "Py_Initialize");
		Py_InitModule4 = (Py_InitModule4_Ptr)SPPY::GetProcAddress(pythonModule, "Py_InitModule4_64");
		PyModule_AddIntConstant = (PyModule_AddIntConstant_Ptr)SPPY::GetProcAddress(pythonModule, "PyModule_AddIntConstant");
		PyFile_AsFile = (PyFile_AsFile_Ptr)SPPY::GetProcAddress(pythonModule, "PyFile_AsFile");
		PyFile_FromString = (PyFile_FromString_Ptr)SPPY::GetProcAddress(pythonModule, "PyFile_FromString");

		PyInt_FromLong = (PyInt_FromLong_Ptr)SPPY::GetProcAddress(pythonModule, "PyInt_FromLong");
		PyObject_CallObject = (PyObject_CallObject_Ptr)SPPY::GetProcAddress(pythonModule, "PyObject_CallObject");
		PyDict_New = (PyDict_New_Ptr)SPPY::GetProcAddress(pythonModule, "PyDict_New");
		PyTuple_SetItem = (PyTuple_SetItem_Ptr)SPPY::GetProcAddress(pythonModule, "PyTuple_SetItem");
		PyTuple_New = (PyTuple_New_Ptr)SPPY::GetProcAddress(pythonModule, "PyTuple_New");
		PyCallable_Check = (PyCallable_Check_Ptr)SPPY::GetProcAddress(pythonModule, "PyCallable_Check");

		Py_BuildValue = (Py_BuildValue_Ptr)SPPY::GetProcAddress(pythonModule, "Py_BuildValue");
		PyString_AsString = (PyString_AsString_Ptr)SPPY::GetProcAddress(pythonModule, "PyString_AsString");
		PyInt_AsLong = (PyInt_AsLong_Ptr)SPPY::GetProcAddress(pythonModule, "PyInt_AsLong");


		_Py_NoneStruct = (_Py_NoneStruct_Ptr)SPPY::GetProcAddress(pythonModule, "_Py_NoneStruct");
		_Py_TrueStruct = (_Py_TrueStruct_Ptr)SPPY::GetProcAddress(pythonModule, "_Py_TrueStruct");
		_Py_ZeroStruct = (_Py_ZeroStruct_Ptr)SPPY::GetProcAddress(pythonModule, "_Py_ZeroStruct");
		
		
		if (PyArg_ParseTuple == NULL || PyDict_SetItemString == NULL || PyString_FromString == NULL || PyErr_Print == NULL || PyRun_SimpleFileExFlags == NULL || PyRun_SimpleStringFlags == NULL || Py_Finalize == NULL || Py_Initialize == NULL || Py_InitModule4 == NULL || PyModule_AddIntConstant == NULL || PyFile_AsFile == NULL || PyFile_FromString == NULL){
			return false;
		}

		if (PyInt_FromLong == NULL || PyObject_CallObject == NULL || PyDict_New == NULL || PyTuple_SetItem == NULL || PyTuple_New == NULL || PyCallable_Check == NULL){
			return false;
		}

		if (Py_BuildValue == NULL || PyString_AsString == NULL || PyInt_AsLong == NULL){
			return false;
		}

		//
		if (_Py_NoneStruct == NULL || _Py_TrueStruct == NULL || _Py_ZeroStruct == NULL){
			return false;
		}

		return true;
	}
}

/*
PTEB
WINDOWS::HMODULE pythonModule = WINDOWS::LoadLibraryW(L"python27.dll");
if (pythonModule == NULL)
return false;
MPyArg_ParseTuple = WINDOWS::GetProcAddress(pythonModule, "PyArg_ParseTuple");
MPyDict_SetItemString = WINDOWS::GetProcAddress(pythonModule, "PyDict_SetItemString");
MPyString_FromString = WINDOWS::GetProcAddress(pythonModule, "PyString_FromString");
MPyErr_Print = WINDOWS::GetProcAddress(pythonModule, "PyErr_Print");
MPyRun_SimpleFileExFlags = WINDOWS::GetProcAddress(pythonModule, "PyRun_SimpleFileExFlags");
MPyRun_SimpleStringFlags = WINDOWS::GetProcAddress(pythonModule, "PyRun_SimpleStringFlags");
MPy_Finalize = WINDOWS::GetProcAddress(pythonModule, "Py_Finalize");
MPy_Initialize = WINDOWS::GetProcAddress(pythonModule, "Py_Initialize");
MPy_InitModule4 = WINDOWS::GetProcAddress(pythonModule, "Py_InitModule4_64");
MPyModule_AddIntConstant = WINDOWS::GetProcAddress(pythonModule, "PyModule_AddIntConstant");
MPyFile_AsFile = WINDOWS::GetProcAddress(pythonModule, "PyFile_AsFile");
MPyFile_FromString = WINDOWS::GetProcAddress(pythonModule, "PyFile_FromString");
if (MPyArg_ParseTuple == NULL || MPyDict_SetItemString == NULL || MPyString_FromString == NULL || MPyErr_Print == NULL || MPyRun_SimpleFileExFlags == NULL || MPyRun_SimpleStringFlags == NULL || MPy_Finalize == NULL || MPy_Initialize == NULL || MPy_InitModule4 == NULL || MPyModule_AddIntConstant == NULL || MPyFile_AsFile == NULL || MPyFile_FromString == NULL){
return false;
}


typedef unsigned char uchar_t;
typedef unsigned short ushort_t;
typedef unsigned long ulong_t;

typedef void (__stdcall *PPS_POST_PROCESS_INIT_ROUTINE) (void);

typedef struct _UNICODE_STRING {
ushort_t Length;
ushort_t MaximumLength;
wchar_t*  Buffer;
} UNICODE_STRING;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
uchar_t Reserved1[16];
void* Reserved2[10];
UNICODE_STRING ImagePathName;
UNICODE_STRING CommandLine;
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef struct _LIST_ENTRY {
struct _LIST_ENTRY *Flink;
struct _LIST_ENTRY *Blink;
} LIST_ENTRY, *PLIST_ENTRY;

typedef struct _PEB_LDR_DATA {
uchar_t Reserved1[8];
void* Reserved2[3];
LIST_ENTRY InMemoryOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _PEB {
uchar_t Reserved1[2];
uchar_t BeingDebugged;
uchar_t Reserved2[1];
void* Reserved3[2];
PPEB_LDR_DATA Ldr;
PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
void* Reserved4[3];
void* AtlThunkSListPtr;
void* Reserved5;
ulong_t Reserved6;
void* Reserved7;
ulong_t Reserved8;
ulong_t AtlThunkSListPtr32;
void* Reserved9[45];
uchar_t Reserved10[96];
PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;
uchar_t Reserved11[128];
void* Reserved12[1];
ulong_t SessionId;
} PEB, *PPEB;


typedef struct _TEB {
void* Reserved1[12];
PPEB ProcessEnvironmentBlock;
void* Reserved2[399];
uchar_t Reserved3[1952];
void* TlsSlots[64];
uchar_t Reserved4[8];
void* Reserved5[26];
void* ReservedForOle;  // Windows 2000 only
void* Reserved6[4];
void* TlsExpansionSlots;
} TEB, *PTEB;

bool DynamicPythonSyscall_Init()
{

return true;
}
*/

