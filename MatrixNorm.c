#include <Python.h>
#include <math.h>

static PyObject *NormEuclidean(PyObject *self, PyObject *args) {
    PyObject *list;
    double  item, res;
    res = 0;
    int i, len1;

    if (!PyArg_ParseTuple(args,"O", &list)) {
        return NULL;
    }
    len1 = PySequence_Fast_GET_SIZE(list);
    for(i=0; i<len1; i++){
      PyObject *aux = PySequence_Fast_GET_ITEM(list,i);
      item = PyFloat_AsDouble(aux);
      res +=  item*item;
    }
    return Py_BuildValue("d", sqrt(res));
}

static PyObject *NormManhattan(PyObject *self, PyObject *args) {
    PyObject *list;
    double  item, res;
    res = 0;
    int i, len1;

    if (!PyArg_ParseTuple(args,"O", &list)) {
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

static PyObject *NormInfinity(PyObject *self, PyObject *args) {
    PyObject *list;
    double  item, res;
    int i, len1;

    if (!PyArg_ParseTuple(args,"O", &list)) {
        return NULL;
    }
    len1 = PySequence_Fast_GET_SIZE(list);
    res = PyFloat_AsDouble(PySequence_Fast_GET_ITEM(list, 0));
    for(i=0; i<len1; i++){
      PyObject *aux = PySequence_Fast_GET_ITEM(list,i);
      item = PyFloat_AsDouble(aux);
      if(fabs(item) > fabs(res)){
        res = item;
      }
    }

    return Py_BuildValue("d", res);
}

static PyObject *NormLp(PyObject *self, PyObject *args) {
    PyObject *list;
    double  p, item, res;
    res = 0;
    int i, len1;

    if (!PyArg_ParseTuple(args,"Od", &list, &p)) {
        return NULL;
    }
    len1 = PySequence_Fast_GET_SIZE(list);
    for(i=0; i<len1; i++){
      PyObject *aux = PySequence_Fast_GET_ITEM(list,i);
      item = PyFloat_AsDouble(aux);
      res +=  pow(fabs(item), (double)p);
    }
    return Py_BuildValue("d", pow(res, (double)1/p));
}


static PyObject *MatrixNormLp(PyObject *self, PyObject *args) {
    PyObject *list;
    double  p, item, res;
    res = 0;
    int i, j, len1, len2;

    if (!PyArg_ParseTuple(args,"Od", &list, &p)) {
        return NULL;
    }
    len1 = PySequence_Fast_GET_SIZE(list);
    len2 = PySequence_Fast_GET_SIZE(PySequence_Fast_GET_ITEM(list,0));
    for(i=0; i<len1; i++){
      PyObject *aux1 = PySequence_Fast_GET_ITEM(list,i);
      for(j=0; j<len2; j++) {
        PyObject *aux2 = PySequence_Fast_GET_ITEM(aux1,j);

        item = PyFloat_AsDouble(aux2);
        res +=  pow(fabs(item), (double)p);
    }
    }
    return Py_BuildValue("d", pow(res, (double)1/p));
}

static PyObject *MatrixNormFrobenius(PyObject *self, PyObject *args) {
    PyObject *list;
    double  item, res;
    res = 0;
    int i, j, len1, len2;

    if (!PyArg_ParseTuple(args,"O", &list)) {
        return NULL;
    }
    len1 = PySequence_Fast_GET_SIZE(list);
    len2 = PySequence_Fast_GET_SIZE(PySequence_Fast_GET_ITEM(list,0));
    for(i=0; i<len1; i++){
      PyObject *aux1 = PySequence_Fast_GET_ITEM(list,i);
      for(j=0; j<len2; j++) {
        PyObject *aux2 = PySequence_Fast_GET_ITEM(aux1,j);

        item = PyFloat_AsDouble(aux2);
        res +=  item*item;
    }
    }
    return Py_BuildValue("d", sqrt(res));
}

static PyObject *MatrixNormOne(PyObject *self, PyObject *args) {
    PyObject *list;
    double  item, res, sum, *new;
    res = 0;
    int i, j, len1, len2;

    if (!PyArg_ParseTuple(args,"O", &list)) {
        return NULL;
    }
    len1 = PySequence_Fast_GET_SIZE(list);
    len2 = PySequence_Fast_GET_SIZE(PySequence_Fast_GET_ITEM(list,0));

    new = (double*)malloc(len2 * sizeof(double));

    for(j=0; j<len2; j++){
      sum = 0;
      PyObject *aux1 = PySequence_Fast_GET_ITEM(list,j);
      for(i=0; i<len1; i++) {
        PyObject *aux2 = PySequence_Fast_GET_ITEM(aux1,i);

        item = PyFloat_AsDouble(aux2);
        sum += fabs(item);
      }
      new[j] = sum;
    }
    res = new[0];
    for(i=0; i<len2; i++){
      if(fabs(new[i]) > fabs(res)){
        res = new[i];
      }
    }
    free(new);
    return Py_BuildValue("d", res);
}

static PyObject *MatrixNormInfinity(PyObject *self, PyObject *args) {
    PyObject *list;
    double  item, res, sum, *new;
    int i, j, len1, len2;

    if (!PyArg_ParseTuple(args,"O", &list)) {
        return NULL;
    }
    len1 = PySequence_Fast_GET_SIZE(list);
    len2 = PySequence_Fast_GET_SIZE(PySequence_Fast_GET_ITEM(list,0));

    new = (double*)malloc(len1 * sizeof(double));

    for(i=0; i<len1; i++){
      sum = 0;
      PyObject *aux1 = PySequence_Fast_GET_ITEM(list,i);
      for(j=0; j<len2; j++) {
        PyObject *aux2 = PySequence_Fast_GET_ITEM(aux1,j);

        item = PyFloat_AsDouble(aux2);
        sum += fabs(item);
      }
    new[i] = sum;
    }
    res = new[0];
    for(i=0; i<len1; i++){
      if(fabs(new[i]) > fabs(res)){
        res = new[i];
      }
    }
    free(new);
    return Py_BuildValue("d", res);
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
        {
                "NormInfinity", // название функции внутри python
                NormInfinity, // функция C
                METH_VARARGS, // макрос, поясняющий, что функция у нас с аргументами
                "calculate the infinity norm" // документация для функции внутри python
        },
        {
                "MatrixNormLp", // название функции внутри python
                MatrixNormLp, // функция C
                METH_VARARGS, // макрос, поясняющий, что функция у нас с аргументами
                "calculate the matrix norm p of the space L" // документация для функции внутри python
        },
        {
                "MatrixNormFrobenius", // название функции внутри python
                MatrixNormFrobenius, // функция C
                METH_VARARGS, // макрос, поясняющий, что функция у нас с аргументами
                "calculate the Frobenius norm" // документация для функции внутри python
        },
        {
                "MatrixNormOne", // название функции внутри python
                MatrixNormOne, // функция C
                METH_VARARGS, // макрос, поясняющий, что функция у нас с аргументами
                "calculate the matrix norm one" // документация для функции внутри python
        },
        {
                "MatrixNormInfinity", // название функции внутри python
                MatrixNormInfinity, // функция C
                METH_VARARGS, // макрос, поясняющий, что функция у нас с аргументами
                "calculate the infinity matrix norm" // документация для функции внутри python
        },

        { NULL, NULL, 0, NULL }
};


static PyModuleDef module = {
        PyModuleDef_HEAD_INIT, // обязательный макрос
        "MatrixNorm", // my_plus.__name__
        "amazing documentation", // my_plus.__doc__
        -1,
        ownmod_methods // methods
};

//PyInit
PyMODINIT_FUNC PyInit_MatrixNorm(void) {
    PyObject* m;
// создаем модуль
    m = PyModule_Create(&module);
    if (m == NULL)
        return NULL;
    return m;
}
