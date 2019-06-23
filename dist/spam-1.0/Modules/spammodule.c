#define PY_SSIZE_T_CLEAN
#include <Python/Python.h>

#define SPAM_MODULE
#include "spammodule.h"

// Method Table
static PyMethodDef SpamMethods[] = {
    {"system",  spam_system, METH_VARARGS,
     "Execute a shell command."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

//// Error
//PyMODINIT_FUNC
//initspam(void)
//{
//    PyObject *m;
//
//    m = Py_InitModule("spam", SpamMethods);
//    if (m == NULL)
//        return;
//
//    SpamError = PyErr_NewException("spam.error", NULL, NULL);
//    Py_INCREF(SpamError);
//    PyModule_AddObject(m, "error", SpamError);
//}

// Main
static PyObject *
spam_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
//    if (sts < 0) {
//            PyErr_SetString(SpamError, "System command failed");
//            return NULL;
//    }
    return Py_BuildValue("i", sts);
}

// Module definition
//static struct PyModuleDef spammodule = {
//    PyModuleDef_HEAD_INIT,
//    "spam",   /* name of module */
//    spam_doc, /* module documentation, may be NULL */
//    -1,       /* size of per-interpreter state of the module,
//                 or -1 if the module keeps state in global variables. */
//    SpamMethods
//};

// Initialization function
//PyMODINIT_FUNC
//PyInit_spam(void)
//{
//    return PyModule_Create(&spammodule);
//}

// Module definition and initializer
PyMODINIT_FUNC
initspam(void)
{
    (void) Py_InitModule("spam", SpamMethods);
}

// Initialization Table
int
main(int argc, char *argv[])
{
  /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(argv[0]);

    /* Initialize the Python interpreter.  Required. */
    Py_Initialize();

    /* Add a static module */
    initspam();

}