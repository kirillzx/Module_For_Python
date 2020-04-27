#include <Python.h>
#include <math.h>

static PyObject *NormEuclidean(PyObject *self, PyObject *args) {
    PyObject *list;
    double  item, len1, res;
    res = 0;
    int i;

    if (!PyArg_ParseTuple(args,"OO", &list)) {
        return NULL;
    }
    len1 = PySequence_Fast_GET_SIZE(list);
    // len2 = PySequence_Fast_GET_SIZE(pylist2);
    // if (len1 != len2)
    //     return NULL;

    // for(i=0; i<len1; i++) {
    //     PyObject *item1 = PySequence_Fast_GET_ITEM(pylist1,i);
    //     PyObject *item2 = PySequence_Fast_GET_ITEM(pylist2,i);
    //     double_item1 = PyFloat_AsDouble(item1);
    //     double_item2 = PyFloat_AsDouble(item2);
    //     result += double_item1 * double_item2;
    // }
    for(i=0; i<len1; i++){
      PyObject *aux = PySequence_Fast_GET_ITEM(list,i);
      item = PyFloat_AsDouble(aux);
      res +=  item*item;
    }
    return Py_BuildValue("d", sqrt(res));
}

static PyObject *NormManhattan(PyObject *self, PyObject *args) {
    PyObject *list;
    double  item, len1, res;
    res = 0;
    int i;

    if (!PyArg_ParseTuple(args,"OO", &list)) {
        return NULL;
    }
    len1 = PySequence_Fast_GET_SIZE(list);
    for(i=0; i<len1; i++){
      PyObject *aux = PySequence_Fast_GET_ITEM(list,i);
      item = PyFloat_AsDouble(aux);
      res +=  fabs(item);
    }
    return Py_BuildValue("d", res);
}

static PyObject *NormLp(PyObject *self, PyObject *args) {
    PyObject *list;
    double  item, len1, res;
    res = 0;
    int i, p;
    p = 5;

    if (!PyArg_ParseTuple(args,"OO", &list)) {
        return NULL;
    }
    len1 = PySequence_Fast_GET_SIZE(list);
    for(i=0; i<len1; i++){
      PyObject *aux = PySequence_Fast_GET_ITEM(list,i);
      item = PyFloat_AsDouble(aux);
      res +=  pow(fabs(item), p);
    }
    return Py_BuildValue("d", pow(res, 1/p));
}

static PyMethodDef ownmod_methods[] = {
        {
                "NormEuclidean", // название функции внутри python
                NormEuclidean, // функция C
                METH_VARARGS, // макрос, поясняющий, что функция у нас с аргументами
                "calculate the Euclidean norm" // документация для функции внутри python
        },
        {
                "NormManhattan", // название функции внутри python
                NormManhattan, // функция C
                METH_VARARGS, // макрос, поясняющий, что функция у нас с аргументами
                "calculate the Manhattan distance" // документация для функции внутри python
        },
        {
                "NormLp", // название функции внутри python
                NormLp, // функция C
                METH_VARARGS, // макрос, поясняющий, что функция у нас с аргументами
                "calculate the p norm of the space L" // документация для функции внутри python
        },
        { NULL, NULL, 0, NULL }
};


static PyModuleDef simple_module = {
        /* Описываем наш модуль */
        PyModuleDef_HEAD_INIT, // обязательный макрос
        "MatrixNorm", // my_plus.__name__
        "amazing documentation", // my_plus.__doc__
        -1,
        ownmod_methods // сюда передаем методы модуля
};

// в названии функции обязательно должен быть префикс PyInit
PyMODINIT_FUNC PyInit_MatrixNorm(void) {
    PyObject* m;
// создаем модуль
    m = PyModule_Create(&simple_module);
// если все корректно, то эта проверка не проходит
    if (m == NULL)
        return NULL;
    return m;
}
