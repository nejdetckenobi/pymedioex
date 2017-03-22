#include <Python.h>
#include "pmedex.h"
#include <bcm2835.h>


int to_do_pin(int var) {
        int result;
        switch(var) {
                case 1: result = pe2a_GPIO_J4_1; break;
                case 2: result = pe2a_GPIO_J4_2; break;
                case 3: result = pe2a_GPIO_J4_3; break;
                case 4: result = pe2a_GPIO_J4_4; break;
                case 5: result = pe2a_GPIO_J5_5; break;
                case 6: result = pe2a_GPIO_J5_6; break;
                case 7: result = pe2a_GPIO_J5_7; break;
                case 8: result = pe2a_GPIO_J5_8; break;
                case 9: result = pe2a_GPIO_J6_9; break;
                case 10: result = pe2a_GPIO_J6_10; break;
                case 11: result = pe2a_GPIO_J6_11; break;
                case 12: result = pe2a_GPIO_J6_12; break;
                case 13: result = pe2a_GPIO_J3_1; break; // Relay triggers
                case 14: result = pe2a_GPIO_J3_2; break; // Relay triggers
                case 15: result = pe2a_GPIO_J3_3; break; // Relay triggers
                case 16: result = pe2a_GPIO_J3_4; break; // Relay triggers
		default: result = -1;
        }
        return result;
}

int to_di_pin(int var) {
        int result = -1;
        switch(var) {
                case 1: result = pe2a_GPIO_J17_1; break;
                case 2: result = pe2a_GPIO_J17_2; break;
                case 3: result = pe2a_GPIO_J17_3; break;
                case 4: result = pe2a_GPIO_J17_4; break;
                case 5: result = pe2a_GPIO_J16_5; break;
                case 6: result = pe2a_GPIO_J16_6; break;
                case 7: result = pe2a_GPIO_J16_7; break;
                case 8: result = pe2a_GPIO_J16_8; break;
                case 9: result = pe2a_GPIO_J15_9; break;
                case 10: result = pe2a_GPIO_J15_10; break;
                case 11: result = pe2a_GPIO_J15_11; break;
                case 12: result = pe2a_GPIO_J15_12; break;
                case 13: result = pe2a_GPIO_J14_13; break;
                case 14: result = pe2a_GPIO_J14_14; break;
                case 15: result = pe2a_GPIO_J14_15; break;
                case 16: result = pe2a_GPIO_J14_16; break;
                default: result = -1;
        }
        return result;
}

int to_ao_pin(int var) {
	int result;
	switch(var) {
		case 1: result = pe2a_GPIO_J1_1; break;
		case 2: result = pe2a_GPIO_J1_2; break;
		case 3: result = pe2a_GPIO_J1_3; break;
		case 4: result = pe2a_GPIO_J1_4; break;
		default: result = -1;
	}
	return result;
}

int to_ai_pin(int var) {
	int result;
	switch(var) {
		case 1: result = pe2a_GPIO_J13_1; break;
		case 2: result = pe2a_GPIO_J13_2; break;
		case 3: result = pe2a_GPIO_J13_3; break;
		case 4: result = pe2a_GPIO_J13_4; break;
		default: result = -1;
	}
	return result;
}

static PyObject *
do_di_init(PyObject *self, PyObject *args)
{
	pe2a_DO_DI_init();
	return Py_BuildValue("");
}

static PyObject *
ao_init(PyObject *self, PyObject *args)
{
	pe2a_AO_init();
	return Py_BuildValue("");
}

static PyObject *
ai_init(PyObject *self, PyObject *args)
{
	pe2a_AI_init();
	return Py_BuildValue("");
}

static PyObject *
do_write(PyObject *self, PyObject *args)
{
	int pin, val;
	if (!PyArg_ParseTuple(args, "ii", &pin, &val)) return NULL;
	pin = to_do_pin(pin);
	if(val == 1) pe2a_DO_setHigh(pin);
	else if(val == 0) pe2a_DO_setLow(pin);
	return Py_BuildValue("");
}

static PyObject *
di_read(PyObject *self, PyObject *args)
{
	int pin, val;
	if (!PyArg_ParseTuple(args, "i", &pin)) return NULL;
	pin = to_di_pin(pin);
	val = pe2a_DI_getVal(pin);
	return PyLong_FromLong(val);
}

static PyObject *
ao_write(PyObject *self, PyObject *args)
{
	int pin, val;
	if (!PyArg_ParseTuple(args, "ii", &pin, &val)) return NULL;
	pin = to_ao_pin(pin);
	if (val < 4096 && val >=0) pe2a_AO_writeVal(pin, val);
	return Py_BuildValue("");
}

static PyObject *
ai_read(PyObject *self, PyObject *args)
{
	int pin, val;
	if (!PyArg_ParseTuple(args, "i", &pin)) return NULL;
	pin = to_ai_pin(pin);
	val = pe2a_AI_getVal(pin);
	return PyLong_FromLong(val);
}

static PyObject *
close_all(PyObject *self, PyObject *args)
{
	pe2a_bcm2835_close();
	return Py_BuildValue("");
}

static PyObject *
temp_init(PyObject *self, PyObject *args)
{
	pe2a_getTemperature_init();
	return Py_BuildValue("");
}

static PyObject *
temp_read(PyObject *self, PyObject *args)
{
	int val, getval;
	if (!PyArg_ParseTuple(args, "i", &getval)) return NULL;
	val = pe2a_getTemperature(getval);
	return PyLong_FromLong(val);
}

static PyMethodDef MedIOExMethods[] = {
	{"do_di_init", do_di_init, METH_VARARGS,
	 "Initializes Digital Outputs and Digital Inputs"},
	{"ao_init", ao_init, METH_VARARGS,
	 "Initializes Analog Outputs"},
	{"ai_init", ai_init, METH_VARARGS,
	 "Initializes Analog Inputs"},
	{"do_write", do_write, METH_VARARGS,
	 "Writes to a Digital Output"},
	{"di_read", di_read, METH_VARARGS,
	 "Reads from a Digital Input"},
	{"ao_write", ao_write, METH_VARARGS,
	 "Writes to an Analog Output"},
	{"ai_read", ai_read, METH_VARARGS,
	 "Reads from an Analog Input"},
	{"close_all", close_all, METH_VARARGS,
	 "Closes all ports"},
	{"temp_init", temp_init, METH_VARARGS,
	 "Initializes temperature sensor"},
	{"temp_read", temp_read, METH_VARARGS,
	 "Reads from temperature sensor. If its argument is 1, it reads from lm75bd"},
	{NULL, NULL, 0, NULL} // Sentinel
};

static struct PyModuleDef medioexmodule = {
	PyModuleDef_HEAD_INIT,
	"medioex",
	NULL,
	-1,
	MedIOExMethods
};

PyMODINIT_FUNC
PyInit_medioex(void)
{
	PyObject *m;
	m = PyModule_Create(&medioexmodule);
	if (m == NULL) return NULL;
	// SpamError = PyErr_NewException("spam.error", NULL, NULL);
	// Py_INCREF(SpamError);
	// PyModule_AddObject(m, "error", SpamError);
	return m;
}


int
main(int argc, char *argv[])
{
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    /* Add a built-in module, before Py_Initialize */
    PyImport_AppendInittab("medioex", PyInit_medioex);

    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(program);

    /* Initialize the Python interpreter.  Required. */
    Py_Initialize();

    /* Optionally import the module; alternatively,
       import can be deferred until the embedded script
       imports it. */
    PyImport_ImportModule("medioex");


    PyMem_RawFree(program);
    return 0;
}

